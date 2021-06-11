package cn.navigational.xbrowser.kit;

public interface Closeable {
    /**
     * 自定义实现资源释放
     */
    default void dispose() {

    }

    /**
     * 尝试关闭传入对象
     */
    static void tryClose(Object obj) {
        if (!(obj instanceof Closeable)) {
            return;
        }
        ((Closeable) obj).dispose();
    }
}
