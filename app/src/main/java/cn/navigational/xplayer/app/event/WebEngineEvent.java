package cn.navigational.xplayer.app.event;

import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.TextInputDialog;
import javafx.scene.web.PromptData;
import javafx.scene.web.WebEngine;
import javafx.scene.web.WebErrorEvent;
import javafx.scene.web.WebEvent;

import java.util.Optional;

/**
 * 注册{@link WebEngine}常用事件
 */
public class WebEngineEvent {
    private final WebEngine engine;

    private WebEngineEvent(WebEngine engine) {
        this.engine = engine;
        this.engine.setOnAlert(this::onAlert);
        this.engine.setOnError(this::onError);
        this.engine.setPromptHandler(this::prompt);
        this.engine.setConfirmHandler(this::confirm);

    }

    /**
     * <code>
     * alert("hello,word")";
     * </code>
     */
    private void onAlert(WebEvent<String> event) {
        var alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setContentText(event.getData());
        alert.showAndWait();
    }

    /**
     * <code>
     * confirm("hello,word")"
     * </code>
     */
    private boolean confirm(String message) {
        var alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setContentText(message);
        var optional = alert.showAndWait();
        return !(optional.isEmpty() || optional.get() != ButtonType.OK);
    }

    /**
     * <code>
     * prompt("hello,word")
     * </code>
     */
    private String prompt(PromptData data) {
        var alert = new TextInputDialog();
        var title = Optional.ofNullable(data.getMessage()).orElse(data.getMessage());
        alert.setTitle(title);
        return alert.showAndWait().orElse(null);
    }

    private void onError(WebErrorEvent event) {
        event.getException().printStackTrace();
    }


    public static WebEngineEvent create(WebEngine engine) {
        return new WebEngineEvent(engine);
    }

}
