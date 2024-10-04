package application;

import javafx.beans.property.SimpleStringProperty;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.layout.AnchorPane;

import java.util.ArrayList;
import java.util.List;

public class OutputController {

    @FXML
    private AnchorPane outputPane;
    Label label = null;

    public void setStringOutput(String stringOutput) {
        outputPane.getChildren().clear();
        label = new Label(stringOutput);
        AnchorPane.setTopAnchor(label, 10.0);
        AnchorPane.setLeftAnchor(label, 10.0);
        outputPane.getChildren().add(label);
    }

    public static class RowData {
        private final SimpleStringProperty[] properties;

        public RowData(List<String> values) {
            properties = new SimpleStringProperty[values.size()];
            for (int i = 0; i < values.size(); i++) {
                properties[i] = new SimpleStringProperty(values.get(i));
            }
        }

        public SimpleStringProperty getProperty(int index) {
            return properties[index];
        }
    }

    public void setTableOutput(String tableOutput) {
        ArrayList<ArrayList<String>> tableData = new ArrayList<>();

        String[] rows = tableOutput.split("\n");
        List<String> columns = parseRow(rows[0]);

        List<List<String>> dataRows = new ArrayList<>();
        for (int i = 1; i < rows.length; i++) {
            List<String> row = parseRow(rows[i]);
            if (!row.isEmpty()) {
                dataRows.add(row);
            }
        }

        TableView<RowData> tableView = new TableView<>();
        tableView.setPrefWidth(1000);

        for (int i = 0; i<columns.size(); i++) {
            TableColumn<RowData, String> column = new TableColumn<>(columns.get(i));
            final int colIndex = i;
            column.setCellValueFactory(cellData -> cellData.getValue().getProperty(colIndex));
            column.setPrefWidth(1000/columns.size());
            tableView.getColumns().add(column);
        }

        for (int i = 0; i<dataRows.size(); i++) {
            tableView.getItems().add(new RowData(dataRows.get(i)));
        }

        outputPane.getChildren().clear();
        outputPane.getChildren().add(tableView);

    }

    private List<String> parseRow(String line) {
        String[] cells = line.split("\\|");
        List<String> row = new ArrayList<>();
        for (String cell : cells) {
            if (!cell.trim().isEmpty()) {
                row.add(cell.trim());
            }
        }

        return row;
    }

}
