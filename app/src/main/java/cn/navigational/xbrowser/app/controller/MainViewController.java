package cn.navigational.xbrowser.app.controller;

import cn.navigational.xbrowser.app.AbstractWindowController;
import cn.navigational.xbrowser.app.controller.web.AbstractWebPageController;
import cn.navigational.xbrowser.app.controller.web.impl.WebPageController;
import cn.navigational.xbrowser.kit.util.StringUtil;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.collections.ListChangeListener;
import javafx.fxml.FXML;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.web.WebEngine;


/**
 * 主界面视图
 */
public class MainViewController extends AbstractWindowController<BorderPane> {
    @FXML
    private TabPane tabPane;

    private MainViewController() {
        super("MainView.fxml");
        this.getStage().setTitle("x-browser");
        this.setSizeByProp(0.7, 0.8);
        this.tabPane.getSelectionModel().selectedItemProperty().addListener(this.tabSelectChangeListener());
        this.tabPane.getTabs().add(new WebPageController().getTab());
        this.tabPane.getTabs().addListener(this.tabListChangeListener());
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


    private static MainViewController mainViewController;

    public synchronized static MainViewController getInstance() {
        if (mainViewController == null) {
            mainViewController = new MainViewController();
        }
        return mainViewController;
    }

}

