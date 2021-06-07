package cn.navigational.xplayer.app.controller;

import cn.navigational.xplayer.app.AbstractFXMLController;
import cn.navigational.xplayer.app.AbstractWindowController;
import javafx.scene.layout.BorderPane;

/**
 * 主界面视图
 */
public class MainViewController extends AbstractWindowController<BorderPane> {
    public MainViewController() {
        super("MainView.fxml");
        this.getStage().show();
    }
}
