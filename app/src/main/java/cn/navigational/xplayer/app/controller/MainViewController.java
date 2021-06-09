package cn.navigational.xplayer.app.controller;

import cn.navigational.xplayer.app.AbstractWindowController;
import cn.navigational.xplayer.app.assets.XPlayerResource;
import cn.navigational.xplayer.app.controller.controls.NavigatorBarController;
import cn.navigational.xplayer.app.event.WebEngineEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.layout.BorderPane;
import javafx.scene.web.WebEngine;
import javafx.scene.web.WebView;

/**
 * 主界面视图
 */
public class MainViewController extends AbstractWindowController<BorderPane> implements NavigatorBarController.NavigatorBarService {
    @FXML
    private Label proText;
    @FXML
    private WebView webView;
    @FXML
    private ProgressBar progress;

    private final WebEngine webEngine;

    private final NavigatorBarController navigatorBarController;

    public MainViewController() {
        super("MainView.fxml");
        this.webEngine = webView.getEngine();
        this.getStage().setTitle("x-browser");
        this.setSizeByProp(0.7,0.8);
        this.webEngine.load("https://www.baidu.com");
        WebEngineEvent.create(this.webEngine);
        this.navigatorBarController = new NavigatorBarController(this);
        this.getParent().setTop(this.navigatorBarController.getParent());
    }

    @Override
    public void title(String title) {
        this.getStage().setTitle(title);
    }

    @Override
    public void progress(double value) {
        this.progress.setProgress(value);
        this.proText.setText(Math.floor(value*100) +"%");
    }

    @Override
    public WebEngine getWebEngine() {
        return this.webEngine;
    }
}
