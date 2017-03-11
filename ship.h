#ifndef SHIP_H
#define SHIP_H
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;


class ship
{
public:
    ship();
    ship(std::string t, double ba, double r, bool ac);
    virtual ~ship();
/////////////////////////////////////////////////////////
    void moveLead(double angle);
    void follow(double angle, double x, double y, bool lowf);
////////////////////////////////////////////////////////
    void setSpeed(double x)
    {
        this->speed = x;
    }
    double getSpeed()
    {
        return this->speed;
    }
    double getMaxSpeed()
    {
        return this->maxSpeed;
    }
    ////////////////////////////////////////////////////
    void setFuel (double x)
    {
        this->fuel = x;
    }
    double getFuel()
    {
        return this->fuel;
    }
    /////////////////////////////////////////////////////////
    void setBearing (double x)
    {
        this -> bearing = x;
    }
    double getBearing() {return this->bearing;}
    /////////////////////////////////////////////////////////
    void setlocation (double x, double y, double z)
    {
        this->X=x;
        this->Y=y;
        this->Z=z;
    }
    std::string getType(){return type;}
    void setRf(); ///set all ships temp varaibles

    void display()
    {
        cout << this->X << " " << this->Y << " " << this->bearing - 2 << endl;
    }
    ///These getters will mostly be for getting the fuel ship location for refueling
    double getX() {return this->X;}
    double getY() {return this->Y;}
    double getZ() {return this->Z;}
 /////////////////////////////////////////////////////////////////

protected:

    double X, Y, Z; /// ship location in X and Y plane
    double fuel = 100; /// current fuel in the ship
    double bearing, range; ///relative bearing
    double bowangle; ///angle from the lead ship
    double deltar = .05;
    double speed;
    double maxSpeed;
    std::string type;
    bool aircraft; ///true for airwings and rotary wing (aka Lamps)
    ///bool refuel;///  if true -> message guide
    int ID;


private:
    double PI = 3.14156;


};

#endif // SHIP_H 