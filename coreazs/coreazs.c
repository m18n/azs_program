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
  database_query(db,"SET NAMES 'utf8'");
  database_query(db,"SET CHARACTER SET utf8");
  database_query(db,"SET SESSION collation_connection = 'utf8_unicode_ci'");
}
void db_node_row_to_param(db_node_t* node,char** row){

}
void db_node_downlaod_param(db_node_t* node){
    
}
void db_node_upload_param(db_node_t* node){

}
void db_node_show(db_node_t* node){

}
char* db_node_get_string(db_node_t* node){

}
void create_db_node(db_node_t* node){
    node->id=0;
    node->db=NULL;
    node->download_param=db_node_downlaod_param;
    node->upload_param=db_node_upload_param;
    node->row_to_param=db_node_row_to_param;
    node->show=db_node_show;
    node->get_string=db_node_get_string;
}
void destroy_database(database_t* db){
    if(db->con!=NULL){
        mysql_close(db->con);
        db->con=NULL;
    }
}
void init_db_node(db_node_t* node,database_t* db){
    create_db_node(node);
    node->db=db;
}
CORE_API int db_table_get_count(db_table_t* table){
    char buffersql[1000];
    int length=0;
    strcpy(buffersql,"SELECT COUNT(*) FROM ");
    length=strlen(buffersql);
    strcpy(&buffersql[length],table->nametable);
    MYSQL* res=database_query(table->db,buffersql);
     MYSQL_ROW row=mysql_fetch_row(res);
    int count=atoi(row[0]);
    mysql_free_result(res);
    return count;
}
db_node_t* db_table_get_all(db_table_t* table,db_node_t* node,int sizenode,int* sizenodes){
    int row_size=db_table_get_count(table);
    *sizenodes=row_size;
    
    char* nodes=malloc(sizenode*row_size);
    char* start=nodes;
    char buffersql[1000];
    int length=0;
    strcpy(buffersql,"SELECT * FROM ");
    length=strlen(buffersql);
    strcpy(&buffersql[length],table->nametable);
    MYSQL* res=database_query(table->db,buffersql);
    
    int numcolum=mysql_num_fields(res);
    int index=0;
    for(int i=0;i<row_size;i++){
        MYSQL_ROW row=mysql_fetch_row(res);
        memcpy(nodes,node,sizenode);
        db_node_t* n=nodes;
        n->row_to_param(n,row);
        nodes+=sizenode;
    }
    nodes=start;
    mysql_free_result(res);
    return (db_node_t*)start;
}
void create_db_table(db_table_t* table){
    table->db=NULL;
 
}
void init_db_table(db_table_t* table,database_t* db,const char nametable[50]){
    create_db_table(table);
    table->db=db;
    strcpy(table->nametable,nametable);    
}
void tovar_node_row_to_param(tovar_node_t* node,char** row){
    // int arrsize = MultiByteToWideChar( CP_UTF8 , 0 , row[5] , -1, NULL , 0 );

    // int count = WideCharToMultiByte(CP_UTF8, 0, row[5], wstr.length(), NULL, 0, NULL, NULL);
    // std::string str(count, 0);
    // WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);

    // arrsize = MultiByteToWideChar( CP_UTF8 , 0 , row[10] , -1, NULL , 0 );
    // MultiByteToWideChar( CP_UTF8 , 0 ,row[10], -1,node->name_p,arrsize);
    // arrsize = MultiByteToWideChar( CP_UTF8 , 0 , row[11] , -1, NULL , 0 );
    // MultiByteToWideChar( CP_UTF8 , 0 ,row[11], -1,node->name_p_f,arrsize);
    
    strcpy(node->name,row[5]);
    strcpy(node->name_p,row[10]);
    strcpy(node->name_p_f,row[11]);
    node->node.id=atoi(row[2]);
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
        tovar_node_row_to_param(node,row);
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
void tovar_node_show(tovar_node_t* node){
    printf("TOVAR: ID: %d NAME: %s NAME_P: %s NAME_P_F: %s ND_CODE: %d WOG_CODE: %d\n",node->node.id,node->name,node->name_p,node->name_p_f,node->nd_code,node->wog_code);
}
char* tovar_node_get_string(tovar_node_t* node){
    char id[12];
    sprintf(id, "%d", node->node.id);
    char wog_code[12];
    sprintf(wog_code, "%d", node->wog_code);
    char nd_code[12];
    sprintf(nd_code, "%d", node->nd_code);
    int lenparam=strlen(id)+strlen(node->name)+strlen(node->name_p)+strlen(node->name_p_f)+strlen(wog_code)+strlen(nd_code);
    int lengtharg=strlen("id:")+1+strlen("name:")+1+strlen("name_p:")+1+strlen("name_p_f:")+1+strlen("wog_code:")+1+strlen("nd_code:")+1;
    char* tovarstr=malloc(lenparam+lengtharg+1);
    int index=0;
    strcpy(&tovarstr[index],"id:");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],id);
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"|");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"name:");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],node->name);
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"|");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"name_p:");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],node->name_p);
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"|");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"name_p_f:");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],node->name_p_f);
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"|");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"wog_code:");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],wog_code);
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"|");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"nd_code:");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],nd_code);
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"|");
    index=strlen(tovarstr);
    tovarstr[lenparam+lengtharg]='\0';
    return tovarstr;

}
void create_tovar_node(tovar_node_t* node){
    create_db_node(&node->node);
    node->nd_code=0;
    node->wog_code=0;
    node->node.download_param=tovar_node_downlaod_param;
    node->node.upload_param=tovar_node_upload_param;
    node->node.row_to_param=tovar_node_row_to_param;
    node->node.show=tovar_node_show;
    node->node.get_string=tovar_node_get_string;
}
void init_tovar_node(tovar_node_t* node,database_t* db){
    create_tovar_node(node);
    init_db_node(&node->node,db);
    node->node.download_param=tovar_node_downlaod_param;
    node->node.upload_param=tovar_node_upload_param;
    node->node.row_to_param=tovar_node_row_to_param;
     node->node.show=tovar_node_show;
      node->node.get_string=tovar_node_get_string;
}