#include "coreazs.h"
void GetDT(){
    printf("MySQL client version: %s\n", mysql_get_client_info());
}
MYSQL_RES* database_query(database_t* db,const char* query){
    if (mysql_query(db->con, query))
    {
            fprintf(stderr, "%s\n", mysql_error(db->con));
            mysql_close(db->con);
            return NULL;
    }
    MYSQL_RES *result = mysql_store_result(db->con);
    return result;
}
void create_database(database_t* database){
    database->con=mysql_init(NULL);
     if (database->con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(database->con));
        exit(1);
    }
   
}
void database_connect(database_t* db){
    if (mysql_real_connect(db->con, "192.168.0.103", "misha", "123",
          NULL, 0, NULL, 0) == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(db->con));
      mysql_close(db->con);
      exit(1);
  }
  database_query(db,"USE azs;");
}

void db_node_downlaod_param(db_node_t* node){
    
}
void db_node_upload_param(db_node_t* node){

}
void create_db_node(db_node_t* node){
    node->id=0;
    node->db=NULL;
    node->download_param=db_node_downlaod_param;
    node->upload_param=db_node_upload_param;
}
void init_db_node(db_node_t* node,database_t* db){
    create_db_node(node);
    node->db=db;
}
void tovar_node_downlaod_param(tovar_node_t* node){
    
   if(node->node.id!=0){
        char buffer[1000];
        strcpy(buffer,"SELECT * FROM tovar WHERE id_tovar=");
        int length=strlen(buffer);
        char buffint[12];
        sprintf(buffint, "%d", node->node.id);
        strcpy(&buffer[length],buffint);
        MYSQL_RES* res=database_query(node->node.db,buffer);
        MYSQL_ROW row=mysql_fetch_row(res);
        strcpy(node->name,row[5]);
        strcpy(node->name_p,row[10]);
        strcpy(node->name_p_f,row[11]);
        mysql_free_result(res);   
   }else{
        printf("ERROR NOT ID\n");
   }
}
void tovar_node_upload_param(tovar_node_t* node){
    if(node->node.id!=0){

   }else{
    printf("ERROR NOT ID\n");
   }
}
void create_tovar_node(tovar_node_t* node){
    create_db_node(&node->node);
    node->nd_code=0;
    node->wog_code=0;
    node->node.download_param=tovar_node_downlaod_param;
    node->node.upload_param=tovar_node_upload_param;
}
void init_tovar_node(tovar_node_t* node,database_t* db){
    create_tovar_node(node);
    init_db_node(&node->node,db);
    node->node.download_param=tovar_node_downlaod_param;
    node->node.upload_param=tovar_node_upload_param;
}