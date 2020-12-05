#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   std::string name=argv[1];
   std::string version=argv[2];
   std::string url=argv[3];

   /* Open database */
   rc = sqlite3_open("quantum.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   std::string sql = "INSERT INTO PACKAGE(NAME,VERSION,URL)"  \
      "VALUES ('";

   sql.append(name);
   sql.append("', '");
   sql.append(version);
   sql.append("', '");
   sql.append(url);
   sql.append("' ); ");

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }

   sqlite3_close(db);
   return 0;
}
