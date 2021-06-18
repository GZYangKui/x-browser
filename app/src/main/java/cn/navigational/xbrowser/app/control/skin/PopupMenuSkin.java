package cn.navigational.xbrowser.app.control.skin;

import cn.navigational.xbrowser.app.AbstractFXMLController;
import cn.navigational.xbrowser.app.assets.XResource;
import cn.navigational.xbrowser.app.control.PopupMenu;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.ContentDisplay;
import javafx.scene.control.Skin;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;



public class PopupMenuSkin implements Skin<PopupMenu> {

    private final GridPane gridPane;
    private final PopupMenu popupMenu;

    private static final String POPUP_STYLE = XResource.class.getResource("css/controls/PopupMenuStyle.css").toExternalForm();


    public PopupMenuSkin(PopupMenu popupMenu) {
        this.popupMenu = popupMenu;
        this.gridPane = new GridPane();
        this.gridPane.getStyleClass().add("popup-menu");
        this.gridPane.getStylesheets().add(POPUP_STYLE);
        for (PopupMenu.PopupMenuAction value : PopupMenu.PopupMenuAction.values()) {
            var button = new Button(value.getTitle());
            var image = XResource.loadImage("menu/" + value.getIcon());
            button.setGraphic(new ImageView(image));
            button.setContentDisplay(ContentDisplay.TOP);
            this.gridPane.add(button,value.getColumn(),value.getRow());
        }
    }

    @Override
    public Node getNode() {
        return this.gridPane;
    }

    @Override
    public void dispose() {

    }

    @Override
    public PopupMenu getSkinnable() {
        return this.popupMenu;
    }
}
