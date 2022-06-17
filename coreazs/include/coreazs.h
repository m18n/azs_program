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

private:
    int width;
    int heigth;
    int x;
    int y;
    
};

class CORE_API AZS
{
public:
    AZS() : AZSdb("azs.sqlite")
    {
        units=Dispens_Unit::StaticGetAllUnit(&AZSdb);
    }

    ~AZS()
    {
    }
    bool CheckPassword(std::string password);

private:
    int id = 1;
    std::vector<Dispens_Unit> units;
    SQLite::Database AZSdb;
};
    
};