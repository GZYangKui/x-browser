package cn.navigational.xbrowser.app.util;

import javafx.application.Platform;
import javafx.geometry.Pos;
import org.controlsfx.control.Notifications;

public class PopMessageUtil {
    /**
     * 显示消息
     */
    public static void showMessage(String message) {
        Platform.runLater(() -> Notifications.create()
                .position(Pos.TOP_RIGHT)
                .text(message)
                .showInformation()
        );

    }
}
