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
void Unit::Synhron()
{
}
void Unit::InitModule(SQLite::Database *db, std::string table, int id)
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
void Dispens_Unit::Synhron()
{
    if (init)
    {
        SQLite::Statement query(*db, "SELECT * FROM " + table + " WHERE id = " + std::to_string(id) + ";");
        query.executeStep();
        width = query.getColumn(1).getInt();
        heigth = query.getColumn(2).getInt();
        x = query.getColumn(3).getInt();
        y = query.getColumn(4).getInt();
        // SQLite::Statement query(*db,"UPDATE "+table+" SET ContactName = 'Alfred Schmidt', City= 'Frankfurt' WHERE id = "+std::to_string(id)+";");
    }
}
void Dispens_Unit::GetAllParam(int* width,int* heigth,int* x,int* y){
    *width=this->width;
    *heigth=this->heigth;
    *x=this->x;
    *y=this->y;
}
std::vector<Dispens_Unit> Dispens_Unit::StaticGetAllUnit(SQLite::Database *db)
{
    std::string table = "dispensing";
    SQLite::Statement query(*db, "SELECT id FROM " + table + ";");
    std::vector<Dispens_Unit> vdisp;
    while (query.executeStep())
    {
        int id = query.getColumn(0).getInt(); // = query.getColumn(0).getInt();
        Dispens_Unit disp;
        disp.InitModule(db, table, id);
        vdisp.push_back(disp);
    }
    return std::move(vdisp);
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
        SQLite::Statement query(*db,"UPDATE "+table+" SET width = "+std::to_string(width)+",heigth = "+std::to_string(heigth)+" WHERE id = "+std::to_string(id)+";");
        query.exec();
    }
}
void Dispens_Unit::Move(int x, int y)
{
    if (init)
    {
        this->x=x;
        this->y=y;
        SQLite::Statement query(*db,"UPDATE "+table+" SET x = "+std::to_string(x)+",y = "+std::to_string(y)+" WHERE id = "+std::to_string(id)+";");
        query.exec();
    }
}