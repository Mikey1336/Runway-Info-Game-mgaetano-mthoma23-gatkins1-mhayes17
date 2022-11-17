#include "Runway.h"

//Constructor
Runway::Runway(string name, double windSpeed, double windDirection, double direction) {
    this->name = name;
    this->windSpeed = windSpeed;
    this->windDirection = windDirection;
    this->direction = direction;
    this->land = false;
    this->directionDiff = fmod((direction - windDirection + 180),(360)) - 180;
    this->headWind = windSpeed * sin(fmod((direction - windDirection + 180),(360)) - 180);
    this->crossWind = windSpeed * cos(fmod((direction - windDirection + 180),(360)) - 180);
}

//Getters
string Runway::getName() {
    return name;
}

double Runway::getWindSpeed() {
    return windSpeed;
}

double Runway::getHeadWind() {
    return headWind;
}

double Runway::getCrossWind() {
    return crossWind;
}

double Runway::getDirection() {
    return direction;
}

double Runway::getDirectionDiff() {
    return directionDiff;
}

bool Runway::getLand() {
    return land;
}

//Setters
void Runway::setName(string name) {
    this->name = name;
}

void Runway::setWind(double windSpeed) {
    this->windSpeed = windSpeed;
}

void Runway::setHeadWind(double headWind) {
    this->headWind = headWind;
}

void Runway::setCrossWind(double crossWind) {
    this->crossWind = crossWind;
}

void Runway::setDirectionDiff(double direction, double windDirection) {
    this->directionDiff = fmod((direction - windDirection + 180),(360-180));
}

void Runway::setLanding(bool land) {
    this->land = land;
}

