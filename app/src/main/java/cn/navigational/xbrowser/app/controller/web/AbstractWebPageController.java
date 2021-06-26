package cn.navigational.xbrowser.app.controller.web;

import cn.navigational.xbrowser.app.controller.MainViewController;
import cn.navigational.xbrowser.app.controller.WebSourceCodeViewController;
import cn.navigational.xbrowser.app.controller.controls.NavigatorBarController;
import cn.navigational.xbrowser.app.controller.popup.PopupMenuController;
import cn.navigational.xbrowser.app.event.WebEngineEvent;
import cn.navigational.xbrowser.app.util.ImageUtil;
import javafx.application.Platform;
import javafx.concurrent.Worker;

import javafx.scene.control.ProgressIndicator;
import javafx.scene.control.Tab;
import javafx.scene.control.Tooltip;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.web.WebEngine;
import javafx.scene.web.WebView;

import java.util.UUID;


public abstract class AbstractWebPageController implements NavigatorBarController.NavigatorBarService {
    private final Tab tab;
    private final String uuid;
    private final WebEngine engine;
    private final NavigatorBarController navigatorBarController;

    public AbstractWebPageController() {
        var webView = new WebView();
        this.engine = webView.getEngine();
        this.uuid = UUID.randomUUID().toString();
        this.navigatorBarController = new NavigatorBarController(this);

        var root = new BorderPane();
        root.setCenter(webView);
        root.setTop(this.navigatorBarController.getParent());

        WebEngineEvent.create(this.engine);

        this.tab = new Tab();
        this.tab.setContent(root);
        this.tab.setUserData(this);
        this.tab.getStyleClass().add("web-tab");
        this.tab.setOnCloseRequest(event -> this.dispose());
    }


    public Tab getTab() {
        return tab;
    }

    /**
     * 获取当前网页标题
     */
    public String getTitle() {
        return this.engine.getTitle();
    }

    @Override
    public WebEngine getWebEngine() {
        return this.engine;
    }

    @Override
    public void state(Worker.State state) {
        var complete = this.navigatorBarController.isComplete(state);
        if (complete) {
            this.loadNetFavicon();
        } else {
            var indicator = new ProgressIndicator();
            indicator.setPrefSize(10, 10);
            this.tab.setGraphic(new ProgressIndicator());
        }
    }

    /**
     * 加载网站favicon图标
     */
    private void loadNetFavicon() {
        var optional = this.navigatorBarController.getLocation();
        if (optional.isEmpty()) {
            this.tab.setGraphic(new ImageView(ImageUtil.DEFAULT_FAVICON));
            return;
        }
        var str = optional.get().favicon();
        ImageUtil.loadNetFav(str).whenComplete((rs, t) -> {
            if (t != null) {
                rs = ImageUtil.DEFAULT_FAVICON;
            }
            var favicon = new ImageView(rs);
            Platform.runLater(() -> this.tab.setGraphic(favicon));
        });
    }

    @Override
    public void title(String title) {
        this.tab.setText(title);
        MainViewController.getInstance().updateTitle(title, this.tab);
    }

    @Override
    public void url(String url) {
        var optional = this.navigatorBarController.getLocation();
        if (optional.isEmpty()) {
            return;
        }
        this.tab.setTooltip(new Tooltip(optional.get().getHost()));
    }

    @Override
    public String uuid() {
        return this.uuid;
    }

    @Override
    public void dispose() {
        this.tab.setUserData(null);
        this.engine.getLoadWorker().cancel();
        this.engine.load(null);
        this.navigatorBarController.dispose();
        //尝试关闭对应的源码视图页面
        WebSourceCodeViewController.tryCloseController(this.uuid);
    }
}
