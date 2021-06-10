package cn.navigational.xplayer.app.controller.controls;

import cn.navigational.xplayer.app.AbstractFXMLController;
import cn.navigational.xplayer.app.assets.XPlayerResource;
import cn.navigational.xplayer.kit.Closeable;
import cn.navigational.xplayer.kit.Location;
import cn.navigational.xplayer.kit.enums.SearchEngine;
import cn.navigational.xplayer.kit.util.StringUtil;
import cn.navigational.xplayer.kit.util.URLUtil;
import javafx.beans.value.ChangeListener;
import javafx.concurrent.Worker;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.HBox;
import javafx.scene.web.WebEngine;

import java.util.Optional;


public class NavigatorBarController extends AbstractFXMLController<HBox> {
    @FXML
    private Button go;
    @FXML
    private Button back;
    @FXML
    private Button flush;
    @FXML
    private HBox inputBox;
    @FXML
    private Button sEngine;
    @FXML
    private TextField textField;

    private final WebEngine engine;

    private final NavigatorBarService service;

    private SearchEngine searchEngine;

    private final ChangeListener<String> urlChangeListener = this.urlChangeListener();

    private final ChangeListener<Boolean> focusListener = this.textInputFocusListener();

    private final ChangeListener<String> titleChangeListener = this.titleChangeListener();

    private final ChangeListener<Worker.State> stateChangeListener = this.stateChangeListener();


    public NavigatorBarController(NavigatorBarService service) {
        super("controls/NavigatorBar.fxml");
        this.service = service;
        this.engine = service.getWebEngine();
        this.switchEngine(SearchEngine.BAIDU);
        this.textField.setOnKeyPressed(this::textInputChange);
        this.textField.focusedProperty().addListener(this.focusListener);
        this.engine.titleProperty().addListener(this.titleChangeListener);
        this.engine.locationProperty().addListener(this.urlChangeListener);
        this.engine.getLoadWorker().stateProperty().addListener(this.stateChangeListener);
    }


    private int getCurrentIndex() {
        var history = engine.getHistory();
        return history.getCurrentIndex();
    }

    private void switchEngine(SearchEngine engine) {
        this.searchEngine = engine;
        this.sEngine.setGraphic(new ImageView(getSEngineIcon(engine)));
    }

    /**
     * 浏览器前进事件
     */
    @FXML
    private void go(ActionEvent event) {
        service.go(event);
        if (event.isConsumed()) {
            return;
        }
        var max = engine.getHistory().getEntries().size();
        if (getCurrentIndex() < max - 1) {
            service.getWebEngine().getHistory().go(1);
        }
    }

    /**
     * 浏览器后退事件
     */
    @FXML
    private void back(ActionEvent event) {
        this.service.back(event);
        if (event.isConsumed()) {
            return;
        }
        if (getCurrentIndex() <= 0) {
            return;
        }
        engine.getHistory().go(-1);
    }

    /**
     * 刷新事件
     */
    @FXML
    private void flush(ActionEvent event) {
        this.service.flush(event);
        if (event.isConsumed()) {
            return;
        }
        var state = this.engine.getLoadWorker().getState();
        if (state == Worker.State.CANCELLED || state == Worker.State.SUCCEEDED || state == Worker.State.FAILED) {
            engine.reload();
        } else {
            this.engine.getLoadWorker().cancel();
        }
    }

    /**
     * 监听{@link WebEngine#locationProperty()}属性
     */
    private ChangeListener<String> urlChangeListener() {
        return (observable, oldValue, newValue) -> {
            this.textField.setText(newValue);
            service.url(newValue);
        };
    }

    /**
     * 监听{@link WebEngine#titleProperty()}属性
     */
    private ChangeListener<String> titleChangeListener() {
        return (observable, oldValue, newValue) -> this.service.title(newValue);
    }

    /**
     * 监听{@link TextField} 是否获取焦点
     */
    private ChangeListener<Boolean> textInputFocusListener() {
        return (observable, oldValue, newValue) -> {
            var styleClass = this.inputBox.getStyleClass();
            if (!newValue) {
                styleClass.remove("input-box-active");
                return;
            }
            var contain = styleClass.contains("input-box-active");
            if (!contain) {
                styleClass.add("input-box-active");
            }
        };
    }

    /**
     * 监听当前输入是否按下ENTER,如果按下处理对应的逻辑{搜索/网页跳转}
     */
    private void textInputChange(KeyEvent event) {
        if (event.getCode() != KeyCode.ENTER) {
            return;
        }
        var keyword = this.textField.getText();
        if (StringUtil.isEmpty(keyword)) {
            return;
        }
        this.engine.load(URLUtil.getUrl(this.searchEngine, keyword));
    }

    /**
     * 监听{@link WebEngine}加载状态
     */
    private ChangeListener<Worker.State> stateChangeListener() {
        return ((observable, oldValue, newValue) -> {
            final Image image;
            //显示刷新图标
            if (isComplete(newValue)) {
                image = XPlayerResource.loadImage("flush.png");
            } else {
                //显示中断
                image = XPlayerResource.loadImage("cancel.png");
            }
            this.flush.setGraphic(new ImageView(image));
            this.service.state(newValue);
        });
    }

    private Image getSEngineIcon(SearchEngine engine) {
        final String icon;
        if (engine == SearchEngine.BAIDU) {
            icon = "engine/baidu.png";
        } else {
            icon = "engine/google.png";
        }
        return XPlayerResource.loadImage(icon);
    }

    /**
     * 判断当前加载工作是否完成
     */
    public boolean isComplete(Worker.State state) {
        return state == Worker.State.CANCELLED
                || state == Worker.State.SUCCEEDED
                || state == Worker.State.FAILED;
    }

    /**
     * 获取当前网页{@link Location}对象
     */
    public Optional<Location> getLocation() {
        var str = engine.getLocation();
        if (StringUtil.isEmpty(str)) {
            return Optional.empty();
        }
        return Optional.of(Location.create(str));
    }

    @Override
    public void dispose() {
        super.dispose();
        this.textField.focusedProperty().removeListener(this.focusListener);
        this.engine.titleProperty().removeListener(this.titleChangeListener);
        this.engine.locationProperty().removeListener(this.urlChangeListener);
        this.engine.getLoadWorker().stateProperty().removeListener(this.stateChangeListener);
    }

    public interface NavigatorBarService extends Closeable {
        /**
         * 后退事件触发
         */
        default void back(ActionEvent event) {
        }

        /**
         * 前进事件触发
         */
        default void go(ActionEvent event) {
        }

        /**
         * url发生改变触发
         */
        default void url(String url) {
        }

        /**
         * 浏览器刷新时调用
         */
        default void flush(ActionEvent event) {
        }

        /**
         * 网站标题发生改变时调用
         */
        default void title(String title) {
        }

        /**
         * 网页加载进度
         *
         * @param value 进度值
         */
        default void progress(double value) {

        }

        /**
         * 网页加载状态发生改变时回调当前函数
         */
        default void state(Worker.State state) {

        }

        /**
         * 获取{@link WebEngine}实例对象
         */
        WebEngine getWebEngine();
    }
}
