package cn.navigational.xbrowser.app.control;

import cn.navigational.xbrowser.app.control.skin.PopupMenuSkin;
import javafx.scene.control.PopupControl;
import javafx.scene.control.Skin;

import java.util.function.Consumer;

public class PopupMenu extends PopupControl {

    private final static double DEFAULT_WIDTH = 500.0;
    private Consumer<PopupMenuAction> actionConsumer;

    public PopupMenu() {
        this.setAutoFix(true);
        this.setAutoHide(true);
        this.setWidth(DEFAULT_WIDTH);
    }

    public void setAction(Consumer<PopupMenuAction> actionConsumer) {
        this.actionConsumer = actionConsumer;
    }

    public void _action(PopupMenuAction action) {
        this.hide();
        if (this.actionConsumer == null) {
            return;
        }
        this.actionConsumer.accept(action);
    }

    @Override
    protected Skin<?> createDefaultSkin() {
        return new PopupMenuSkin(this);
    }


    public enum PopupMenuAction {
        TAG(0, 0, "tag.png", "书签"),
        HISTORY(0, 1, "history.png", "历史"),
        PROTECT_EYE(0, 2, "eye.png", "护眼"),
        VIEW_SOURCE(0, 3, "code.png", "源码"),
        BROWSER_UA(0, 4, "ua.png", "UA"),
        COLLECT(1, 0, "collect.png", "收藏"),
        DOWNLOAD(1, 1, "download.png", "下载"),
        SETTING(1, 2, "setting.png", "设置"),
        EXPOSE(1, 3, "expose.png", "嗅探"),
        EXIT(1, 4, "exit.png", "退出");

        private final int row;
        private final int column;
        private final String icon;
        private final String title;

        PopupMenuAction(int row, int column, String icon, String title) {
            this.row = row;
            this.icon = icon;
            this.title = title;
            this.column = column;
        }

        public int getRow() {
            return row;
        }

        public int getColumn() {
            return column;
        }

        public String getTitle() {
            return title;
        }

        public String getIcon() {
            return icon;
        }
    }

}
