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
#include <iostream>
#include <vector>
#include "../SQLiteCpp/include/SQLiteCpp/SQLiteCpp.h"
#include <string>

extern "C"
{
class CORE_API Unit
{
public:
    Unit()
    {
        init = false;
        db = NULL;
        id = -1;
    }
    virtual void Synhron();
    void InitModule(SQLite::Database *db, std::string table, int id);
    virtual void Show();
    int GetId(){
        return id;
    }
    
protected:
    SQLite::Database *db;
    bool init;
    std::string table;
    int id;
};
class CORE_API Dispens_Unit : public Unit
{
public:
    Dispens_Unit(){

    };
    void Synhron();
    static std::vector<Dispens_Unit> StaticGetAllUnit(SQLite::Database *db);
    void Show();
    void Resize(int width, int heigth);
    void Move(int x, int y);
    void GetAllParam(int* width,int* heigth,int* x,int* y);
    
    ~Dispens_Unit(){

    };
    std::string GetParamDispens_Unit(){
        std::string param;
        param+="id:"+std::to_string(id)+"|";
        param+="width:"+std::to_string(width)+"|";
        param+="heigth:"+std::to_string(heigth)+"|";
        param+="x:"+std::to_string(x)+"|";
        param+="y:"+std::to_string(y)+"|";
        return param;
    }
private:
    int width;
    int heigth;
    int x;
    int y;
    
};

class CORE_API AZS
{
public:
    AZS() : AZSdb("azs.sqlite",SQLite::OPEN_READWRITE)
    {
        units=Dispens_Unit::StaticGetAllUnit(&AZSdb);
    }

    ~AZS()
    {
        std::cout<<"END AZS\n";
    }
    Dispens_Unit* GetUnit(int index){
        return &units[index];
    }
     Dispens_Unit* GetUnitbyId(int id){
         for(int i=0;i<units.size();i++){
             if(units[i].GetId()==id){
                 return &units[i];
             }
         }
        return NULL;
    }
    int GetSizeUnit(){
        return units.size();
    }

    bool CheckPassword(std::string password);
    
private:
    int id = 1;
    std::vector<Dispens_Unit> units;
    SQLite::Database AZSdb;
};
    
};