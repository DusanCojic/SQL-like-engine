package application;

import javax.swing.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Class that controls navigation bar of the application
 * All its methods are linked to certain option in the navbar
 * */
public class NavBarController {

    private String selectPattern = "^\\s*SELECT\\s+(\\*|(?:[^,]+(?:,[^,]+)*))\\s+FROM\\s+(\\w+)\\s*(?:WHERE\\s+((?:[^,]+(?:\\s*[><=]\\s*[^,]+)*(?:\\s+AND\\s+[^,]+)*)))?\\s*$";
    private String createTablePattern = "^\\s*CREATE\\s+TABLE\\s+(\\w+)\\s*\\(([^)]+)\\)\\s*$";
    private String dropTablePattern = "(DROP\\s+TABLE\\s+(\\w+))";

    /**
     * public void newDatabase():
     * creates new database using a native method implemented in C++
     * prints a message if the database is created successfully and error if it is not
     * */
    public void newDatabase() {
        Main.d.createDatabase("Baza");
        Main.mediator.getOutputController().setStringOutput("Database created successfully");
        Main.isDatabaseOpened = true;
    }

    /**
     * public void executeQuery():
     * gets a string input from the TextArea in the application
     * calls native method which parses it and executes on previously created ot imported database
     * prints a result string from the query execution as a label or as a table if it is a select query
     * and updates the table list if it is a create table or drop table query
     * */
    public void executeQuery() {
        if (!Main.isDatabaseOpened) {
            Main.mediator.getOutputController().setStringOutput("There is no database");
            return;
        }

        String query = Main.mediator.getCodeAreaController().getQuery();
        if (!query.isEmpty()) {
            String result = Main.d.executeQuery(query);

            Pattern pattern = Pattern.compile(createTablePattern, Pattern.CASE_INSENSITIVE);
            Matcher matcher = pattern.matcher(query);

            if (matcher.matches()) {
                Main.mediator.getTableListController().addTable(matcher.group(1));
                Main.mediator.getOutputController().setStringOutput("Table with a name '" + matcher.group(1) + "' created successfully");
                return;
            }

            pattern = Pattern.compile(dropTablePattern, Pattern.CASE_INSENSITIVE);
            matcher = pattern.matcher(query);

            if (matcher.matches()) {
                Main.mediator.getOutputController().setStringOutput("Dropped table '" + matcher.group(2) + "'");
                Main.mediator.getTableListController().removeTable(matcher.group(2));
                return;
            }

            pattern = Pattern.compile(selectPattern, Pattern.CASE_INSENSITIVE);
            matcher = pattern.matcher(query);

            if (matcher.matches()) {
                Main.mediator.getOutputController().setTableOutput(result);
                return;
            }

            Main.mediator.getOutputController().setStringOutput(result);

        }
    }

    /**
     * importDB and exportDB:
     * imports (exports) current database to a chosen location in a custom defined format
     * */
    public void importDB() {
        JFileChooser fileChooser = new JFileChooser();
        int response = fileChooser.showOpenDialog(null);
        if (response == JFileChooser.APPROVE_OPTION) {
            Main.d.importCustomFormat(fileChooser.getSelectedFile().getAbsolutePath());

            String tablesStr = Main.d.getTableNames();
            String[] tables = tablesStr.split("\n");

            Main.mediator.getTableListController().clearList();
            for (int i = 0; i < tables.length; i++)
                Main.mediator.getTableListController().addTable(tables[i]);

            Main.isDatabaseOpened = true;
        }
    }

    public void exportDB() {
        JFileChooser fileChooser = new JFileChooser();
        int response = fileChooser.showSaveDialog(null);
        if (response == JFileChooser.APPROVE_OPTION) {
            Main.d.exportCustomFormat(fileChooser.getSelectedFile().getAbsolutePath());
        }
    }

    /**
     * exportSQL():
     * exports database in a well-known SQL format
     * */
    public void exportSQL() {
        JFileChooser fileChooser = new JFileChooser();
        int response = fileChooser.showSaveDialog(null);
        if (response == JFileChooser.APPROVE_OPTION) {
            Main.d.exportSQL(fileChooser.getSelectedFile().getAbsolutePath());
        }
    }

}
