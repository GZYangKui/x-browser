package cn.navigational.xbrowser.app.controller.controls;

import cn.navigational.xbrowser.app.AbstractFXMLController;
import cn.navigational.xbrowser.app.assets.XResource;
import cn.navigational.xbrowser.app.controller.MainViewController;
import cn.navigational.xbrowser.app.controller.popup.PopupMenuController;
import cn.navigational.xbrowser.app.util.PopMessageUtil;
import cn.navigational.xbrowser.app.util.WebEngineUtil;
import cn.navigational.xbrowser.kit.Closeable;
import cn.navigational.xbrowser.kit.Location;
import cn.navigational.xbrowser.kit.downloader.XDownloadHelper;
import cn.navigational.xbrowser.kit.enums.SearchEngine;
import cn.navigational.xbrowser.kit.util.StringUtil;
import cn.navigational.xbrowser.kit.util.LocationUtil;
import javafx.beans.value.ChangeListener;
import javafx.concurrent.Worker;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.MenuButton;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.web.WebEngine;

import java.util.Optional;
import java.util.UUID;
import java.util.concurrent.CompletableFuture;


public class NavigatorBarController extends AbstractFXMLController<HBox> {
    @FXML
    private Button go;
    @FXML
    private Button func;
    @FXML
    private Button back;
    @FXML
    private Button flush;
    @FXML
    private HBox inputBox;
    @FXML
    private MenuButton sEngine;
    @FXML
    private TextField textField;

    private final WebEngine engine;

    private SearchEngine searchEngine;

    private final NavigatorBarService service;

    private final PopupMenuController popupMenuController;

    private final ChangeListener<Boolean> focusListener = this.textInputFocusListener();

    private final ChangeListener<String> titleChangeListener = this.titleChangeListener();

    private final ChangeListener<Number> indexChangeListener = this.indexChangeListener();

    private final ChangeListener<Worker.State> stateChangeListener = this.stateChangeListener();

    private final ChangeListener<String> locationChangeListener = this.locationChangeListener();


    public NavigatorBarController(NavigatorBarService service) {
        super("controls/NavigatorBar.fxml");
        this.initSEngine();
        this.service = service;
        this.engine = service.getWebEngine();
        this.func.setOnMouseClicked(this::openFuncPopup);
        this.textField.setOnKeyPressed(this::textInputChange);
        this.popupMenuController = new PopupMenuController(service);
        this.textField.focusedProperty().addListener(this.focusListener);
        this.engine.titleProperty().addListener(this.titleChangeListener);
        this.engine.locationProperty().addListener(this.locationChangeListener);
        this.engine.getLoadWorker().stateProperty().addListener(this.stateChangeListener);
        this.engine.getHistory().currentIndexProperty().addListener(this.indexChangeListener);

    }

    /**
     * 初始化搜索引擎选项
     */
    private void initSEngine() {
        for (SearchEngine value : SearchEngine.values()) {
            var item = new MenuItem();
            item.setText(value.getTitle());
            item.setOnAction(event -> this.switchEngine(value));
            item.setGraphic(new ImageView(getSEngineIcon(value)));
            this.sEngine.getItems().add(item);
        }
        this.switchEngine(SearchEngine.BAIDU);
    }

    /**
     * 切换搜索引擎
     */
    private void switchEngine(SearchEngine engine) {
        this.searchEngine = engine;
        this.sEngine.setGraphic(new ImageView(getSEngineIcon(engine)));
    }

    /**
     * 获取当前鼠标点击位置显示{@link cn.navigational.xbrowser.app.control.PopupMenu}
     */
    private void openFuncPopup(MouseEvent event) {
        var x = event.getScreenX();
        var y = event.getScreenY() + 20;
        this.popupMenuController.show(x, y);
    }


    private int getCurrentIndex() {
        var history = engine.getHistory();
        return history.getCurrentIndex();
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
        if (isComplete(state)) {
            engine.reload();
        } else {
            this.engine.getLoadWorker().cancel();
        }
    }

    /**
     * {@link WebEngine#getHistory()#indexChangeListener()}
     */
    private ChangeListener<Number> indexChangeListener() {
        return (observable, oldValue, newValue) -> {
            var index = newValue.intValue();
            var max = this.engine.getHistory().getEntries().size();
            //判断前进按钮是否可用
            if (index != max - 1) {
                this.go.setGraphic(new ImageView(XResource.loadImage("go.png")));
            } else {
                this.go.setGraphic(new ImageView(XResource.loadImage("go_disable.png")));
            }
            //判断后退按钮是否可用
            if (index > 0) {
                this.back.setGraphic(new ImageView(XResource.loadImage("back.png")));
            } else {
                this.back.setGraphic(new ImageView(XResource.loadImage("back_disable.png")));
            }
        };
    }

    /**
     * 监听{@link WebEngine#locationProperty()}属性
     */
    private ChangeListener<String> locationChangeListener() {
        return (observable, oldValue, newValue) -> {
            this.textField.setText(newValue);
            this.checkDownload(newValue);
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
        this.engine.load(LocationUtil.getUrl(this.searchEngine, keyword));
    }

    /**
     * js中调用java搜索
     */
    public void jsSearch(String keyword) {
        if (StringUtil.isEmpty(keyword)){
            return;
        }
        this.engine.load(LocationUtil.getUrl(this.searchEngine, keyword));
    }

    /**
     * 监听{@link WebEngine}加载状态
     */
    private ChangeListener<Worker.State> stateChangeListener() {
        return ((observable, oldValue, newValue) -> {
            final Image image;
            //显示刷新图标
            if (isComplete(newValue)) {
                image = XResource.loadImage("flush.png");
                //将当前对象设置为js window对象的成员之一
                WebEngineUtil.setMember(service.getWebEngine(), this);
            } else {
                //显示中断
                image = XResource.loadImage("cancel.png");
            }
            this.flush.setGraphic(new ImageView(image));
            this.service.state(newValue);
        });
    }

    /**
     * 检查当前连接是否下载连接
     */
    private void checkDownload(String location) {
        var future = CompletableFuture.supplyAsync(() -> XDownloadHelper.checkDownload(location));
        future.thenAccept(download -> {
            if (!download) {
                return;
            }
            PopMessageUtil.showMessage("检测到下载链接!");
        });
    }

    private Image getSEngineIcon(SearchEngine engine) {
        final String icon;
        if (engine == SearchEngine.BAIDU) {
            icon = "engine/baidu.png";
        } else {
            icon = "engine/google.png";
        }
        return XResource.loadImage(icon);
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
        this.textField.focusedProperty().removeListener(this.focusListener);
        this.engine.titleProperty().removeListener(this.titleChangeListener);
        this.engine.locationProperty().removeListener(this.locationChangeListener);
        this.engine.getLoadWorker().stateProperty().removeListener(this.stateChangeListener);
        this.engine.getHistory().currentIndexProperty().removeListener(this.indexChangeListener);
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
         * NavigationBar唯一标识
         */
        String uuid();

        /**
         * 获取{@link WebEngine}实例对象
         */
        WebEngine getWebEngine();
    }
}
