package cn.navigational.xplayer.app.controller;

import cn.navigational.xplayer.app.AbstractWindowController;
import cn.navigational.xplayer.app.controller.controls.NavigatorBarController;
import javafx.fxml.FXML;
import javafx.scene.layout.BorderPane;
import javafx.scene.web.WebEngine;
import javafx.scene.web.WebView;

/**
 * 主界面视图
 */
public class MainViewController extends AbstractWindowController<BorderPane> implements NavigatorBarController.NavigatorBarService {
    @FXML
    private WebView webView;
    @FXML
    private final WebEngine webEngine;

    private final NavigatorBarController navigatorBarController;

    public MainViewController() {
        super("MainView.fxml");
        this.webEngine = webView.getEngine();
        this.getStage().setTitle("x-browser");
        this.webEngine.load("https://www.baidu.com");
        this.navigatorBarController = new NavigatorBarController(this);
        this.getParent().setTop(this.navigatorBarController.getParent());
    }

    @Override
    public void title(String title) {
        this.getStage().setTitle(title);
    }


    @Override
    public WebEngine getWebEngine() {
        return this.webEngine;
    }
}
