package cn.navigational.xplayer.app.controller.web;

import cn.navigational.xplayer.app.controller.controls.NavigatorBarController;
import cn.navigational.xplayer.app.event.WebEngineEvent;
import javafx.concurrent.Worker;

import javafx.scene.control.ProgressIndicator;
import javafx.scene.control.Tab;
import javafx.scene.layout.BorderPane;
import javafx.scene.web.WebEngine;
import javafx.scene.web.WebView;

public abstract class AbstractWebPageController implements NavigatorBarController.NavigatorBarService {
    private final Tab tab;
    private final WebEngine engine;
    private final NavigatorBarController navigatorBarController;

    public AbstractWebPageController() {
        var webView = new WebView();
        this.engine = webView.getEngine();
        this.navigatorBarController = new NavigatorBarController(this);

        var root = new BorderPane();
        root.setCenter(webView);
        root.setTop(this.navigatorBarController.getParent());

        WebEngineEvent.create(this.engine);

        this.tab = new Tab();
        this.tab.setContent(root);
        this.tab.getStyleClass().add("web-tab");
        this.tab.setOnCloseRequest(event -> this.dispose());
    }


    public Tab getTab() {
        return tab;
    }

    @Override
    public WebEngine getWebEngine() {
        return this.engine;
    }

    @Override
    public void state(Worker.State state) {
        var complete = this.navigatorBarController.isComplete(state);
        if (complete) {
            this.tab.setGraphic(null);
        } else {
            var indicator = new ProgressIndicator();
            indicator.setPrefSize(10, 10);
            this.tab.setGraphic(new ProgressIndicator());
        }
    }

    @Override
    public void title(String title) {
        this.tab.setText(title);
    }


    @Override
    public void dispose() {
        this.navigatorBarController.dispose();
    }
}
