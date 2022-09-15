#pragma once
#ifdef _WIN32

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)


#else
#define CORE_API __declspec(dllimport)
#endif
#else
#define CORE_API
#endif

// #include <mysql_connection.h>
// #include <cppconn/driver.h>

// #include <cppconn/exception.h>
// #include <cppconn/statement.h>
// #include <cppconn/resultset.h>
#include <stdlib.h>
#include <stdio.h>
#include"mysql.h"
#ifdef __cplusplus
extern "C" {
#endif

void CORE_API GetDT();
typedef struct CORE_API database{
    MYSQL* con;
    
}database_t;
CORE_API MYSQL_RES* database_query(database_t* db,const char* query);
void CORE_API create_database(database_t* database);
void CORE_API database_connect(database_t* db);

typedef struct CORE_API db_node{
    database_t* db;
    int id;
    void(*download_param)(struct db_node* node);
    void(*upload_param)(struct db_node* node);
}db_node_t;
void CORE_API db_node_downlaod_param(db_node_t* node);
void CORE_API db_node_upload_param(db_node_t* node);
void CORE_API create_db_node(db_node_t* node);
void CORE_API init_db_node(db_node_t* node,database_t* db);

typedef struct CORE_API tovar_node{
    db_node_t node;
    char name[50];
    char name_p[50];
    char name_p_f[50];
    int nd_code;
    int wog_code;
}tovar_node_t;
void CORE_API tovar_node_downlaod_param(tovar_node_t* node);
void CORE_API tovar_node_upload_param(tovar_node_t* node);
void CORE_API create_tovar_node(tovar_node_t* node);
void CORE_API init_tovar_node(tovar_node_t* node,database_t* db);
#ifdef __cplusplus
}
#endif
