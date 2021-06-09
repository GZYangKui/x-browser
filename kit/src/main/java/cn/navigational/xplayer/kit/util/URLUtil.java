package cn.navigational.xplayer.kit.util;

import cn.navigational.xplayer.kit.enums.SearchEngine;

import java.util.regex.Pattern;

public class URLUtil {
    private static final Pattern URL_PATTERN = Pattern.compile("^(((file|gopher|news|nntp|telnet|http|ftp|https|ftps|sftp)://)?|(www\\.))+(([a-zA-Z0-9\\._-]+\\.[a-zA-Z]{2,6})|([0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}))(/[a-zA-Z0-9\\&%_\\./-~-]*)?$");


    /**
     * 判断给定的字符串是否正确的网址url
     */
    public static boolean isUrl(String str) {
        var matcher = URL_PATTERN.matcher(str);
        return matcher.find();
    }


    public static String getUrl(SearchEngine engine,String str){
        final String url;
        if (isUrl(str)){
            url =  str;
        }else {
            url = engine.getUrl(str);
        }
        return url;
    }

}
