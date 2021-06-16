package cn.navigational.xbrowser.app;

import cn.navigational.xbrowser.app.controller.MainViewController;
import javafx.application.Application;
import javafx.stage.Stage;

public class XBrowser extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        MainViewController.getInstance().openWindow();
    }

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void stop() throws Exception {
        MainViewController.getInstance().dispose();
    }
}
