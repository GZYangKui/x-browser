package cn.navigational.xplayer.app;

import cn.navigational.xplayer.app.assets.XPlayerResource;
import javafx.application.Platform;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.net.URL;


public class AbstractWindowController<T extends Parent> extends AbstractFXMLController<T> {
    private final Stage stage;
    private final Scene scene;

    public AbstractWindowController(String fxml) {
        super(fxml);
        this.scene = new Scene(this.getParent());
        this.stage = new Stage();
        this.stage.setScene(this.scene);
        this.stage.setOnCloseRequest(this::onCloseRequest);
    }

    public Scene getScene() {
        return scene;
    }

    public Stage getStage() {
        return stage;
    }

    public void openWindow() {
        Platform.runLater(() -> {
            this.stage.show();
            this.stage.toFront();
        });
    }

    /**
     * 当前窗口关闭时调用当前函数
     */
    protected void onCloseRequest(WindowEvent event) {

    }
}
