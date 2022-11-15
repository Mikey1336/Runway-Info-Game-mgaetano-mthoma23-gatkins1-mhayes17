#ifndef M4OEP_MGAETANO_MTHOMA23_GATKINS1_MHAYES17_RUNWAY_H
#define M4OEP_MGAETANO_MTHOMA23_GATKINS1_MHAYES17_RUNWAY_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using std::string;

class Runway{
    string name;
    double windSpeed;
    double windDirection;
    double direction;
    double headWind;
    double crossWind;
    double directionDiff;
    bool land;

public:
    //Constructor
    Runway(string name, double windSpeed, double windDirection, double direction);

    //Getters
    string getName();
    double getWindSpeed();
    double getHeadWind();
    double getCrossWind();
    double getDirection();
    double getDirectionDiff();
    bool getLand();

    //Setters
    void setName(string name);
    void setWind(double windSpeed);
    void setHeadWind(double headWind);
    void setCrossWind(double crossWind);
    void setDirectionDiff(double direction, double windDirection);
    void setLanding(bool land);


};


#endif //M4OEP_MGAETANO_MTHOMA23_GATKINS1_MHAYES17_RUNWAY_H
