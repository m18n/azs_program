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

#include <mysql_connection.h>
#include <cppconn/driver.h>

#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

#ifdef __cplusplus
extern "C" {
#endif
class  CORE_API DataBase{
private:
    sql::Driver *driver;
    sql::Connection *con;
    std::string database;
    sql::Statement* stmt;
    bool init;
public:
    DataBase();
    void Connection(std::string ip,std::string name,std::string password,std::string database);
    bool IsInit();
    sql::ResultSet* SendSql(std::string sql);
    ~DataBase();
};
class CORE_API tb_node{
public:
    tb_node(DataBase* db);
    tb_node(DataBase*db,int id_node);
    virtual void Init(int id_node)=0;
    virtual void DownloadParameters()=0;
    virtual void UploadParameters()=0;
    ~tb_node();
protected:
    std::string table;
    DataBase* db;
    int id_node;

};
class CORE_API Tovar:public tb_node{
public:
    Tovar(DataBase* db);
    Tovar(DataBase* db,int id_tovar);
    virtual void  Init(int id_node) override;
    virtual void DownloadParameters() override;
    virtual void UploadParameters()override;
    ~Tovar();
private:
    
    std::string name_prog;
    std::string name_p;
    std::string name_p_f;
    int nd_code;
    int wog_code;
};
#ifdef __cplusplus
}
#endif
