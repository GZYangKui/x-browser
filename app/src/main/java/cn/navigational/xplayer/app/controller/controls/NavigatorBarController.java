package cn.navigational.xplayer.app.controller.controls;

import cn.navigational.xplayer.app.AbstractFXMLController;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.web.WebEngine;


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
    private TextField textField;

    private final WebEngine engine;
    private final NavigatorBarService service;

    public NavigatorBarController(NavigatorBarService service) {
        super("controls/NavigatorBar.fxml");
        this.service = service;
        this.engine = service.getWebEngine();
        this.init();
    }

    /**
     * 初始化浏览器事件
     */
    private void init() {
        this.back.setOnAction(event -> {
            this.service.back(event);
            if (event.isConsumed()) {
                return;
            }
            if (getCurrentIndex() <= 0) {
                return;
            }
            engine.getHistory().go(-1);
        });

        this.flush.setOnAction(event -> {
            this.service.flush(event);
            if (event.isConsumed()) {
                return;
            }
            engine.reload();
        });

        this.go.setOnAction(event -> {
            service.go(event);
            if (event.isConsumed()) {
                return;
            }
            var max = engine.getHistory().getEntries().size();
            if (getCurrentIndex() < max - 1) {
                service.getWebEngine().getHistory().go(1);
            }
        });
        this.textField.focusedProperty().addListener((observable, oldValue, newValue) -> {
            var styleClass = this.inputBox.getStyleClass();
            if (!newValue) {
                styleClass.remove("input-box-active");
                return;
            }
            var contain = styleClass.contains("input-box-active");
            if (!contain) {
                styleClass.add("input-box-active");
            }
        });
        engine.titleProperty().addListener((observable, oldValue, newValue) -> service.title(newValue));
        engine.locationProperty().addListener((observable, oldValue, newValue) -> {
            this.textField.setText(newValue);
            service.url(newValue);
        });
        engine.getLoadWorker().progressProperty().addListener((observable, oldValue, newValue) -> this.service.progress(newValue.doubleValue()));
    }

    private int getCurrentIndex() {
        var history = engine.getHistory();
        return history.getCurrentIndex();
    }

    public interface NavigatorBarService {
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
         * 获取{@link WebEngine}实例对象
         */
        WebEngine getWebEngine();
    }
}
