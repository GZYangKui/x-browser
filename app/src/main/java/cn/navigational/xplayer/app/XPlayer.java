package cn.navigational.xplayer.app;

import cn.navigational.xplayer.app.controller.MainViewController;
import javafx.application.Application;
import javafx.stage.Stage;

public class XPlayer extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        new MainViewController().openWindow();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
