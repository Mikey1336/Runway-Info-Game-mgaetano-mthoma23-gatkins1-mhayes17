#include "Runway.h"
#include <time.h>
using namespace std;


/*
int main(){
    cout << "*** Welcome to the Landing Game! ***" << endl;
    cout << "** Based on the image above, choose the runway safest to land on! **" << endl;
    //Random wind Direction
    srand(time(NULL));
    double windDirection = rand() % 360 +1;
    //Random wind Speed
    double windSpeed = rand() % 31;
    cout << "Today's wind speed is: " << windSpeed << " mph" << endl;
    cout << "Today's wind is coming from: " << windDirection << " degrees" << endl;
    //Create Runways
    Runway r13("r13", windSpeed , windDirection, 130);
    Runway r31("r31", windSpeed, windDirection, 310);
    Runway r9("r9", windSpeed, windDirection, 90);
    Runway r27("r27", windSpeed, windDirection, 270);
    if(r13.getHeadWind() < 0){
        cout << r13.getName() << " - Tailwind: " << r13.getHeadWind() * -1 << " mph, Crosswind: "; (r13.getCrossWind() < 0) ? (cout << r13.getCrossWind() * -1 << " mph from left" << endl) : (cout << r13.getCrossWind() << " mph from right" << endl);
    } else {
        cout << r13.getName() << " - Headwind: " << r13.getHeadWind() << " mph, Crosswind: "; (r13.getCrossWind() < 0) ? (cout << r13.getCrossWind() * -1 << " mph from left" << endl) : (cout << r13.getCrossWind() << " mph from right" << endl);
    }
    if(r31.getHeadWind() < 0){
        cout << r31.getName() << " - Tailwind: " << r31.getHeadWind() * -1 << " mph, Crosswind: "; (r31.getCrossWind() < 0) ? (cout << r31.getCrossWind() * -1 << " mph from left" << endl) : (cout << r31.getCrossWind() << " mph from right" << endl);
    } else {
        cout << r31.getName() << " - Headwind: " << r31.getHeadWind() << " mph, Crosswind: "; (r31.getCrossWind() < 0) ? (cout << r31.getCrossWind() * -1 << " mph from left" << endl) : (cout << r31.getCrossWind() << " mph from right" << endl);
    }
    if(r9.getHeadWind() < 0){
        cout << r9.getName() << " - Tailwind: " << r9.getHeadWind() * -1 << " mph, Crosswind: "; (r9.getCrossWind() < 0) ? (cout << r9.getCrossWind() * -1 << " mph from left" << endl) : (cout << r9.getCrossWind() << " mph from right" << endl);
    } else {
        cout << r9.getName() << " - Headwind: " << r9.getHeadWind() << " mph, Crosswind: "; (r9.getCrossWind() < 0) ? (cout << r9.getCrossWind() * -1 << " mph from left" << endl) : (cout << r9.getCrossWind() << " mph from right" << endl);
    }
    if(r27.getHeadWind() < 0){
        cout << r27.getName() << " - Tailwind: " << r27.getHeadWind() * -1 << " mph, Crosswind: "; (r27.getCrossWind() < 0) ? (cout << r27.getCrossWind() * -1 << " mph from left" << endl) : (cout << r27.getCrossWind() << " mph from right" << endl);
    } else {
        cout << r27.getName() << " - Headwind: " << r27.getHeadWind() << " mph, Crosswind: "; (r27.getCrossWind() < 0) ? (cout << r27.getCrossWind() * -1 << " mph from left" << endl) : (cout << r27.getCrossWind() << " mph from right" << endl);
    }
    cout << "r13: " << r13.getDirectionDiff() << endl;
    cout << "r31: " << r31.getDirectionDiff() << endl;
    cout << "r9: " << r9.getDirectionDiff() << endl;
    cout << "r27: " << r27.getDirectionDiff() << endl;
    vector<Runway> runways;
    runways.push_back(r13);
    runways.push_back(r31);
    runways.push_back(r9);
    runways.push_back(r27);
    double lowestVal = abs(r13.getDirectionDiff());
    string correct = "r13";
    for (Runway r : runways){
        if(abs(r.getDirectionDiff()) < lowestVal){
            lowestVal = r.getDirectionDiff();
            correct = r.getName();
            r.setLanding(true);
        }
    }
    cout << "* Based on the information, what runway would be optimal for landing? *"  << endl;
    string ans;
    cin >> ans;
    if (ans == correct){
        cout << "congrats!" << endl;
    }else{
        cout << "Oops! Wrong answer :(" << endl;
        cout << "The correct answer is " << correct << endl;
    }
}
*/