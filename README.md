### Simple SQL-like engine for executing queries

- Java native library made in C++
- GUI made using JavaFX framework

#### Features

- Creating empty database
- Import existing database
- Export created database with tables to a custom format and SQL format
- Creating table with given name and columns: ```CREATE TABLE Table(Column1,Column2)```
- Deleting table with a given name: ```DROP TABLE Table```
- Selecting data from a table with filters: ```SELECT Column1, Column2 FROM Table WHERE Column1>1 AND Column1<5```
- Inserting into a table: ```INSERT INTO Table(Colum1,Column2) VALUES (Value1,Value2),(Value2,Value4)```
- Deleting rows from a table: ```DELETE FROM Table WHERE Column1=Something```
- Updating rows in a table: ```UPDATE Table SET Column1=Something WHERE Column1=SomethingElse```

https://github.com/user-attachments/assets/794fe085-2002-4b52-ad55-5f9f27c006e2
