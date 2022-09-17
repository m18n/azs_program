#pragma once
#ifdef _WIN32

#ifdef CORE_EXPORTS

#define CORE_API __declspec(dllimport)

#else
#define CORE_API __declspec(dllexport)
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
void CORE_API destroy_database(database_t* db);
typedef struct CORE_API db_node{
    database_t* db;
    int id;
    void(*row_to_param)(struct db_node* node,char** row);
    void(*download_param)(struct db_node* node);
    void(*upload_param)(struct db_node* node);
    void(*show)(struct db_node* node);
    char*(*get_string)(struct db_node* node);
}db_node_t;
void CORE_API db_node_row_to_param(db_node_t* node,char** row);
void CORE_API db_node_downlaod_param(db_node_t* node);
void CORE_API db_node_upload_param(db_node_t* node);
void CORE_API db_node_show(db_node_t* node);
CORE_API char*  db_node_get_string(db_node_t* node);
void CORE_API create_db_node(db_node_t* node);
void CORE_API init_db_node(db_node_t* node,database_t* db);
typedef struct CORE_API db_table{
    database_t* db;
    char nametable[100];
}db_table_t;
CORE_API db_node_t* db_table_get_all(db_table_t* table,db_node_t* node,int sizenode,int* sizenodes);
CORE_API int db_table_get_count(db_table_t* table);
void CORE_API create_db_table(db_table_t* table);
void CORE_API init_db_table(db_table_t* table,database_t* db,const char nametable[50]);
typedef struct CORE_API tovar_node{
    db_node_t node;
    char name[150];
    char name_p[150];
    char name_p_f[150];
    int nd_code;
    int wog_code;
    
}tovar_node_t;
void CORE_API tovar_node_show(tovar_node_t* node);
void CORE_API tovar_node_row_to_param(tovar_node_t* node,char** row);
void CORE_API tovar_node_downlaod_param(tovar_node_t* node);
void CORE_API tovar_node_upload_param(tovar_node_t* node);
CORE_API char*  tovar_node_get_string(tovar_node_t* node);

void CORE_API create_tovar_node(tovar_node_t* node);
void CORE_API init_tovar_node(tovar_node_t* node,database_t* db);

#ifdef __cplusplus
}
#endif
