#include "ship.h"

ship::ship(std::string t, double ba, double r, bool ac)
{
    type = t;
    bowangle = ba * PI;
    range = r;
    aircraft = ac;//ctor

}

void ship::setRf()
{
    //this->fx = this -> X;   ///Save current locations
    //this->fy = this -> Y;
    //this->fbearing = 200;
}

void ship::moveLead(double angle)
{
    //cout<< this -> fuel << endl;
    ///get our fuel calculations set up
    double f=0.0; /// fuel percentage used in who numbers
    double c1 = 0.000556; ///factors that effect our fuel usage
    double c2 = -0.000699;
        f=100*(c1*this->speed*this->speed + (c2*this->speed))/2.0; ///fuel percentage calculation
        if(f<2.0)
        {
            f=2.0; ///Garuntee atleast 2% is used
        }
        f = f/100; ///change the percentage into a decimal
    //cout << f << endl;
    f = this->fuel*f; ///Take the percentage of our current fuel stock
    //cout << f << endl;
    f = this->fuel-f; ///take the amount calculated and subtract it from our main ship
    this->setFuel(f); ///set our fuel to the new amount
    //cout<< this -> fuel << endl;
//////////////////////////////////////////////////////////////////

    //normal_distribution<double> bdist (0, 5.0/2.0); ///bearing distribution
    double dx, dy;
    double dz = 0;
    //double theta = 0.0; ///course correction variable

    double alpha = 0.0; /// course correction angle


    dx = this->speed*cos(angle); ///movement directions and length
    dy = this->speed*sin(angle);

    dx = dx + this->getX(); /// add the movement lengths to our current positions
    dy = dy + this->getY();

    this->setlocation(dx, dy, dz);
}

void ship::follow(double angle, double leadX, double leadY, bool lowf)
{
    default_random_engine gen(time(NULL)); ///Random Number Generator
    normal_distribution<double> bdist(0,5.0/2.0); ///Bearing Distribution
    normal_distribution<double> rdist(0,deltar*range/2); ///Range Distribution
    double tempX, tempY;
    double dbearing = angle + bdist(gen);///bearing variation
    double drange = this->range + rdist(gen); ///range variation
    ///This calculation will assume each time that the bearing and range were meant to be the same as the lead,
    /// and varied after acquiring that exact match

    if (lowf == true) {drange = 200;} ///for use in the refueling calculations
    this->X = (cos(this->bowangle+dbearing)*drange) + leadX;
    this->Y = (sin(this->bowangle+dbearing)*drange) + leadY;
    //cout << this-> X << " " << this->Y << endl;
    //cout << leadX << " " << leadY << endl;
}

ship::~ship()
{
    //dtor
}