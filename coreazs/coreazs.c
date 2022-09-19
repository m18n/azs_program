#include "coreazs.h"
void  create_local_database(local_database_t* ld){
    int rc = sqlite3_open("config.sqlite", &ld->db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(ld->db));
        sqlite3_close(ld->db);
        
        return 1;
    }
}
void create_conf_table(conf_table_t* loc){
    loc->id=-1;
    strcpy(loc->host,"");
    strcpy(loc->name,"");
    strcpy(loc->password,"");   
}
conf_table_t conf_table_getconfig(local_database_t* loc){
     char sql[300];
    int index=0;
    strcpy(&sql[0],"CREATE TABLE IF NOT EXISTS config_db (id INTEGER,host TEXT,name TEXT,password TEXT,PRIMARY KEY(id AUTOINCREMENT));");
    
    local_database_query(loc,sql,false);
    strcpy(sql,"SELECT * FROM config_db");
    sqlite3_stmt* res=local_database_query(loc,sql,true);
    conf_table_t conf;
    create_conf_table(&conf);
    int rc = sqlite3_step(res);
   if (rc == SQLITE_ROW) {
        conf.id=sqlite3_column_int(res,0);
        strcpy(conf.host,sqlite3_column_text(res,1));
        strcpy(conf.name,sqlite3_column_text(res,2));
        strcpy(conf.password,sqlite3_column_text(res,3));
    }
    sqlite3_finalize(res);
    return conf;
}

void conf_table_setconfig(local_database_t* loc,conf_table_t* conf){
    char sql[300];
    if(conf->id==-1){
        int index=0;
        strcpy(&sql[0],"INSERT INTO config_db (host,name,password) VALUES ('");     
        index=strlen(sql);
        strcpy(&sql[index],conf->host);
        index=strlen(sql);
        strcpy(&sql[index],"','");
        index=strlen(sql);
        strcpy(&sql[index],conf->name);
        index=strlen(sql);
        strcpy(&sql[index],"','");
        index=strlen(sql);
        strcpy(&sql[index],conf->password);
        index=strlen(sql);
        strcpy(&sql[index],"');");
        local_database_query(loc,sql,false);
        *conf=conf_table_getconfig(loc);
    }else{
        int index=0;
        strcpy(&sql[0],"UPDATE config_db SET host='");     
        index=strlen(sql);
        strcpy(&sql[index],conf->host);
        index=strlen(sql);
        strcpy(&sql[index],"', name='");
        index=strlen(sql);
        strcpy(&sql[index],conf->name);
        index=strlen(sql);
        strcpy(&sql[index],"', password='");
        index=strlen(sql);
        strcpy(&sql[index],conf->password);
        index=strlen(sql);
        strcpy(&sql[index],"' WHERE id=");
         char id[12];
        sprintf(id, "%d",conf->id);
        index=strlen(sql);
        strcpy(&sql[index],id);
        index=strlen(sql);
        strcpy(&sql[index],";");
        local_database_query(loc,sql,false);
    }
   
}
 sqlite3_stmt* local_database_query(local_database_t* db,const char* query,bool res){
    int rc=0;
    if(res){
        sqlite3_stmt* res;
        rc = sqlite3_prepare_v2(db->db, query, -1, &res, 0);    
        
        if (rc != SQLITE_OK) {
            
            fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db->db));
            sqlite3_close(db->db);
            
            return NULL;
        }
        return res;
    }else{
        char *err_msg = 0;
        rc = sqlite3_exec(db->db, query, 0, 0, &err_msg);
    
        if (rc != SQLITE_OK ) {
            
            fprintf(stderr, "SQL error: %s\n", err_msg);
            
            sqlite3_free(err_msg);        
            sqlite3_close(db->db);
            
            return 1;
        } 
        return NULL;
    }
}
void destroy_local_database(local_database_t* loc){
    if(loc->db!=NULL){
    sqlite3_close(loc->db);
    loc->db=NULL;
    }
}
void GetDT(){
    printf("MySQL client version: %s\n", mysql_get_client_info());
}
MYSQL_RES* database_query(database_t* db,const char* query,bool res){
    if (mysql_query(db->con, query))
    {
            fprintf(stderr, "%s\n", mysql_error(db->con));
            mysql_close(db->con);
            return NULL;
    }
    MYSQL_RES *result = mysql_store_result(db->con);
    if(res==false){
        mysql_free_result(res);
        result=NULL;
    }
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
int database_connect(database_t* db,const char* host,const char* username,const char* password){
    if (mysql_real_connect(db->con, host,username,password,
          NULL, 0, NULL, 0) == NULL)
  {
       
      fprintf(stderr, "%s\n", mysql_error(db->con));
      mysql_close(db->con);
       db->con=NULL;
      return -1;
  }
  database_query(db,"USE azs;",false);
  database_query(db,"SET NAMES 'utf8'",false);
  database_query(db,"SET CHARACTER SET utf8",false);
  database_query(db,"SET SESSION collation_connection = 'utf8_unicode_ci'",false);
  return 0;
}
void db_node_rowdb_to_param(db_node_t* node,char** row){

}
void db_node_string_to_param(db_node_t* node,char* string,int size){

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
    node->rowdb_to_param=db_node_rowdb_to_param;
    node->show=db_node_show;
    node->get_string=db_node_get_string;
    node->string_to_param=db_node_string_to_param;
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
int db_table_get_count(db_table_t* table){
    char buffersql[1000];
    int length=0;
    strcpy(buffersql,"SELECT COUNT(*) FROM ");
    length=strlen(buffersql);
    strcpy(&buffersql[length],table->nametable);
    MYSQL_RES* res=database_query(table->db,buffersql,true);
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
    MYSQL_RES* res=database_query(table->db,buffersql,true);
    
    int numcolum=mysql_num_fields(res);
    int index=0;
    for(int i=0;i<row_size;i++){
        MYSQL_ROW row=mysql_fetch_row(res);
        memcpy(nodes,node,sizenode);
        db_node_t* n=nodes;
        n->rowdb_to_param(n,row);
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
void tovar_node_rowdb_to_param(tovar_node_t* node,char** row){
    strcpy(node->name,row[5]);
    strcpy(node->name_p,row[10]);
    strcpy(node->name_p_f,row[11]);
    node->nd_code=atoi(row[14]);
    node->wog_code=atoi(row[15]);
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
        MYSQL_RES* res=database_query(node->node.db,buffer,true);
        MYSQL_ROW row=mysql_fetch_row(res);
        tovar_node_rowdb_to_param(node,row);
        mysql_free_result(res);   
   }else{
        printf("ERROR NOT ID\n");
   }
}
void tovar_node_upload_param(tovar_node_t* node){
    if(node->node.id!=0){
        char nd_code[12];
        sprintf(nd_code, "%d",node->nd_code);
        char wog_code[12];
        sprintf(wog_code, "%d",node->wog_code);
        char buffer[1000];
        int length=0;
        strcpy(&buffer[length],"UPDATE tovar SET name = '");
        length=strlen(buffer);
        strcpy(&buffer[length],node->name);
        length=strlen(buffer);
        strcpy(&buffer[length],"', name_p = '");
        length=strlen(buffer);
        strcpy(&buffer[length],node->name_p);
        length=strlen(buffer);
        strcpy(&buffer[length],"', name_p_f = '");
        length=strlen(buffer);
        strcpy(&buffer[length],node->name_p_f);
        length=strlen(buffer);
        strcpy(&buffer[length],"', nd_code = ");
        length=strlen(buffer);
        strcpy(&buffer[length],nd_code);
        length=strlen(buffer);
        strcpy(&buffer[length],", wog_code = ");
        length=strlen(buffer);
        strcpy(&buffer[length],wog_code);
        length=strlen(buffer);
        strcpy(&buffer[length]," WHERE id_tovar = ");
        length=strlen(buffer);
        char buffint[12];
        sprintf(buffint, "%d", node->node.id);
        strcpy(&buffer[length],buffint);
        database_query(node->node.db,buffer,false);

          
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
    int lengtharg=strlen("id:")+1+strlen("name:")+1+strlen("name_p:")+1+strlen("name_p_f:")+1+strlen("nd_code:")+1+strlen("wog_code:")+1;
    char* tovarstr=malloc(lenparam+lengtharg+1);
    int index=0;
    strcpy(&tovarstr[index],"id:");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],id);
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"\r");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"name:");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],node->name);
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"\r");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"name_p:");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],node->name_p);
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"\r");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"name_p_f:");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],node->name_p_f);
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"\r");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"nd_code:");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],nd_code);
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"\r");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"wog_code:");
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],wog_code);
    index=strlen(tovarstr);
    strcpy(&tovarstr[index],"\r");
    index=strlen(tovarstr);
    tovarstr[lenparam+lengtharg]='\0';
    return tovarstr;

}
void tovar_node_string_to_param(tovar_node_t* node,char* string,int size){
    int sizeres=0;
    char* temp=NULL;
    temp=GetValueParam(string,size,"id",&sizeres);
    node->node.id=atoi(temp);
    free(temp);
    temp=GetValueParam(string,size,"name",&sizeres);
    memcpy(node->name,temp,size);
    free(temp);
    temp=GetValueParam(string,size,"name_p",&sizeres);
    memcpy(node->name_p,temp,size);
    free(temp);
    temp=GetValueParam(string,size,"name_p_f",&sizeres);
    memcpy(node->name_p_f,temp,size);
    free(temp);
    temp=GetValueParam(string,size,"nd_code",&sizeres);
    node->nd_code=atoi(temp);
    free(temp);
    temp=GetValueParam(string,size,"wog_code",&sizeres);
    node->wog_code=atoi(temp);
    free(temp);
}
void create_tovar_node(tovar_node_t* node){
    create_db_node(&node->node);
    node->nd_code=0;
    node->wog_code=0;
    node->node.download_param=tovar_node_downlaod_param;
    node->node.upload_param=tovar_node_upload_param;
    node->node.rowdb_to_param=tovar_node_rowdb_to_param;
    node->node.show=tovar_node_show;
    node->node.get_string=tovar_node_get_string;
    node->node.string_to_param=tovar_node_string_to_param;
}
void init_tovar_node(tovar_node_t* node,database_t* db){
    create_tovar_node(node);
    init_db_node(&node->node,db);
    node->node.download_param=tovar_node_downlaod_param;
    node->node.upload_param=tovar_node_upload_param;
    node->node.rowdb_to_param=tovar_node_rowdb_to_param;
    node->node.show=tovar_node_show;
    node->node.get_string=tovar_node_get_string;
    node->node.string_to_param=tovar_node_string_to_param;
}