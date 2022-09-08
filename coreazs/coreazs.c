#include "include/coreazs.h"
void CreateNetwork(network_t* network){
    network->dllverison=MAKEWORD(2,1);
    if(WSAStartup(network->dllverison,&network->wsaData)!=0){
        printf("ERROR\n");
        exit(1);
    }
    network->idquery=0;
}
void UpdatePacket(network_t*network){
    while(1){
        char buff[1024];
        recv(network->conn,buff,1024,NULL);
        printf("CHECK\n");
    }
}
void InitPacket(packet_t* pack,int id,char*(*GetStrPacket)(struct packet* pack,int* size)){
    pack->id=id;
    pack->GetStrPacket=GetStrPacket;
}
char* GetChats(packet_t* pack,int* size){
    getchat_t* chat=(getchat_t*)pack;
    *size=15;
    char* test=malloc(*size);
    char max[100];
    sprintf(max, "%d",chat->max);
    strcpy(test,"max ");
    strcpy(&test[4],max);
    return test;
}
void CreateGetChat(getchat_t* chat){
    InitPacket(&chat->pack,1,GetChats);
    chat->max=0;
    chat->min=0;
}
void InitGetChat(getchat_t* chat,int max,int min){
    InitPacket(&chat->pack,1,GetChats);
    chat->max=max;
    chat->min=min;
}
void send_query(network_t* network,packet_t* pack,void(*Res)(void*data)){
    network->idquery++;
    int sizepacket=0;
    char* arrpack=pack->GetStrPacket(pack,&sizepacket);
    //
    char packidstr[100];
    sprintf(packidstr, "%d", pack->id);
    int lengthidpack=strlen(packidstr);
    //
    char sizepacketstr[100];
    sprintf(sizepacketstr, "%d", sizepacket);
    int lengthsizepacket=strlen(sizepacketstr);
    //
    char idquerystr[100];
    sprintf(idquerystr, "%d", network->idquery);
    int lengthqueryid=strlen(idquerystr);
    //
    int size=1+lengthidpack+1+lengthsizepacket+1+lengthqueryid+1+sizepacket;
    char* data=malloc(size);
    int index=1;
    data[0]='#';
    memcpy(&data[index],packidstr,lengthidpack);
    index+=lengthidpack;
    data[index]='|';
    index++;
    memcpy(&data[index],sizepacketstr,lengthsizepacket);
    index+=lengthsizepacket;
    data[index]='|';
    index++;
    memcpy(&data[index],idquerystr,lengthqueryid);
    index+=lengthqueryid;
    data[index]='|';
    index++;
    memcpy(&data[index],arrpack,sizepacket);
    index+=sizepacket;
   
    printf("DATA: %s\n",data);
    free(arrpack);
    send(network->conn,data,size,NULL);
}
char* Test(int* size){
    *size=4;
    char* test=malloc(4);
    strcpy(test,"tes");
    return test;
}
void ConnectNetwork(network_t* network,int port){
    CreateNetwork(network);
    network->addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    network->addr.sin_port=htons(port);
    network->addr.sin_family=AF_INET;
    network->conn=socket(AF_INET,SOCK_STREAM,NULL);
    if(connect(network->conn,(SOCKADDR*)&network->addr,sizeof(network->addr))!=0){
        printf("ERROR Connect\n");
        return;
    }
    printf("Connect\n");
    // getchat_t chat;
    // InitGetChat(&chat,10,20);
    // send_query(network,&chat,NULL);
   int length=send(network->conn,"\r#$^|2|10|7|1234",17,NULL);
   printf("LENGTH: %d",length);
   length=send(network->conn,"\r#$^|2|10|6|12345",18,NULL);
   printf("LENGTH: %d",length);
}

// bool AZS::CheckPassword(std::string password)
// {
//     if (password == "123")
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }
// AZS::AZS()
//     {
//         sqlite3_open("azs.sqlite", &AZSdb);
//         units=Dispens_Unit::StaticGetAllUnit(AZSdb);
//     }
//  AZS::~AZS()
//     {
//         sqlite3_close(AZSdb);
//         std::cout<<"END AZS\n";
//     }
//  Unit::Unit()
//     {
//         init = false;
//         db = NULL;
//         id = -1;
//     }
//  Unit::~Unit(){

//  }
// int Unit::GetId(){
//     return id;
// }
// void Unit::Synhron()
// {
// }

// void Unit::InitModule(sqlite3 *db, std::string table, int id)
// {
//     this->db = db;
//     this->table = table;
//     init = true;
//     this->id = id;
//     Synhron();
// }
// void Unit::Show()
// {
//     std::cout << "ID: " << id << " TABLE: " << table << "\n";
// }
//  Dispens_Unit::Dispens_Unit(){
    
//     }
//     Dispens_Unit::~Dispens_Unit(){

//     }
// void Dispens_Unit::Synhron()
// {
//     if (init)
//     {
//         std::string sql="SELECT * FROM " + table + " WHERE id = " + std::to_string(id) + ";";
//         sqlite3_stmt* res;
//         sqlite3_prepare_v2(db,sql.c_str(),-1,&res,0);
//         int rc=sqlite3_step(res);
//          if (rc == SQLITE_ROW) {
//             width=sqlite3_column_int(res,1);
//             heigth=sqlite3_column_int(res,2);
//             x=sqlite3_column_int(res,3);
//             y=sqlite3_column_int(res,4);
            
//          }
//         sqlite3_finalize(res);
//         // SQLite::Statement query(*db,"UPDATE "+table+" SET ContactName = 'Alfred Schmidt', City= 'Frankfurt' WHERE id = "+std::to_string(id)+";");
//     }
// }
// void Dispens_Unit::GetAllParam(int* width,int* heigth,int* x,int* y){
//     *width=this->width;
//     *heigth=this->heigth;
//     *x=this->x;
//     *y=this->y;
// }
//  std::vector<Dispens_Unit> Dispens_Unit::StaticGetAllUnit(sqlite3 *db)
// {
//     std::string table = "dispensing";
//     std::string sql="SELECT id FROM " + table + ";";
//     sqlite3_stmt* res;
//     sqlite3_prepare_v2(db,sql.c_str(),-1,&res,0);
//     std::vector<Dispens_Unit> vdisp;
//     while (sqlite3_step(res)==SQLITE_ROW)
//     {
//         int id = sqlite3_column_int(res,0); // = query.getColumn(0).getInt();

//         Dispens_Unit disp;
//         disp.InitModule(db, table, id);
//         vdisp.push_back(disp);
//     }
//     sqlite3_finalize(res);
//     return std::move(vdisp);
// }
// std::string Dispens_Unit::GetParamDispens_Unit(){
//         std::string param;
//         param+="id:"+std::to_string(id)+"|";
//         param+="width:"+std::to_string(width)+"|";
//         param+="heigth:"+std::to_string(heigth)+"|";
//         param+="x:"+std::to_string(x)+"|";
//         param+="y:"+std::to_string(y)+"|";
//         return param;
//     }
// void Dispens_Unit::Show()
// {
//     std::cout << "WIDTH: " << width << " HEIGTH: " << heigth << " X: " << x << " Y: " << y << " ID: " << id << "\n";
// }
// void Dispens_Unit::Resize(int width, int heigth)
// {
//     if (init)
//     {
//         this->width=width;
//         this->heigth=heigth;
//         std::string sql="UPDATE "+table+" SET width = "+std::to_string(width)+",heigth = "+std::to_string(heigth)+" WHERE id = "+std::to_string(id)+";";
//         sqlite3_exec(db,sql.c_str(),0,0,0);
        
        
//     }
// }
// void Dispens_Unit::Move(int x, int y)
// {
//     if (init)
//     {
//         this->x=x;
//         this->y=y;
//          std::string sql="UPDATE "+table+" SET x = "+std::to_string(x)+",y = "+std::to_string(y)+" WHERE id = "+std::to_string(id)+";";
//          sqlite3_exec(db,sql.c_str(),0,0,0);
//     }
// }
//  Dispens_Unit* AZS::GetUnit(int index){
//         return &units[index];
//     }
//      Dispens_Unit* AZS::GetUnitbyId(int id){
//          for(int i=0;i<units.size();i++){
//              if(units[i].GetId()==id){
//                  return &units[i];
//              }
//          }
//         return NULL;
//     }
//     int AZS::GetSizeUnit(){
//         return units.size();
//     }