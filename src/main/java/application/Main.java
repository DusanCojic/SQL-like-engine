package application;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.util.Objects;

public class Main extends Application {

    public static Database d = new Database();
    public static ControllerMediator mediator = new ControllerMediator();
    public static boolean isDatabaseOpened = false;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage stage) throws Exception {
        FXMLLoader rootLoader = new FXMLLoader(Objects.requireNonNull(getClass().getResource("main.fxml")));
        Parent root = rootLoader.load();

        FXMLLoader navBarLoader = new FXMLLoader(Objects.requireNonNull(getClass().getResource("navbar.fxml")));
        Node navbar = navBarLoader.load();

        FXMLLoader codeAreaLoader = new FXMLLoader(Objects.requireNonNull(getClass().getResource("codeArea.fxml")));;
        Node codearea = codeAreaLoader.load();
        AnchorPane.setTopAnchor(codearea, 25.0);
        AnchorPane.setLeftAnchor(codearea, 200.0);

        FXMLLoader tableListLoader = new FXMLLoader(Objects.requireNonNull(getClass().getResource("tableList.fxml")));
        Node tableList = tableListLoader.load();
        AnchorPane.setTopAnchor(tableList, 25.0);

        FXMLLoader outputPaneLoader = new FXMLLoader(Objects.requireNonNull(getClass().getResource("outputArea.fxml")));
        Node output = outputPaneLoader.load();
        AnchorPane.setTopAnchor(output, 375.0);
        AnchorPane.setLeftAnchor(output, 200.0);

        MainController mainController = rootLoader.getController();
        AnchorPane mainContainer = mainController.mainPane;

        mediator.setNavBarController(navBarLoader.getController());
        mediator.setCodeAreaController(codeAreaLoader.getController());
        mediator.setOutputController(outputPaneLoader.getController());
        mediator.setTableListController(tableListLoader.getController());

        mainContainer.getChildren().add(navbar);
        mainContainer.getChildren().add(codearea);
        mainContainer.getChildren().add(tableList);
        mainContainer.getChildren().add(output);

        Scene scene = new Scene(root);
        stage.setTitle("DataForge");
        stage.setResizable(false);
        stage.setScene(scene);
        stage.show();
    }
}
