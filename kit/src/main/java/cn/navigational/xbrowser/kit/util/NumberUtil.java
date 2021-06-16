package cn.navigational.xbrowser.kit.util;

import java.math.BigDecimal;
import java.math.RoundingMode;

public class NumberUtil {
    /**
     * 默认四舍五入
     */
    public static double divide(long a, long b) {
        return divide(a, b, RoundingMode.HALF_UP);
    }

    /**
     * 两个数相除
     */
    public static double divide(long a, long b, RoundingMode model) {
        var aa = new BigDecimal(a);
        var bb = new BigDecimal(b);
        return aa.divide(bb, model).doubleValue();
    }

    /**
     * 将字节转换为MB
     */
    public static double byteToMB(long len) {
        return divide(len, 1024 * 1024);
    }
}
