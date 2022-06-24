#pragma once
#ifdef _WIN32



#define CORE_API __declspec(dllexport)



#else
#define CORE_API
#endif
#include <iostream>
#include <vector>
#include <string>
#include"sqlite/sqlite3.h"

extern "C"
{
   
class CORE_API Unit
{
public:
      Unit();
     virtual void Synhron();
     void InitModule(sqlite3 *db, std::string table, int id);
     virtual void Show();
    int GetId();
    ~Unit();
protected:
    sqlite3 *db;
    bool init;
    std::string table;
    int id;
};
class CORE_API Dispens_Unit : public Unit
{
public:
     Dispens_Unit();
     void Synhron();
    static  std::vector<Dispens_Unit> StaticGetAllUnit(sqlite3 *db);
    void Show();
    void Resize(int width, int heigth);
    void Move(int x, int y);
    void GetAllParam(int* width,int* heigth,int* x,int* y);
    
    ~Dispens_Unit();
    std::string GetParamDispens_Unit();
private:
    int width;
    int heigth;
    int x;
    int y;
    
};

class CORE_API AZS
{
public:
    AZS();

    ~AZS();
    Dispens_Unit* GetUnit(int index);
    Dispens_Unit* GetUnitbyId(int id);
    int GetSizeUnit();

    bool CheckPassword(std::string password);
    
private:
    int id = 1;
    std::vector<Dispens_Unit> units;
    sqlite3* AZSdb;
};
    
};