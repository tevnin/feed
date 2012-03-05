//
//  ofxTimeUtils.cpp
//  Created by Martial Geoffre-Rouland on 22/09/2011.
//  
//

#include "ofxTimeUtils.h"

ofxTimeUtils::ofxTimeUtils () {
    ofAddListener(ofEvents.update, this, &ofxTimeUtils::update);
}


string ofxTimeUtils::getCurrentDate() {
    
    return ofToString(currentDay) + "/" + ofToString(currentMonth) +"/" + ofToString("currentYear") + " " + ofToString(currentHour) + ":" + ofToString(currentMinut);
}


int ofxTimeUtils::convertHoursToSeconds(int hour, int minuts) {
    return convertHoursToSeconds (hour * 60) + convertMinutsToSeconds(minuts);
}

int ofxTimeUtils::convertHoursToSeconds(int hour) {
    return convertMinutsToSeconds (hour * 60);
}

int ofxTimeUtils::convertMinutsToSeconds(int minuts) {
    return  minuts * 60;
}

void ofxTimeUtils::update(ofEventArgs & e) {
    
    time_t t = time(0);
    currentUnixTime = (long)t;
    
    time_t rawtime;
    struct tm * timeinfo;
    char year [80];
    char month [80];
    char day [80];
    char hour [80];
    char minut [80];
    time ( &rawtime );
    
    timeinfo = localtime ( &rawtime );
    
    strftime (year,80,"%Y",timeinfo);
    strftime (month,80,"%m",timeinfo);
    strftime (day,80,"%d",timeinfo);
    strftime (hour,80,"%H",timeinfo);
    strftime (minut,80,"%M",timeinfo);
    
    
    currentYear = ofToInt(year);
    currentMonth = ofToInt(month);
    currentDay = ofToInt(day);
    currentHour =  ofToInt(hour);
    currentMinut =  ofToInt(minut);
}