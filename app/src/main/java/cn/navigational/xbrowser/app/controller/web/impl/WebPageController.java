package cn.navigational.xbrowser.app.controller.web.impl;

import cn.navigational.xbrowser.app.controller.web.AbstractWebPageController;

import java.io.File;
import java.net.URL;


public class WebPageController extends AbstractWebPageController {
    private static final File INDEX = new File("web/html/index.html");
    public WebPageController() {
        this.getWebEngine().load(INDEX.toURI().toString());
    }
}
