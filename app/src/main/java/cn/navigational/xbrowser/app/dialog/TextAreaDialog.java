package cn.navigational.xbrowser.app.dialog;

import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import javafx.scene.control.TextArea;
import javafx.util.Callback;

public class TextAreaDialog extends Dialog<String> {
    private final TextArea textArea;

    public TextAreaDialog() {
        this.setResizable(true);
        this.textArea = new TextArea();
        this.textArea.setWrapText(true);
        this.getDialogPane().setContent(textArea);
        this.setResultConverter(this.resultConvert());
        this.getDialogPane().getButtonTypes().addAll(ButtonType.CANCEL, ButtonType.OK);

    }

    /**
     * 处理用户点击确定/取消以及X-WINDOW处理逻辑
     */
    private Callback<ButtonType, String> resultConvert() {
        return btn -> {
            if (btn == null || btn == ButtonType.CANCEL) {
                return null;
            }
            return this.textArea.getText();
        };
    }

}
