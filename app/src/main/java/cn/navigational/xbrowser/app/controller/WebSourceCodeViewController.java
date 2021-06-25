package cn.navigational.xbrowser.app.controller;

import cn.navigational.xbrowser.app.AbstractWindowController;
import cn.navigational.xbrowser.app.controller.controls.NavigatorBarController;
import cn.navigational.xbrowser.kit.util.XMLUtil;
import javafx.beans.value.ChangeListener;
import javafx.fxml.FXML;
import javafx.scene.control.TextArea;
import javafx.scene.layout.BorderPane;
import javafx.stage.WindowEvent;
import org.w3c.dom.Document;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Web站点源码查看窗口
 */
public class WebSourceCodeViewController extends AbstractWindowController<BorderPane> {
    @FXML
    private TextArea textArea;

    private final NavigatorBarController.NavigatorBarService service;

    private final ChangeListener<String> locationListener = ((observable, oldValue, newValue) -> this.setTitle(newValue));

    private final ChangeListener<Document> documentListener = (observable, oldValue, newValue) -> this.initHtmlDocument(newValue);

    private WebSourceCodeViewController(NavigatorBarController.NavigatorBarService service) {
        super("WebSourceCodeView.fxml");
        this.service = service;
        this.setSizeByProp(0.8, 0.8);
        this.initHtmlDocument(this.service.getWebEngine().getDocument());
        this.getStage().setTitle("Dev-Tools - " + service.getWebEngine().getLocation());
        this.service.getWebEngine().documentProperty().addListener(this.documentListener);
        this.service.getWebEngine().locationProperty().addListener(this.locationListener);
    }

    /**
     * 获取html文档并显示到{@link TextArea}上
     */
    private void initHtmlDocument(Document document) {
        if (document == null) {
            this.textArea.setText(null);
            return;
        }
        var html = (String) service
                .getWebEngine().executeScript("document.documentElement.outerHTML");
        this.textArea.setText(html);
    }


    private void setTitle(String location) {
        this.getStage().setTitle("DevTools - " + location);
    }

    @Override
    protected void onCloseRequest(WindowEvent event) {
        super.onCloseRequest(event);
        CONTROLLERS.remove(this.service.uuid());
    }

    @Override
    public void dispose() {
        this.service.getWebEngine().locationProperty().removeListener(this.locationListener);
        this.service.getWebEngine().documentProperty().removeListener(this.documentListener);
    }

    private static final Map<String, WebSourceCodeViewController> CONTROLLERS = new ConcurrentHashMap<>();

    /**
     * 尝试新建源码查看视图,
     * 如果当前{@link cn.navigational.xbrowser.app.controller.controls.NavigatorBarController.NavigatorBarService}对应视图存在取消新建
     * </p>
     */
    public static void tryNewController(NavigatorBarController.NavigatorBarService service) {
        var controller = CONTROLLERS.get(service.uuid());
        if (controller == null) {
            controller = new WebSourceCodeViewController(service);
            CONTROLLERS.put(service.uuid(), controller);
        }
        controller.openWindow();
    }

    /**
     * 外部调用关闭目标源码视图
     */
    public static void tryCloseController(String uuid) {
        var controller = CONTROLLERS.remove(uuid);
        if (controller == null) {
            return;
        }
        controller.getStage().close();
        controller.dispose();
    }
}
