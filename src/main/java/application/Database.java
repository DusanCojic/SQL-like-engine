package application;

public class Database {

    static {
        System.loadLibrary("nativeDatabase");
    }

    public native void createDatabase(String name);

    public native String getTableNames();

    public native String executeQuery(String query);

    public native void importCustomFormat(String file);

    public native void exportCustomFormat(String output);

    public native void exportSQL(String output);

}
