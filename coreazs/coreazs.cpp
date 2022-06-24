#include "include/coreazs.h"

bool AZS::CheckPassword(std::string password)
{
    if (password == "123")
    {
        return true;
    }
    else
    {
        return false;
    }
}
AZS::AZS()
    {
        sqlite3_open("azs.sqlite", &AZSdb);
        units=Dispens_Unit::StaticGetAllUnit(AZSdb);
    }
 AZS::~AZS()
    {
        sqlite3_close(AZSdb);
        std::cout<<"END AZS\n";
    }
 Unit::Unit()
    {
        init = false;
        db = NULL;
        id = -1;
    }
 Unit::~Unit(){

 }
int Unit::GetId(){
    return id;
}
void Unit::Synhron()
{
}

void Unit::InitModule(sqlite3 *db, std::string table, int id)
{
    this->db = db;
    this->table = table;
    init = true;
    this->id = id;
    Synhron();
}
void Unit::Show()
{
    std::cout << "ID: " << id << " TABLE: " << table << "\n";
}
 Dispens_Unit::Dispens_Unit(){
    
    }
    Dispens_Unit::~Dispens_Unit(){

    }
void Dispens_Unit::Synhron()
{
    if (init)
    {
        std::string sql="SELECT * FROM " + table + " WHERE id = " + std::to_string(id) + ";";
        sqlite3_stmt* res;
        sqlite3_prepare_v2(db,sql.c_str(),-1,&res,0);
        int rc=sqlite3_step(res);
         if (rc == SQLITE_ROW) {
            width=sqlite3_column_int(res,1);
            heigth=sqlite3_column_int(res,2);
            x=sqlite3_column_int(res,3);
            y=sqlite3_column_int(res,4);
            
         }
        sqlite3_finalize(res);
        // SQLite::Statement query(*db,"UPDATE "+table+" SET ContactName = 'Alfred Schmidt', City= 'Frankfurt' WHERE id = "+std::to_string(id)+";");
    }
}
void Dispens_Unit::GetAllParam(int* width,int* heigth,int* x,int* y){
    *width=this->width;
    *heigth=this->heigth;
    *x=this->x;
    *y=this->y;
}
 std::vector<Dispens_Unit> Dispens_Unit::StaticGetAllUnit(sqlite3 *db)
{
    std::string table = "dispensing";
    std::string sql="SELECT id FROM " + table + ";";
    sqlite3_stmt* res;
    sqlite3_prepare_v2(db,sql.c_str(),-1,&res,0);
    std::vector<Dispens_Unit> vdisp;
    while (sqlite3_step(res)==SQLITE_ROW)
    {
        int id = sqlite3_column_int(res,0); // = query.getColumn(0).getInt();

        Dispens_Unit disp;
        disp.InitModule(db, table, id);
        vdisp.push_back(disp);
    }
    sqlite3_finalize(res);
    return std::move(vdisp);
}
std::string Dispens_Unit::GetParamDispens_Unit(){
        std::string param;
        param+="id:"+std::to_string(id)+"|";
        param+="width:"+std::to_string(width)+"|";
        param+="heigth:"+std::to_string(heigth)+"|";
        param+="x:"+std::to_string(x)+"|";
        param+="y:"+std::to_string(y)+"|";
        return param;
    }
void Dispens_Unit::Show()
{
    std::cout << "WIDTH: " << width << " HEIGTH: " << heigth << " X: " << x << " Y: " << y << " ID: " << id << "\n";
}
void Dispens_Unit::Resize(int width, int heigth)
{
    if (init)
    {
        this->width=width;
        this->heigth=heigth;
        std::string sql="UPDATE "+table+" SET width = "+std::to_string(width)+",heigth = "+std::to_string(heigth)+" WHERE id = "+std::to_string(id)+";";
        sqlite3_exec(db,sql.c_str(),0,0,0);
        
        
    }
}
void Dispens_Unit::Move(int x, int y)
{
    if (init)
    {
        this->x=x;
        this->y=y;
         std::string sql="UPDATE "+table+" SET x = "+std::to_string(x)+",y = "+std::to_string(y)+" WHERE id = "+std::to_string(id)+";";
         sqlite3_exec(db,sql.c_str(),0,0,0);
    }
}
 Dispens_Unit* AZS::GetUnit(int index){
        return &units[index];
    }
     Dispens_Unit* AZS::GetUnitbyId(int id){
         for(int i=0;i<units.size();i++){
             if(units[i].GetId()==id){
                 return &units[i];
             }
         }
        return NULL;
    }
    int AZS::GetSizeUnit(){
        return units.size();
    }