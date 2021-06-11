package cn.navigational.xbrowser.app.controller;

import cn.navigational.xbrowser.app.AbstractWindowController;
import cn.navigational.xbrowser.app.controller.web.AbstractWebPageController;
import cn.navigational.xbrowser.app.controller.web.impl.WebPageController;
import javafx.beans.value.ChangeListener;
import javafx.fxml.FXML;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.layout.BorderPane;


/**
 * 主界面视图
 */
public class MainViewController extends AbstractWindowController<BorderPane> {
    @FXML
    private TabPane tabPane;

    private MainViewController() {
        super("MainView.fxml");
        this.getStage().setTitle("x-browser");
        this.setSizeByProp(0.7, 0.8);
        this.tabPane.getSelectionModel().selectedItemProperty().addListener(this.tabSelectChangeListener());
        this.tabPane.getTabs().add(new WebPageController().getTab());
    }

    private ChangeListener<Tab> tabSelectChangeListener() {
        return (observable, oldValue, newValue) -> {
//            var userData = newValue.getUserData();
//            if (!(userData instanceof WebPageController)){
//                return;
//            }
//            var navigatorBar = ((WebPageController) userData).getNavigatorBar();
//            this.getParent().setTop(navigatorBar);
        };
    }

    public void createPopupWindow(AbstractWebPageController webPageController) {
        var tab = webPageController.getTab();
        this.tabPane.getTabs().add(tab);
        this.tabPane.getSelectionModel().select(tab);
    }

    /**
     * 更新窗口标题
     */
    public void updateTitle(String title) {
        this.getStage().setTitle(title);
    }


    private static MainViewController mainViewController;

    public synchronized static MainViewController getInstance() {
        if (mainViewController == null) {
            mainViewController = new MainViewController();
        }
        return mainViewController;
    }

}
