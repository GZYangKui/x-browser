package cn.navigational.xbrowser.app.dialog;

import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import javafx.scene.control.TextArea;
import javafx.scene.web.WebEngine;

public class WebCodeDialog extends Dialog<Void> {
    private final WebEngine engine;
    private final TextArea textArea;

    public WebCodeDialog(WebEngine engine) {
        this.engine = engine;
        this.setResizable(true);
        this.textArea = new TextArea();
        this.getDialogPane().setContent(textArea);
        this.getDialogPane().getButtonTypes().add(ButtonType.OK);
        this.initCode();
    }

    private void initCode(){
        var text = this.engine.getDocument().getTextContent();
        this.setTitle(engine.getLocation());
        this.textArea.setText(text);
    }
}
