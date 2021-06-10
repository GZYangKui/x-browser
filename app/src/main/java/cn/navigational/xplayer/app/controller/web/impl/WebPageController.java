package cn.navigational.xplayer.app.controller.web.impl;

import cn.navigational.xplayer.app.controller.web.AbstractWebPageController;


public class WebPageController extends AbstractWebPageController {
    public WebPageController() {
        this.getWebEngine().load("https://baidu.com");
    }
}
