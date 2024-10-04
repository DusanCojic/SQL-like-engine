package application;

public class ControllerMediator {

    private NavBarController navBarController;
    private CodeAreaController codeAreaController;
    private OutputController outputController;
    private TableListController tableListController;

    public void setNavBarController(NavBarController navBarController) {
        this.navBarController = navBarController;
    }

    public void setCodeAreaController(CodeAreaController codeAreaController) {
        this.codeAreaController = codeAreaController;
    }

    public void setOutputController(OutputController outputController) {
        this.outputController = outputController;
    }

    public void setTableListController(TableListController tableListController) {
        this.tableListController = tableListController;
    }

    public NavBarController getNavBarController() {
        return navBarController;
    }

    public CodeAreaController getCodeAreaController() {
        return codeAreaController;
    }

    public OutputController getOutputController() {
        return outputController;
    }

    public TableListController getTableListController() {
        return tableListController;
    }

}
