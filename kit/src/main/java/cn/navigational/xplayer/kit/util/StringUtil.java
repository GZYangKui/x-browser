package cn.navigational.xplayer.kit.util;

public class StringUtil {
    /**
     * 判断给定字符串是否为空
     */
    public static boolean isNotEmpty(String str) {
        return str != null && str.trim().length() > 0;
    }
}
