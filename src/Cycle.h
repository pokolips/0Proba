
#pragma once
#include <stdint.h>
#include <Arduino.h>
//#include "Dano.h"

class Cycle {
  public:
      int8_t goCompr(int8_t thl, int8_t tmr);//
       
      bool getKlapan(bool kn);//

      //Включение компрессора
      uint8_t WorkCompressor(bool go);

  private:
      void setKlapan (bool klapan);//
      int8_t _thl;//
      int8_t _tmr;//
      uint8_t _comprGo;//
      uint8_t _minTempHol = 15;//
      uint8_t _minTempMor = 2;//
      uint8_t _nomTempHol = 18;//
      uint8_t _nomTempMor = 5;//
      bool _klpn;//
      bool _flag;//
      bool _kn;//
      bool _wrkCompr;//
      const uint8_t _klapan = 7;//

};
// Cycle::Cycle{
// _thl = thl;
// _tmr = tmr;
// }
