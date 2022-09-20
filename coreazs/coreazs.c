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
    strcpy(loc->database,""); 
}

conf_table_t conf_table_getconfig(local_database_t* loc){
     char sql[300];
    strcpy(sql,"CREATE TABLE IF NOT EXISTS config_db (id INTEGER,host TEXT,name TEXT,password TEXT,database TEXT,PRIMARY KEY(id AUTOINCREMENT));");
    
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
        strcpy(conf.database,sqlite3_column_text(res,4));
    }
    sqlite3_finalize(res);
    return conf;
}

void conf_table_setconfig(local_database_t* loc,conf_table_t* conf){
    char sql[300];
    sql[0]='\0';
    if(conf->id==-1){
        StringAddString(sql,"INSERT INTO config_db (host,name,password,database) VALUES ('");
        StringAddString(sql,conf->host);
        StringAddString(sql,"','");
        StringAddString(sql,conf->name);
        StringAddString(sql,"','");
        StringAddString(sql,conf->password);
        StringAddString(sql,"','");
        StringAddString(sql,conf->database);
        StringAddString(sql,"');");
        local_database_query(loc,sql,false);
        *conf=conf_table_getconfig(loc);
    }else{
        StringAddString(sql,"UPDATE config_db SET host='");
        StringAddString(sql,conf->host);
        StringAddString(sql,"', name='");
        StringAddString(sql,conf->name);
        StringAddString(sql,"', password='");
        StringAddString(sql,conf->password);
        StringAddString(sql,"', database='");
        StringAddString(sql,conf->database);
        StringAddString(sql,"' WHERE id=");
        StringAddInt(sql,conf->id);
        StringAddString(sql,";");
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
    if(db->isconnect){
    if (mysql_query(db->con, query))
    {
            fprintf(stderr, "%s\n", mysql_error(db->con));
            destroy_database(db);
            return NULL;
    }
    MYSQL_RES *result = mysql_store_result(db->con);
    if(res==false){
        mysql_free_result(res);
        result=NULL;
    }
    return result;
    }else{
        return NULL;
    }
}
void create_database(database_t* database){
    database->con=mysql_init(NULL);
    database->isconnect=false;
     if (database->con == NULL)
    {

        fprintf(stderr, "%s\n", mysql_error(database->con));
        exit(1);
    }
   
}
int database_connect(database_t* db,const char* host,const char* username,const char* password,const char*database){
    destroy_database(db);
    create_database(db);
    if (mysql_real_connect(db->con, host,username,password,
          NULL, 0, NULL, 0) == NULL)
  {
       
      fprintf(stderr, "%s\n", mysql_error(db->con));
      mysql_close(db->con);
      db->con=NULL;
      db->isconnect=false;
      return -1;
  }
  db->isconnect=true;
  char use[100];
  use[0]='\0';
  StringAddString(use,"USE `");
  StringAddString(use,database);
  StringAddString(use,"`;");
  database_query(db,use,false);
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
    db->isconnect=false;
    if(db->con!=NULL){
        db->isconnect=false;
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
    buffersql[0]='\0';
    int length=0;
    StringAddString(buffersql,"SELECT COUNT(*) FROM ");
    StringAddString(buffersql,table->nametable);
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
    buffersql[0]='\0';
    int length=0;
    StringAddString(buffersql,"SELECT * FROM ");
    StringAddString(buffersql,table->nametable);
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
        StringAddInt(buffer,node->node.id);
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
        char buffer[1000];
        strcpy(buffer,"UPDATE tovar SET name = '");
        StringAddString(buffer,node->name);
        StringAddString(buffer,"', name_p = '");
        StringAddString(buffer,node->name_p);
        StringAddString(buffer,"', name_p_f = '");
        StringAddString(buffer,node->name_p_f);
        StringAddString(buffer,"', nd_code = ");
        StringAddInt(buffer,node->nd_code);
        StringAddString(buffer,", wog_code = ");
        StringAddInt(buffer,node->wog_code);
        StringAddString(buffer," WHERE id_tovar = ");
        StringAddInt(buffer,node->node.id);
        database_query(node->node.db,buffer,false);

          
   }else{
    printf("ERROR NOT ID\n");
   }
}
void tovar_node_show(tovar_node_t* node){
    printf("TOVAR: ID: %d NAME: %s NAME_P: %s NAME_P_F: %s ND_CODE: %d WOG_CODE: %d\n",node->node.id,node->name,node->name_p,node->name_p_f,node->nd_code,node->wog_code);
}
char* tovar_node_get_string(tovar_node_t* node){
    int lenparam=GetLengthInt(node->node.id)+strlen(node->name)+strlen(node->name_p)+strlen(node->name_p_f)+GetLengthInt(node->wog_code)+GetLengthInt(node->nd_code);
    int lengtharg=strlen("id:")+1+strlen("name:")+1+strlen("name_p:")+1+strlen("name_p_f:")+1+strlen("nd_code:")+1+strlen("wog_code:")+1;
    char* tovarstr=malloc(lenparam+lengtharg+1);
    int index=0;
    tovarstr[0]='\0';
    StringAddString(tovarstr,"id:");
    StringAddInt(tovarstr,node->node.id);
    StringAddString(tovarstr,"\rname:");
    StringAddString(tovarstr,node->name);
    StringAddString(tovarstr,"\rname_p:");
    StringAddString(tovarstr,node->name_p);
    StringAddString(tovarstr,"\rname_p_f:");
    StringAddString(tovarstr,node->name_p_f);
    StringAddString(tovarstr,"\rnd_code:");
    StringAddInt(tovarstr,node->nd_code);
    StringAddString(tovarstr,"\rwog_code:");
    StringAddInt(tovarstr,node->wog_code);
    StringAddString(tovarstr,"\r");
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
    node->node.db=db;
}
void tank_node_show(tank_node_t* node){
    
    printf("TANK Id:%d,NN:%d,id_tovar:%d,color:%d\n",node->node.id,node->nn,node->id_tovar,node->color);
}
void  tank_node_rowdb_to_param(tank_node_t* node,char** row){
    node->nn=atoi(row[0]);
    node->node.id=atoi(row[2]);
    node->id_tovar=atoi(row[4]);
    node->color=atoi(row[7]);
}
void  tank_node_string_to_param(tank_node_t* node,char* string,int size){
    int sizeres=0;
    char* temp=NULL;
    temp=GetValueParam(string,size,"id",&sizeres);
    node->node.id=atoi(temp);
    free(temp);
    temp=GetValueParam(string,size,"nn",&sizeres);
    node->nn=atoi(temp);
    free(temp);
    temp=GetValueParam(string,size,"id_tovar",&sizeres);
    node->id_tovar=atoi(temp);
    free(temp);
    temp=GetValueParam(string,size,"color",&sizeres);
    node->color=atoi(temp);
    free(temp);
    
}
void  tank_node_downlaod_param(tank_node_t* node){
    if(node->node.id!=0){
        char buffer[1000];
        strcpy(buffer,"SELECT * FROM tank WHERE id_tank=");
        StringAddInt(buffer,node->node.id);
        MYSQL_RES* res=database_query(node->node.db,buffer,true);
        MYSQL_ROW row=mysql_fetch_row(res);
        tovar_node_rowdb_to_param(node,row);
        mysql_free_result(res);   
   }else{
        printf("ERROR NOT ID\n");
   }
}
void  tank_node_upload_param(tank_node_t* node){
    if(node->node.id!=0){
        char buffer[1000];
        strcpy(buffer,"UPDATE tovar SET nn = '");
        StringAddInt(buffer,node->nn);
        StringAddString(buffer,"', id_tovar = '");
        StringAddInt(buffer,node->id_tovar);
        StringAddString(buffer,"', color = '");
        StringAddInt(buffer,node->color);
        StringAddString(buffer," WHERE id_tank = ");
        StringAddInt(buffer,node->node.id);
        database_query(node->node.db,buffer,false);          
   }else{
    printf("ERROR NOT ID\n");
   }
}
 char*  tank_node_get_string(tank_node_t* node){
    int lenparam=GetLengthInt(node->node.id)+GetLengthInt(node->nn)+GetLengthInt(node->id_tovar)+GetLengthInt(node->color);
    int lengtharg=strlen("id:")+1+strlen("nn:")+1+strlen("id_tovar:")+1+strlen("color:")+1;
    char* tovarstr=malloc(lenparam+lengtharg+1);
    int index=0;
    tovarstr[0]='\0';
    StringAddString(tovarstr,"id:");
    StringAddInt(tovarstr,node->node.id);
    StringAddString(tovarstr,"\rnn:");
    StringAddInt(tovarstr,node->nn);
    StringAddString(tovarstr,"\rid_tovar:");
    StringAddInt(tovarstr,node->id_tovar);
    StringAddString(tovarstr,"\rcolor:");
    StringAddInt(tovarstr,node->color);
    StringAddString(tovarstr,"\r");
    return tovarstr;
 }

void  create_tank_node(tank_node_t* node){
    create_db_node(node);
    node->node.download_param=tank_node_downlaod_param;
    node->node.get_string=tank_node_get_string;
    node->node.rowdb_to_param=tank_node_rowdb_to_param;
    node->node.string_to_param=tank_node_string_to_param;
    node->node.show=tank_node_show;
    node->node.upload_param=tank_node_upload_param;
}
void  init_tank_node(tank_node_t* node,database_t* db){
    create_tank_node(node);
    node->node.db=db;
}