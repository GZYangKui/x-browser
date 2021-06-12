package cn.navigational.xbrowser.app.util;

import cn.navigational.xbrowser.app.assets.XResource;
import cn.navigational.xbrowser.kit.util.HttpUtil;
import javafx.embed.swing.SwingFXUtils;
import javafx.scene.image.Image;
import net.sf.image4j.codec.ico.ICODecoder;

import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.net.http.HttpResponse;
import java.util.concurrent.CompletableFuture;
import java.util.logging.Logger;

public class ImageUtil {

    private static final Logger LOG = Logger.getLogger(ImageUtil.class.getName());
    /**
     * 默认网站favicon图标
     */
    public static final Image DEFAULT_FAVICON = XResource.loadImage("favicon.png");

    /**
     * 加载网站favicon图标
     */
    public static CompletableFuture<Image> loadNetFav(String favicon) {
        return CompletableFuture.supplyAsync(() -> {
            var optional = HttpUtil.doGet(favicon, HttpResponse.BodyHandlers.ofByteArray());
            var image = DEFAULT_FAVICON;
            if (optional.isEmpty()) {
                return image;
            }
            var in = new ByteArrayInputStream(optional.get());
            try {
                var list = ICODecoder.read(in);
                if (!list.isEmpty()) {
                    var bufferImage = resize(list.get(0), 20, 20);
                    image = SwingFXUtils.toFXImage(bufferImage, null);
                }
            } catch (IOException e) {
                e.printStackTrace();
                LOG.info("ico image decoder happen error:" + e.getMessage());
            }
            return image;
        });
    }

    /**
     * 调整{@link BufferedImage} 图像尺寸
     */
    public static BufferedImage resize(BufferedImage img, int width, int height) {
        var tmp = img.getScaledInstance(
                width,
                height,
                java.awt.Image.SCALE_SMOOTH
        );
        var dImage = new BufferedImage(
                width,
                height,
                BufferedImage.TYPE_INT_ARGB
        );

        var g2d = dImage.createGraphics();
        g2d.drawImage(tmp, 0, 0, null);
        g2d.dispose();

        return dImage;
    }
}
