#include <list>
#include "ship.h"
#include "sub.h"

///I could have left the objects alone as regular objects instead of making them pointers, but I wanted to experiment more with pointers,
///Overcome some anxiety I have surrounding them
using namespace std;

int main()
{
	sub marine;
    list<ship>::iterator myitr;  ///Set some private variables
    list<ship>fleet;
    ship * sptr; ///ship pointer for making new ships
    /// ship * head; ///Don't lose your head
    fstream fout, fout2;
    string fname, outfile;
    double toTurn; ///how much do you want to turn?
    string decide = "y"; ///do we go again?
    double PI = 3.14156; ///Just in case
    bool lowF = false;
    bool topped = false;
///////////////////////////////////////////////////////
    ///I will hard code the needed ships settings in place, instead of using a creation loop to speed up testing
    sptr = new ship("carrier",0,0, true); ///Head carrier
    fleet.push_back(*sptr);
    sptr = new ship("fuel", 1, 100, false);/// Fuel Ship
    fleet.push_back(*sptr);
    sptr = new ship("ddg", .5, 300, true);/// DDG Lamps
    fleet.push_back(*sptr);
    sptr = new ship("ddg2", 1.5, 300, false);/// DDG no-Lamps
    fleet.push_back(*sptr);
    sptr = new ship("frigate", .75, 300, true);/// Frigate
    fleet.push_back(*sptr);
    sptr = new ship("missle", 1.25, 300, false);/// Missle Cruiser
    fleet.push_back(*sptr);
    sptr = new ship("Sub", 0, 300, false);/// Submarine
    fleet.push_back(*sptr);
////////////////////////////////////////////////////////////////////
    myitr=fleet.begin();                ///Let's set the fleet's base stats
    myitr->setBearing(0);
    myitr->setSpeed(10);
    myitr->setlocation(0,0,0);
///////////////////////////////////////////////////////////////////
    fout2.open("command.txt",ios::out); ///build the command file
    fout2<<"set view (60 , 45, 45)"<<endl;
    fout2 << "set ylabel \"x\"" << endl;
    fout2 << "set ylabel \"y\"" << endl;
    fout2<<"set xrange [-1000:1000]"<<endl;
    fout2<<"set yrange [-1000:1000]"<<endl;
    fout2<<"set zrange [-100:100]"<<endl;
    fout2<<"set mapping cylindrical"<<endl;
    ///fout2<<"set angles radians"<<endl;
    fout2<<"set terminal png"<<endl;
////////////////////////////////////////////////////////////////
    cout << "Starting bearing is 0" << endl;
    int i=0; ///Use this to keep track of file names
    while (decide == "y") ///Begin movement
    {
        double days; ///How many days are we moving?
        double dSpeed; ///Our new speed
        cout << "Captain, should we begin changing course?" << endl
             << "[In whole radians, Pi will be added]" << endl;
        cin >> toTurn;
        cout << "What is our current speed, captain?" << endl;
        cin >> dSpeed;
        myitr->setSpeed(dSpeed);
        cout << "How long should we hold this course, sir?" << endl;
        cin >> days;
        ///cout << "Will our sub change? [Depth, angle change]" << endl;
//////////////////////////////////////////////////////////
        ///Calculate Our bearing
        toTurn = (2 *(PI)) - (toTurn * PI); ///In the navy angles go clockwise instead of counter clockwise.
        toTurn = myitr->getBearing() + toTurn; ///add the change in angle to the current bearing to get our new bearing
///I tried previously to do this in the moveLead function, but it caused a loop of constantly changing my bearing
//////////////////////////////////////////////////////////
        for(int j=0; j<days; j++) /// take our input settings
        {
            double headX; ///Values to hold the leaders position
            double headY; ///tried to use a head pointer but it didn't pan out as I hoped
            //head = fleet.begin();/// give us a pointer to the lead ship at all times
            fname="position_"+to_string(i)+".dat";
            outfile="position_"+to_string(i)+".png";
            cout<<fname<<endl;
            ///we take the string, turn it into a char []
            ///so that we can use it as a filename for output
            fout.open(fname.c_str(),ios::out);
///////////////////////////////////////////////////////////////////////////

            if (lowF == true)
            {
                double fx, fy; ///X and y locations of the fuel ship, as well as bearing
                double fspeed = 13;/// these are used in the main file to avoid having unecisarry variables used in the other ships
                //////////////////////////////////////////////////////////
                myitr->setSpeed(fspeed); ///this bit sets our lead with the refuel speed
                myitr->moveLead(toTurn);///move our lead with new speed
                fout << myitr->getX() << " " << myitr->getY() << " " << myitr->getZ() << endl; 
                headX = myitr->getX();
                headY = myitr->getY();
                myitr->setFuel(100);
                myitr++;
                /////////////////////////////////////////////
                myitr->setSpeed(fspeed); ///Set move our fuel into position
                myitr->follow(toTurn, headX, headY, false); ///follow the leader
                fout << myitr->getX() << " " << myitr->getY() << " " << myitr->getZ() << endl; ///print out
                fx = myitr->getX();
                fy= myitr->getY();
                myitr++;

                //////////////////////////////////////////////////////////
                ///myitr = fleet.begin();
                while (myitr != fleet.end())
                {
                    myitr->setSpeed(fspeed); ///move the rest of the fleet around the fuel ship
                    myitr->follow(toTurn, fx, fy, true); ///follow the leader
                    fout << myitr->getX() << " " << myitr->getY() << " " << myitr->getZ() << endl; ///print out
                    myitr++; ///next boat
                }
                lowF=false;

            }

/////////////////////////////////////////////////////////////////////////////////////////////

            else
            {
                if (myitr->getFuel() <=70) ///If our lead ship is at 70% or less fuel, reduce speed and signal fleet
                {
                    lowF = true;
                    myitr ->setSpeed(13);
                }
                myitr->moveLead(toTurn); ///Move our first ship
                headX = myitr->getX();
                headY = myitr->getY();
                    fout << myitr->getX() << " " << myitr->getY() << " " << myitr->getZ() << endl; ///print out

////////////////////////////////////////////////////////////////////////
                myitr++;
                while (myitr != fleet.end()) ///Begin moving the rest of the fleet
                {
                    myitr->setSpeed(dSpeed); ///Set the speed
                    myitr->follow(toTurn, headX, headY, false); ///follow the leader
                    fout << myitr->getX() << " " << myitr->getY() << " " << myitr->getZ() << endl; ///print out
                    myitr++; ///next boat
                }
            }
            ///test = test+5;
            fout.close();

            fout2<<"set output \'"<<outfile<<"\'"<<endl;
            fout2<<"splot \'"<<fname<<"\' with circles"<<endl;
            ///fout2<<"-1"<<endl;
            i++;
            myitr = fleet.begin();
        }
        cout << "would you like to continue? [y]/[n]" << endl;
        cin >> decide;


    }
    fout2.close();
    system("gnuplot command.txt");
    return 0;
}
