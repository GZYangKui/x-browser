package cn.navigational.xbrowser.app.util;

import cn.navigational.xbrowser.app.dialog.EyeColorDialog;
import cn.navigational.xbrowser.app.dialog.TextAreaDialog;
import javafx.scene.web.WebEngine;

public class PopupMenuUtil {
    /**
     * 设置浏览器User-Agent
     */
    public static void setUserAgent(WebEngine engine) {
        var dialog = new TextAreaDialog(engine.getUserAgent());
        dialog.setTitle("User-Agent");
        dialog.setHeaderText("请输入正确User-Agent格式,否则网络可能无法请求.");
        dialog.showAndWait().ifPresent(engine::setUserAgent);
    }

    public static void setEyeColor(WebEngine engine){
        var dialog = new EyeColorDialog();
        var optional = dialog.showAndWait();
        if (optional.isPresent()){
            //todo 改变网页背景色

        }
    }
}
