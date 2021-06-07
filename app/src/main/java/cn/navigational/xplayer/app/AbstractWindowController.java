package cn.navigational.xplayer.app;

import cn.navigational.xplayer.app.assets.XPlayerResource;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.net.URL;


public class AbstractWindowController<T extends Parent> extends AbstractFXMLController<T> {
    private final Stage stage;
    private final Scene scene;

    public AbstractWindowController(URL fxmlURL) {
        super(fxmlURL);
        this.scene = new Scene(this.getParent());
        this.stage = new Stage();
        this.stage.setScene(this.scene);
        this.stage.setOnCloseRequest(this::onCloseRequest);
    }

    public AbstractWindowController(String fxml){
        this(XPlayerResource.class.getResource("fxml/"+fxml));
    }

    public Scene getScene() {
        return scene;
    }

    public Stage getStage() {
        return stage;
    }

    /**
     * 当前窗口关闭时调用当前函数
     */
    protected void onCloseRequest(WindowEvent event) {

    }
}
