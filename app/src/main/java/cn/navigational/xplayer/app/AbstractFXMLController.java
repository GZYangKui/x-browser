package cn.navigational.xplayer.app;

import cn.navigational.xplayer.app.assets.XPlayerResource;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;

import java.io.IOException;
import java.net.URL;

public class AbstractFXMLController<T extends Parent> {
    private T parent;
    private final URL fxmlURL;

    public AbstractFXMLController(URL fxmlURL) {
        this.fxmlURL = fxmlURL;
    }

    public AbstractFXMLController(String fxml){
       this(XPlayerResource.class.getResource("fxml/"+fxml));
    }

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
