package cn.navigational.xbrowser.kit.util;

import cn.navigational.xbrowser.kit.enums.SearchEngine;

import java.net.URI;
import java.util.regex.Pattern;

public class LocationUtil {
    /**
     * 判断当前location是否http/https连接地址
     */
    private static boolean tryConvert(String str) {
        var uri = URI.create(str);
        return !StringUtil.isEmpty(uri.getScheme())
                &&
                !StringUtil.isEmpty(uri.getHost());
    }

    /**
     * 如果当前连接地址不是标准Http、Https连接地址,则生成搜索引擎地址
     */
    public static String getUrl(SearchEngine engine, String str) {
        if (!tryConvert(str)) {
            str = engine.getUrl(str);
        }
        return str;
    }

}
