
 

#include "Statistic.h"
#include "Arduino.h"
#include <string>


#define ARRAYN 3;

class MuxSerialTime{
private:
  static const int array=3;

  String ValueLineDivider;

  long int GroupMultiply;

  long int GroupsDelay[array];
  Statistic grouped[array];

  long int GroupsElapsed[array];
  long int currentTime;

  int skyps;

  String type;
  String addr;

public:
  MuxSerialTime(String type="none", String addr="none", String divider="#", int skyp=5, long int Multiply=60){

    addr = addr;
    type =  type;
  
    GroupMultiply=Multiply;
    
    for(int i=0;i<=array;i++){
      if(i==0) GroupsDelay[i]=1;
      else GroupsDelay[i]=i*5;
    }

    ValueLineDivider = divider;
    skyps = skyp;

    for(int i=0;i<array;i++){
      GroupsElapsed[i]= millis();
    }
  }

  void putValue(double value){
    
    currentTime = millis();

    for(int i=0;i<=array;i++){

        if(
          ((currentTime-GroupsElapsed[i])/1000) 
            >= (GroupMultiply*GroupsDelay[i])
          ) {

          String timeID = i + "T";
          GroupsElapsed[i] = currentTime;
          PrintTimedStats(grouped[i], timeID ,"MULTI-AVG");
        }

        grouped[i].add(value);
    }

  HEADSerialLine("0T", "SINGLE-INSTANT");
  Serial.print(value);
  Serial.print(ValueLineDivider);

  }


  void PrintTimedStats(Statistic group, String IDLine, String ValueType){
    HEADSerialLine(IDLine,ValueType);
    BODYSerialLine(group);
  }
 
  void BODYSerialLine(Statistic group){
    Serial.print(group.average());
    Serial.print(ValueLineDivider);
    Serial.print(group.minimum());
    Serial.print(ValueLineDivider);
    Serial.print(group.maximum());
    Serial.print(ValueLineDivider);
    Serial.println(group.pop_stdev());
    group.clear();
  }

  void HEADSerialLine(String IDLine, String TypeValue){
    Serial.print(IDLine);
    Serial.print(ValueLineDivider);
    Serial.print(type);
    Serial.print(ValueLineDivider);
    Serial.print(addr);
    Serial.print(ValueLineDivider);
    Serial.print(TypeValue);
    Serial.print(ValueLineDivider);
  }

};
