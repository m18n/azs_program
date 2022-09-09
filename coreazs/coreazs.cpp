#include "coreazs.h"
DataBase::DataBase(){
        init=false;
        driver = get_driver_instance();
    }
void DataBase::Connection(std::string ip,std::string name,std::string password,std::string database){
        con = driver->connect(ip, name,password);
        init=true;
        con->setSchema(database);
        this->database=database;
        stmt=con->createStatement();

    }
bool DataBase::IsInit(){
        return init;
    }
sql::ResultSet* DataBase::SendSql(std::string sql){
         sql::ResultSet* res = stmt->executeQuery(sql);
         return res;
    }
DataBase::~DataBase(){
        delete stmt;
        delete con;
        
    }
tb_node::tb_node(DataBase*db){
       
        id_node=0;
    }
tb_node::tb_node(DataBase*db,int id_node){
 
        
}
tb_node::~tb_node(){

}
Tovar::Tovar(DataBase*db):tb_node(db){
        table="tovar";
    }
Tovar::Tovar(DataBase*db,int id_tovar):tb_node(db,id_tovar){
        
        table="tovar";
        Init(id_tovar);
    }
void Tovar::Init(int id_node) {
        this->id_node=id_node;
        DownloadParameters();
    }
void Tovar::DownloadParameters() {
        if(db->IsInit()){
            auto res=db->SendSql("SELECT * FROM "+table+" WHERE id="+std::to_string(id_node));
             while (res->next()) {
                
                std::cout << res->getString(1) << "\n";
            }
        }
    }
void Tovar::UploadParameters(){
    std::cout<<"TEST\n";
    }
Tovar::~Tovar(){
    
}