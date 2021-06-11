package cn.navigational.xbrowser.kit.util;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class StringUtil {

    /**
     * 判断给定字符串是否为空
     */
    public static boolean isNotEmpty(String str) {
        return str != null && str.trim().length() > 0;
    }

    /**
     * 判断给定字符串是否为空
     */
    public static boolean isEmpty(String str){
        return !isNotEmpty(str);
    }

}
