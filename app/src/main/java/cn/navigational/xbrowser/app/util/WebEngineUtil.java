package cn.navigational.xbrowser.app.util;

import javafx.scene.web.WebEngine;
import netscape.javascript.JSObject;

public class WebEngineUtil {
    /**
     * 将java对象挂在到 JS 的window对象中 实现js调用java方法
     */
    public static void setMember(WebEngine engine, Object javaObject) {
        JSObject window = (JSObject) engine.executeScript("window");
        window.setMember("xBrowser", javaObject);
    }
}
