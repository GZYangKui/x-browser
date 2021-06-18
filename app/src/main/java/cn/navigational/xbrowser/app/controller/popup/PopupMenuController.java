package cn.navigational.xbrowser.app.controller.popup;


import cn.navigational.xbrowser.app.control.PopupMenu;
import cn.navigational.xbrowser.app.controller.MainViewController;
import javafx.stage.Window;


/**
 * Popup 浮动菜单
 */
public class PopupMenuController {
    private final PopupMenu popupMenu;

    public PopupMenuController() {
        this.popupMenu = new PopupMenu();
    }

    public void show() {
        var window = MainViewController.getInstance().getStage();
        //设置居中显示
        this.popupMenu.show(window, getAnchorX(window), getAnchorY(window));
    }

    private double getAnchorY(Window window){
        var y = window.getY();
        return y+window.getHeight()*0.8;
    }

    private double getAnchorX(Window window) {
        var x = window.getX();
        var w = window.getWidth();
        var w1 = this.popupMenu.getWidth();
        return x + ((w - w1) / 2);
    }
}
