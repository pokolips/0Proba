#include <stdint.h>
#pragma once
#include <Arduino.h>
#include <GyverNTC.h>
// термистор на пине А1 - А3
// сопротивление резистора 10к
// тепловой коэффициент 3950
GyverNTC therm1(0, 10000, 3950);  // морозилка
GyverNTC therm2(1, 10000, 3950);  //  холодилка
GyverNTC therm3(2, 10000, 3950);  //  испарилка (испарение)

class Temperature{ 
  
private:
  int8_t thol = 0;
  int8_t tmor = 0;
  int8_t tisp = 0;
  int8_t tholSt = 0;
  int8_t tmorSt = 0;
  int8_t _thl = 0;
  int8_t _tmr = 0;
  bool _isCheckPass = false;

  public:
    void setTemperature(){
      therm1.getTempAverage();
      therm2.getTempAverage();
       // therm3.getTempAverage(); 
      tmor = therm1.getTempAverage();//Температура морозильника
      thol = therm2.getTempAverage();//Температура холодильника
      tisp = therm3.getTempAverage();//
    }
    int getTempHol(){
      return thol;
    }
    int getTempMor(){
      return tmor;
    }
    int getTempIsp(){
      return tisp;
    }
    
    void setTempOld(uint8_t thl, uint8_t tmr){
      _thl = thl;
      _tmr = tmr;
    }
    uint8_t getOldTemp(){  // Поправить. Не может так быть одновременно.(Подправлено, требует проверки.)
      
      if(_thl == thol && _tmr == tmor){_isCheckPass = false; return 0;}
      if(_thl >= (thol - 2)){_isCheckPass = true; return 1;}//временно убрано в основном цикле
      if(_thl <= (thol - 2)){_isCheckPass = true; return 2;}//временно убрано в основном цикле
      if(_tmr >= (tmor - 2)){_isCheckPass = true; return 3;}//
      if(_tmr <= (tmor - 2)){_isCheckPass = true; return 4;}
    }
    bool getCheckPasss(){
      return _isCheckPass;
    }
    
//h


};
