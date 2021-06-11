package cn.navigational.xbrowser.kit.enums;

import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;

public enum SearchEngine {
    BAIDU("https://www.baidu.com/s?ie=UTF-8&wd=%s", "百度"),
    GOOGLE("https://www.google.com/search?q=%s&ie=UTF-8","谷歌");

    private final String url;
    private final String title;

    SearchEngine(String url, String title) {
        this.url = url;
        this.title = title;
    }

    public String getTitle() {
        return title;
    }

    public String getUrl(String keyword) {
        keyword = URLEncoder.encode(keyword, StandardCharsets.UTF_8);
        return String.format(url,keyword);
    }
}
