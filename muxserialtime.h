
/**
 *
 * Author: Domenico Monaco, domenico.monaco@kiuz.it - monaco.kiuz.it
 *
 * Description: This class manage aggregation of temporal data acquisition
 *
 * Version: 0.1.3
 *
 * Date: 17/07/2014
 * License: GPL v2
 * Copyright: Domenico Monaco
 *
 **/

#include "Statistic.h"
#include "Arduino.h"
#include <string>

class MuxSerialTime{
protected:
    
    static const int numAggr = 3;
    
    static const int delayDiff = 5;
    
    String ValueLineDivider;
    
    bool syncTime;
    char* LastDateTime;
    char* zone;
    
    static const long int SecondsInM = 60;
    
    long int AggrDelay[numAggr];
    Statistic Aggregation[numAggr];
    
    long int AggrMillisElapsed[numAggr];
    long int currentMillis;
    
    int skips;
    
    String type;
    String addr;
    
public:
    
    /**
     * Enable to using time by Arduino
     * Recieve String of time in ISO format
     */
    void enableTime(char* date, char* z){
        
        LastDateTime = date;
        zone = z;
        syncTime = true;
    }
    
    
    /**
     * Make configuration of this class
     * ty = type of sensor
     * ad = address of sensor
     * divider = symbol used to divide values into serial outputs
     * sk = numbers of skips befor read
     */
    void config(String ty="none", String ad = "none", String divider = "#", int sk=5){
        syncTime=false;
        MuxSerialTime::addr = ad;
        MuxSerialTime::type =  ty;
        
        for(int i=0;i<numAggr;i++){
            if(i==0) MuxSerialTime::AggrDelay[i] = 1;
            else MuxSerialTime::AggrDelay[i]= i * delayDiff;
        }
        
        MuxSerialTime::ValueLineDivider = divider;
        MuxSerialTime::skips = sk;
        
        for(int i=0;i<numAggr;i++){
            MuxSerialTime::AggrMillisElapsed[i]= millis();
        }
    }
    
    /**
     * put new value with new time
     */
    void putValue(char* date, double value){
        if(syncTime==true){
            LastDateTime = date;
        }
        putValue(value);
    }
    
    /**
     *
     * put new only new value
     */
    void putValue(double value){
        
        MuxSerialTime::currentMillis = millis();
        
        if(MuxSerialTime::skips == 0){
            
            for(int i=0;i<numAggr;i++){
                if(
                   ((MuxSerialTime::currentMillis-MuxSerialTime::AggrMillisElapsed[i])/1000)
                   >= (MuxSerialTime::SecondsInM*MuxSerialTime::AggrDelay[i])
                   ) {
                    
                    /**
                     * ISSUE#1: changed 0T,1T...nT ID into 0M,1M...nM
                     * where n are size of time aggregation
                     *
                     * BUGFIX#1: fixed problem of conversion int into string
                     * with String() arduino function
                     **/
                    
                    String timeSizeToString = String(MuxSerialTime::AggrDelay[i]);
                    String timeID = (timeSizeToString + "M");
                    
                    MuxSerialTime::AggrMillisElapsed[i] = MuxSerialTime::currentMillis;
                    
                    PrintTimedStats(MuxSerialTime::Aggregation[i], timeID ,"A");
                    
                    MuxSerialTime::Aggregation[i]=Statistic();
                    MuxSerialTime::Aggregation[i].clear();
                    
                }
                
                MuxSerialTime::Aggregation[i].add(value);
            }
            
            /**
             * ISSUE#1: changed 0T,1T...nT ID into 0M,1M...nM
             * where n are size of time aggregation
             **/
            MuxSerialTime::HEADSerialLine("0M", "S");
            Serial.println(value);
            
        }else{
            skips--;
        }
    }
    
    void PrintTimedStats(Statistic group, String IDLine, String ValueType){
        MuxSerialTime::HEADSerialLine(IDLine,ValueType);
        MuxSerialTime::BODYSerialLine(group);
    }
    
    void BODYSerialLine(Statistic group){
        Serial.print(group.average());
        Serial.print(MuxSerialTime::ValueLineDivider);
        Serial.print(group.minimum());
        Serial.print(MuxSerialTime::ValueLineDivider);
        Serial.print(group.maximum());
        Serial.print(MuxSerialTime::ValueLineDivider);
        Serial.println(group.pop_stdev());
        group.clear();
    }
    
    void HEADSerialLine(String IDLine, String TypeValue){
        
        if(syncTime ==true){
            Serial.print(LastDateTime);
            Serial.print(MuxSerialTime::ValueLineDivider);
            Serial.print(zone);
            Serial.print(MuxSerialTime::ValueLineDivider);
            
        }else{
            Serial.print("-");
            Serial.print(MuxSerialTime::ValueLineDivider);
            Serial.print("-");
            Serial.print(MuxSerialTime::ValueLineDivider);
            Serial.print("-");
            Serial.print(MuxSerialTime::ValueLineDivider);
        }
        
        Serial.print(IDLine);
        Serial.print(MuxSerialTime::ValueLineDivider);
        Serial.print(MuxSerialTime::type);
        Serial.print(MuxSerialTime::ValueLineDivider);
        Serial.print(MuxSerialTime::addr);
        Serial.print(MuxSerialTime::ValueLineDivider);
        Serial.print(TypeValue);
        Serial.print(MuxSerialTime::ValueLineDivider);
    }
};
