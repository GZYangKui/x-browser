package cn.navigational.xbrowser.app;

import cn.navigational.xbrowser.app.assets.XPlayerResource;
import cn.navigational.xbrowser.kit.Closeable;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;

import java.io.IOException;
import java.net.URL;

public class AbstractFXMLController<T extends Parent> implements Closeable {
    private T parent;
    private final URL fxmlURL;

    public AbstractFXMLController(URL fxmlURL) {
        this.fxmlURL = fxmlURL;
        this.parent = getParent();
    }

    public AbstractFXMLController(String fxml) {
        this(XPlayerResource.class.getResource("fxml/" + fxml));
    }

    /**
     * 子类可以根据需求自定义覆盖实现获取{@link Parent}
     */
    public synchronized T getParent() {
        if (parent == null) {
            this.parent = loadFXMLView(this.fxmlURL, this);
        }
        return this.parent;
    }

    public static <K extends Parent> K loadFXMLView(URL fxmlURL, Object controller) {
        var fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(fxmlURL);
        fxmlLoader.setController(controller);
        try {
            return fxmlLoader.load();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

}
