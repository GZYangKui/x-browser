package cn.navigational.xbrowser.app.dialog;

import cn.navigational.xbrowser.app.assets.XResource;
import javafx.scene.Node;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import javafx.scene.control.Label;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

import java.util.Arrays;

public class EyeColorDialog extends Dialog<EyeColorDialog.Colors> {

    private static final String STYLE_SHEETS = XResource.class.getResource("css/dialog/EyeDialogStyle.css").toExternalForm();

    private Colors color;

    private GridPane gridPane;


    public EyeColorDialog() {
        this.color = Colors.ZERO;
        this.init();
        this.getDialogPane().requestFocus();
        this.getDialogPane().getStylesheets().add(STYLE_SHEETS);
        this.getDialogPane().getButtonTypes().addAll(ButtonType.OK, ButtonType.CANCEL);

        this.setResultConverter((btn)->{
            if (btn == null || btn == ButtonType.CANCEL){
                return Colors.ZERO;
            }
            return color;
        });
    }

    private void init() {
        this.gridPane = new GridPane();
        this.gridPane.getStyleClass().add("grid-pane");
        Arrays.stream(Colors.values())
                .map(ColorBox::new)
                .forEach(box -> this.gridPane.add(box, box.getColor().getColumn(), box.getColor().getRow()));
        this.getDialogPane().setContent(this.gridPane);
    }

    private class ColorBox extends VBox {
        private final Label label;
        private final Colors color;
        private final Rectangle rectangle;

        private static final String DEFAULT_CLASS_STYLE = "color-box";
        private static final String DEFAULT_SELECT_STYLE = "select-box";

        public ColorBox(Colors color) {
            this.color = color;
            this.label = new Label(color.getTitle());

            this.rectangle = new Rectangle();
            this.rectangle.setWidth(100);
            this.rectangle.setHeight(100);
            this.rectangle.setFill(color.getColor());

            this.getChildren().addAll(rectangle, label);
            this.getStyleClass().add(DEFAULT_CLASS_STYLE);

            //设置默认选中
            if (color == EyeColorDialog.this.color){
                this.getStyleClass().add(DEFAULT_SELECT_STYLE);
            }

            this.rectangle.setOnMouseClicked(event -> {
                var children = EyeColorDialog.this.gridPane.getChildren();
                for (Node child : children) {
                    if (child == this) {
                        EyeColorDialog.this.color = this.color;
                        child.getStyleClass().add(DEFAULT_SELECT_STYLE);
                    } else {
                        child.getStyleClass().removeAll(DEFAULT_SELECT_STYLE);
                    }
                }
            });
        }

        public Colors getColor() {
            return color;
        }

        public Label getLabel() {
            return label;
        }

        public Rectangle getRectangle() {
            return rectangle;
        }
    }


    public enum Colors {

        ZERO(Color.GRAY, "WEB", 0, 0),
        A(Color.web("#acd579"), "益眼绿", 0, 1),
        B(Color.web("#acd579"), "搜啥绿", 0, 2),
        C(Color.web("#f0e78c"), "鹅蛋黄", 0, 3),
        D(Color.web("#f0e78c"), "海天蓝", 1, 0),
        E(Color.web("#f0f5f9"), "米白色", 1, 1),
        F(Color.web("#fff7fc"), "雅嫩粉", 1, 2),
        G(Color.web("#fff7fc"), "咸蛋黄", 1, 3);

        private final Color color;
        private final String title;

        private final int row;
        private final int column;

        Colors(Color color, String title, int row, int column) {
            this.color = color;
            this.title = title;
            this.row = row;
            this.column = column;
        }

        public Color getColor() {
            return color;
        }

        public String getTitle() {
            return title;
        }

        public int getRow() {
            return row;
        }

        public int getColumn() {
            return column;
        }
    }
}
