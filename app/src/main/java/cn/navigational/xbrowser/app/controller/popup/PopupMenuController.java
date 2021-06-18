package cn.navigational.xbrowser.app.controller.popup;


import cn.navigational.xbrowser.app.control.PopupMenu;
import cn.navigational.xbrowser.app.controller.MainViewController;
import cn.navigational.xbrowser.app.controller.controls.NavigatorBarController;
import cn.navigational.xbrowser.app.util.PopupMenuUtil;
import javafx.application.Platform;
import javafx.stage.Window;


/**
 * Popup 浮动菜单
 */
public class PopupMenuController {
    private final PopupMenu popupMenu;
    private final NavigatorBarController.NavigatorBarService service;

    public PopupMenuController(NavigatorBarController.NavigatorBarService service) {
        this.service = service;
        this.popupMenu = new PopupMenu();
        this.popupMenu.setAction(this::popupEvent);
    }

    /**
     * 处理菜单选中逻辑
     */
    private void popupEvent(PopupMenu.PopupMenuAction action) {
        if (action == PopupMenu.PopupMenuAction.EXIT) {
            Platform.exit();
        }
        if (action == PopupMenu.PopupMenuAction.BROWSER_UA) {
            PopupMenuUtil.setUserAgent(this.service.getWebEngine());
        }
    }

    public void show() {
        var window = MainViewController.getInstance().getStage();
        //设置居中显示
        this.popupMenu.show(window, getAnchorX(window), getAnchorY(window));
    }

    private double getAnchorY(Window window) {
        var y = window.getY();
        return y + window.getHeight() * 0.8;
    }

    private double getAnchorX(Window window) {
        var x = window.getX();
        var w = window.getWidth();
        var w1 = this.popupMenu.getWidth();
        return x + ((w - w1) / 2);
    }
}
