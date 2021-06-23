package cn.navigational.xbrowser.app.controller.popup;


import cn.navigational.xbrowser.app.control.PopupMenu;
import cn.navigational.xbrowser.app.controller.MainViewController;
import cn.navigational.xbrowser.app.controller.controls.NavigatorBarController;
import cn.navigational.xbrowser.app.util.PopupMenuUtil;
import javafx.application.Platform;


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
        if (action == PopupMenu.PopupMenuAction.PROTECT_EYE){
            PopupMenuUtil.setEyeColor(this.service.getWebEngine());
        }
        if (action == PopupMenu.PopupMenuAction.VIEW_SOURCE){
            PopupMenuUtil.viewSource(this.service.getWebEngine());
        }
    }

    /**
     * 动态调整当前菜单显示位置
     */
    public void show(double x, double y) {
        var window = MainViewController.getInstance().getStage();
        var width = window.getWidth();
        //判读当前菜单x方向是否超出当前窗口=>强制拉回窗口
        var xb = window.getX() + width;
        if (width + x > xb) {
            x = xb - this.popupMenu.getWidth();
        }
        this.popupMenu.show(window, x, y);
    }
}
