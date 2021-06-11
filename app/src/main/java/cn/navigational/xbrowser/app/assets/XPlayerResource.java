package cn.navigational.xbrowser.app.assets;

import javafx.scene.image.Image;

import java.io.IOException;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.ConcurrentHashMap;

public class XPlayerResource {
    private static final String BASE_IMG_PATH = "img/";

    /**
     * 缓存图片资源
     */
    private static final Map<String, Image> IMG_CACHED = new ConcurrentHashMap<>();

    /**
     * 程序全局样式
     */
    public static final String APP_STYLE = Objects
            .requireNonNull(XPlayerResource.class.getResource("css/Application.css"))
            .toExternalForm();

    /**
     * 加载jar内部图片资源
     */
    public static Image loadImage(String path) {
        var key = BASE_IMG_PATH + path;
        var img = IMG_CACHED.get(key);
        if (img != null) {
            return img;
        }
        var url = XPlayerResource.class.getResource(key);
        try {
            assert url != null;
            img = new Image(url.openStream());
            IMG_CACHED.put(key, img);
            return img;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
