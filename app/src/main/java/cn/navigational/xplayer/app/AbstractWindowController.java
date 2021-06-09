package cn.navigational.xplayer.app;

import cn.navigational.xplayer.app.assets.XPlayerResource;
import javafx.application.Platform;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Screen;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;


public class AbstractWindowController<T extends Parent> extends AbstractFXMLController<T> {
    private final Stage stage;
    private final Scene scene;

    public AbstractWindowController(String fxml) {
        super(fxml);
        this.scene = new Scene(this.getParent());
        this.stage = new Stage();
        this.stage.setScene(this.scene);
        this.stage.setOnCloseRequest(this::onCloseRequest);
        this.stage.getIcons().add(XPlayerResource.loadImage("icon.png"));
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
     * 根据屏幕尺寸按照比例设置窗口大小
     */
    protected void setSizeByProp(double wProp, double hProp) {
        var screen = Screen.getPrimary();
        var rect = screen.getVisualBounds();
        var width = Math.floor(rect.getWidth() * wProp);
        var height = Math.floor(rect.getHeight() * hProp);
        this.stage.setWidth(width);
        this.stage.setHeight(height);
    }

    /**
     * 当前窗口关闭时调用当前函数
     */
    protected void onCloseRequest(WindowEvent event) {

    }
}
