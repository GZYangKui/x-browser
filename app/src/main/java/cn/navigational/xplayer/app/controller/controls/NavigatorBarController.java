package cn.navigational.xplayer.app.controller.controls;

import cn.navigational.xplayer.app.AbstractFXMLController;
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
    private TextField textField;

    public NavigatorBarController(NavigatorBarService service) {
        super("controls/NavigatorBar.fxml");
        service.getWebEngine().titleProperty().addListener((observable, oldValue, newValue) -> service.title(newValue));
        service.getWebEngine().locationProperty().addListener((observable, oldValue, newValue) -> {
            this.textField.setText(newValue);
            service.url(newValue);
        });
        this.back.setOnAction(event -> {
           var index =  service.getWebEngine().getHistory().getCurrentIndex();
           if (index > 0){
               service.getWebEngine().getHistory().go(-1);
           }
        });

        this.go.setOnAction(event -> {
            var index = service.getWebEngine().getHistory().getCurrentIndex();
            if (index<service.getWebEngine().getHistory().getMaxSize()){
                service.getWebEngine().getHistory().go(1);
            }
        });
    }

    public interface NavigatorBarService {
        /**
         * 后退事件触发
         */
        default void back() {

        }

        /**
         * 前进事件触发
         */
        default void go() {

        }

        /**
         * url发生改变触发
         */
        default void url(String url) {
        }

        /**
         * 网站标题发生改变时调用
         */
        default void title(String title) {

        }

        /**
         * 获取{@link WebEngine}实例对象
         */
        WebEngine getWebEngine();
    }
}
