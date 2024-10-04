package application;

import javafx.fxml.FXML;
import javafx.scene.control.TextArea;

public class CodeAreaController {

    @FXML
    private TextArea codeArea;

    public String getQuery() {
        return codeArea.getText();
    }

}
