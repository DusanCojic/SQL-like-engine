package application;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.ListView;

import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;

public class TableListController implements Initializable {

    @FXML
    private ListView<String> tableList;

    private ArrayList<String> items = new ArrayList<>();

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        tableList.getItems().addAll(items);

        tableList.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observableValue, String s, String t1) {
                String tableName = t1;
                String query = "SELECT * FROM " + tableName;
                String result = Main.d.executeQuery(query);
                Main.mediator.getOutputController().setTableOutput(result);
            }
        });
    }

    public void addTable(String table) {
        if (!items.contains(table)) {
            items.add(table);
            tableList.getItems().add(table);
        }
    }

    public void removeTable(String table) {
        items.remove(table);
        tableList.getItems().clear();
        tableList.getItems().addAll(items);
    }

    public void clearList() {
        items.clear();
        tableList.getItems().clear();
    }
}
