#include "application_Database.h"
#include "Database.h"
#include "Statement.h"
#include "Parser.h"
#include "CustomFormat.h"
#include "SQLFormat.h"

Database* database = nullptr;
Parser* parser = nullptr;

JNIEXPORT void JNICALL Java_application_Database_createDatabase
  (JNIEnv *env, jobject ptr, jstring n) {
    const char* nm = env->GetStringUTFChars(n, nullptr);
    std::string name(nm);

    database = new Database(name);
    parser = new Parser(database);

    env->ReleaseStringUTFChars(n, nm);
  }
  
JNIEXPORT jstring JNICALL Java_application_Database_getTableNames
  (JNIEnv *env, jobject) {
    std::vector <Table*> tables = database->getTables();

    std::string result = "";
    for (int i = 0; i<tables.size(); i++) {
      result += tables[i]->getName();
      if (i != tables.size())
        result += "\n";
    }

    return env->NewStringUTF(result.c_str());
  }

JNIEXPORT jstring JNICALL Java_application_Database_executeQuery
  (JNIEnv *env, jobject ptr, jstring q) {
    const char* qy = env->GetStringUTFChars(q, nullptr);
    std::string query(qy);

    try {
        Statement* s = parser->parse(query);
        std::string res = s->execute();
        env->ReleaseStringUTFChars(q, qy);
        return env->NewStringUTF(res.c_str());
    }
    catch (const std::exception& e) {
        env->ReleaseStringUTFChars(q, qy);
        return env->NewStringUTF(e.what());
    }

  }

JNIEXPORT void JNICALL Java_application_Database_importCustomFormat
  (JNIEnv *env, jobject, jstring file) {
      const char* f = env->GetStringUTFChars(file, nullptr);
      std::string path(f);

      CustomFormat* cf = new CustomFormat(database);
      database = cf->import(path);
      parser = new Parser(database);

      env->ReleaseStringUTFChars(file, f);
  }

JNIEXPORT void JNICALL Java_application_Database_exportCustomFormat
  (JNIEnv *env, jobject, jstring file) {
      const char* f = env->GetStringUTFChars(file, nullptr);
      std::string path(f);

      CustomFormat* cf = new CustomFormat(database);
      cf->export_db(path);

      env->ReleaseStringUTFChars(file, f);
  }

JNIEXPORT void JNICALL Java_application_Database_exportSQL
  (JNIEnv *env, jobject, jstring file) {
      const char* f = env->GetStringUTFChars(file, nullptr);
      std::string path(f);

      SQLFormat* sql = new SQLFormat(database);
      sql->export_db(path);

      env->ReleaseStringUTFChars(file, f);
  }