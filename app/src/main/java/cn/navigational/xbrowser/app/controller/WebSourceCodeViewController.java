package cn.navigational.xbrowser.app.controller;

import cn.navigational.xbrowser.app.AbstractWindowController;
import cn.navigational.xbrowser.app.controller.controls.NavigatorBarController;
import javafx.beans.value.ChangeListener;
import javafx.scene.layout.BorderPane;
import javafx.stage.WindowEvent;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Web站点源码查看窗口
 */
public class WebSourceCodeViewController extends AbstractWindowController<BorderPane> {

    private final NavigatorBarController.NavigatorBarService service;

    private final ChangeListener<String> locationListener = ((observable, oldValue, newValue) -> {
        this.getStage().setTitle("DevTools - "+newValue);
    });

    private WebSourceCodeViewController(NavigatorBarController.NavigatorBarService service) {
        super("WebSourceCodeView.fxml");
        this.service = service;
        this.setSizeByProp(0.8, 0.8);
        this.getStage().setTitle("Dev-Tools - "+service.getWebEngine().getLocation());
        this.service.getWebEngine().locationProperty().addListener(this.locationListener);
    }

    @Override
    protected void onCloseRequest(WindowEvent event) {
        super.onCloseRequest(event);
        CONTROLLERS.remove(this.service.uuid());
    }

    @Override
    public void dispose() {
        this.service.getWebEngine().locationProperty().removeListener(this.locationListener);
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
