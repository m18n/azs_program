#pragma once
#ifdef _WIN32

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif
#else
#define CORE_API
#endif
#define VERSION 1
#include"sqlite/sqlite3.h"
#include<WinSock2.h>
#include<stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct network{
    WSADATA wsaData;
    WORD dllverison;
    SOCKADDR_IN addr;
    SOCKET conn;
    int sizeofaddr;
    int idquery;
}network_t;
typedef struct packet{
    int id;
    char*(*GetStrPacket)(struct packet* pack,int* size);
}packet_t;
void InitPacket(packet_t* pack,int id,char*(*GetStrPacket)(struct packet* pack,int* size));
typedef struct getchat{
    struct packet pack;
    int min;
    int max;
}getchat_t;
void CreateGetChat(getchat_t* chat);
char* GetChats(packet_t* pack,int* size);
void InitGetChat(getchat_t* chat,int max,int min);
void send_query(network_t* network,packet_t* pack,void(*Res)(void*data));
MATHLIBRARY_API void CreateNetwork(network_t* network);
MATHLIBRARY_API void ConnectNetwork(network_t* network,int port);
void UpdatePacket(network_t*network);
#ifdef __cplusplus
}
#endif
// class CORE_API Unit
// {
// public:
//       Unit();
//      virtual void Synhron();
//      void InitModule(sqlite3 *db, std::string table, int id);
//      virtual void Show();
//     int GetId();
//     ~Unit();
// protected:
//     sqlite3 *db;
//     bool init;
//     std::string table;
//     int id;
// };
// class CORE_API Dispens_Unit : public Unit
// {
// public:
//      Dispens_Unit();
//      void Synhron();
//     static  std::vector<Dispens_Unit> StaticGetAllUnit(sqlite3 *db);
//     void Show();
//     void Resize(int width, int heigth);
//     void Move(int x, int y);
//     void GetAllParam(int* width,int* heigth,int* x,int* y);
    
//     ~Dispens_Unit();
//     std::string GetParamDispens_Unit();
// private:
//     int width;
//     int heigth;
//     int x;
//     int y;
    
// };

// class CORE_API AZS
// {
// public:
//     AZS();

//     ~AZS();
//     Dispens_Unit* GetUnit(int index);
//     Dispens_Unit* GetUnitbyId(int id);
//     int GetSizeUnit();

//     bool CheckPassword(std::string password);
    
// private:
//     int id = 1;
//     std::vector<Dispens_Unit> units;
//     sqlite3* AZSdb;
// };
    
