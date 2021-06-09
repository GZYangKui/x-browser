package cn.navigational.xplayer.kit.enums;

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
        return String.format(url,keyword);
    }
}
