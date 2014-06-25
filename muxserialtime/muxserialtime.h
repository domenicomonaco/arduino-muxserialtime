#define ARRAYN 3;

#include <sstream>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

///http://stackoverflow.com/a/5590404

class MuxSerialTime{
protected:
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
  void config(String ty="none", String ad="none", String divider="#", int skyp=5, long int Multiply=60){

    MuxSerialTime::addr = ad;
    MuxSerialTime::type =  ty;
  
    MuxSerialTime::GroupMultiply=Multiply;
    
    for(int i=0;i<array;i++){
      if(i==0) MuxSerialTime::GroupsDelay[i]=1;
      else MuxSerialTime::GroupsDelay[i]=i*5;
    }

    MuxSerialTime::ValueLineDivider = divider;
    MuxSerialTime::skyps = skyp;

    for(int i=0;i<array;i++){
      MuxSerialTime::GroupsElapsed[i]= millis();
    }
  }

  void putValue(double value){

    if(MuxSerialTime::skyps == 0){
      MuxSerialTime::currentTime = millis();
      for(int i=0;i<array;i++){

          if(
            ((MuxSerialTime::currentTime-MuxSerialTime::GroupsElapsed[i])/1000) 
              >= (MuxSerialTime::GroupMultiply*MuxSerialTime::GroupsDelay[i])
            ) {
            String s = String(i);
          Serial.println(s);
            String timeID = s +"T";
            MuxSerialTime::GroupsElapsed[i] = MuxSerialTime::currentTime;
            PrintTimedStats(MuxSerialTime::grouped[i], timeID ,"MULTI-AVG");
          }

          MuxSerialTime::grouped[i].add(value);
      }

      MuxSerialTime::HEADSerialLine("0T", "SINGLE-INSTANT");
      Serial.println(value);
      
    }else{
      skyps--;
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
