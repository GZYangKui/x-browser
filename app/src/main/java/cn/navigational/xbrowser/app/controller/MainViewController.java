package cn.navigational.xbrowser.app.controller;

import cn.navigational.xbrowser.app.AbstractWindowController;
import cn.navigational.xbrowser.app.controller.web.AbstractWebPageController;
import cn.navigational.xbrowser.app.controller.web.impl.WebPageController;
import cn.navigational.xbrowser.kit.Closeable;
import cn.navigational.xbrowser.kit.util.NumberUtil;
import cn.navigational.xbrowser.kit.util.StringUtil;
import javafx.animation.AnimationTimer;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.collections.ListChangeListener;
import javafx.fxml.FXML;
import javafx.scene.Cursor;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.web.WebEngine;
import jdk.jfr.consumer.EventStream;

import java.util.Calendar;
import java.util.Timer;
import java.util.TimerTask;


/**
 * 主界面视图
 */
public class MainViewController extends AbstractWindowController<BorderPane> implements Closeable {
    /**
     * 定时统计内存时间间隔
     */
    private static final long CALCULATE_PERIOD = 1000L;
    /**
     * 内存占用过高显示样式
     */
    private static final String MEM_HIGHER_CLASS = "memory-higher";

    @FXML
    private Label fpsLabel;
    @FXML
    private Label memText;
    @FXML
    private TabPane tabPane;
    @FXML
    private Button triggerGC;
    @FXML
    private ProgressBar memBar;

    private final Timer timer;

    private int frameTimeIndex = 0;
    private boolean arrayFilled = false;
    private final AnimationTimer fpsTimer;
    private final long[] frameTimes = new long[100];

    private MainViewController() {
        super("MainView.fxml");
        this.timer = new Timer();
        this.fpsTimer = this.fps();
        this.getStage().setTitle("x-browser");
        this.setSizeByProp(0.7, 0.8);
        this.triggerGC.setCursor(Cursor.HAND);
        this.timer.schedule(this.calculateMemory(), 0, CALCULATE_PERIOD);
        this.tabPane.getTabs().add(new WebPageController().getTab());
        this.tabPane.getTabs().addListener(this.tabListChangeListener());
        this.tabPane.getSelectionModel().selectedItemProperty().addListener(this.tabSelectChangeListener());
    }

    /**
     * 使用固定帧数时间法,计算FPS
     */
    private AnimationTimer fps() {
        AnimationTimer fpsTimer = new AnimationTimer() {
            @Override
            public void handle(long now) {
                long oldFrameTime = frameTimes[frameTimeIndex];
                frameTimes[frameTimeIndex] = now;
                frameTimeIndex = (frameTimeIndex + 1) % frameTimes.length;
                if (frameTimeIndex == 0) {
                    arrayFilled = true;
                }
                if (arrayFilled) {
                    //获取两帧之间的时间差
                    var elapsedNanos = now - oldFrameTime;
                    var elapsedNanosPerFrame = elapsedNanos / frameTimes.length;
                    var frameRate = 1_000_000_000.0 / elapsedNanosPerFrame;
                    var fps = String.format("FPS: %.2f", frameRate);
                    fpsLabel.setText(fps);
                }
            }
        };
        fpsTimer.start();
        return fpsTimer;
    }

    /**
     * 监听{@link TabPane#getTabs()}列表改变事件
     */
    private ListChangeListener<Tab> tabListChangeListener() {
        return c -> {
            while (c.next()) {
                //如果当前TabPane中Tab被全部移出,退出程序
                if (c.wasRemoved() && this.tabPane.getTabs().isEmpty()) {
                    Platform.exit();
                }
            }
        };
    }


    /**
     * 监听tab选中事件,动态改变当前窗口标题
     */
    private ChangeListener<Tab> tabSelectChangeListener() {
        return (observable, oldValue, newValue) -> {
            if (newValue == null) {
                return;
            }
            var controller = newValue.getUserData();
            if (!(controller instanceof AbstractWebPageController)) {
                return;
            }
            var title = ((AbstractWebPageController) controller).getTitle();
            this.updateTitle(title, newValue);
        };
    }

    /**
     * 处理window.open 打开窗口事件
     */
    public WebEngine createPopupWindow() {
        var controller = new WebPageController();
        var tab = controller.getTab();
        this.tabPane.getTabs().add(tab);
        this.tabPane.getSelectionModel().select(tab);
        return controller.getWebEngine();
    }

    /**
     * 更新窗口标题
     */
    public void updateTitle(String title, Tab target) {
        var current = this.tabPane.getSelectionModel().getSelectedItem();
        if (current != target) {
            return;
        }
        if (StringUtil.isEmpty(title)) {
            title = "x-browser";
        }
        this.getStage().setTitle(title);
    }

    /**
     * 动态统计当前应用内存使用情况
     */
    private TimerTask calculateMemory() {
        return new TimerTask() {
            @Override
            public void run() {
                var free = Runtime.getRuntime().freeMemory();
                var total = Runtime.getRuntime().totalMemory();

                var sTotal = NumberUtil.byteToMB(total);
                var sUsed = NumberUtil.byteToMB(total - free);
                var rate = sUsed / sTotal;

                Platform.runLater(() -> {
                    MainViewController.this.memBar.setProgress(rate);
                    MainViewController.this.memText.setText(sUsed + "MB of " + sTotal + "MB");
                    var high = rate > 0.7 && !memBar.getStyleClass().contains(MEM_HIGHER_CLASS);
                    if (high) {
                        memBar.getStyleClass().add(MEM_HIGHER_CLASS);
                    } else {
                        memBar.getStyleClass().remove(MEM_HIGHER_CLASS);
                    }
                });
            }
        };
    }

    @FXML
    private void triGC() {
        System.gc();
    }

    @Override
    public void dispose() {
        this.timer.cancel();
        this.fpsTimer.stop();
    }

    private static MainViewController mainViewController;

    public synchronized static MainViewController getInstance() {
        if (mainViewController == null) {
            mainViewController = new MainViewController();
        }
        return mainViewController;
    }

}

