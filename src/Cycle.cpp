#include "Cycle.h"
//********** Запуск компрессора ********** 
int8_t Cycle::goCompr(int8_t thl, int8_t tmr){
  _thl = thl;
  _tmr = tmr;
  if(_thl <= _minTempHol || _tmr <= _minTempMor){
    _comprGo = 0;
  } else if(_thl <= _nomTempHol && _tmr <= _nomTempMor){
            _comprGo = 0;
          } else if(_thl > _nomTempHol || _tmr > _nomTempMor){
                    _comprGo = 1;
                  } return _comprGo; 
}
//********** Запуск  **********
void Cycle::setKlapan (bool klapan) { //Рабочая проверка  клапана
  _klpn = klapan;
  if(_thl > _nomTempHol && _tmr > _nomTempMor) { 
   _klpn = true;
  } else if (_thl > _nomTempHol || _tmr > _nomTempMor) {
          if (_thl < _nomTempHol && _klpn == true) { 
            _flag = true;
          } else if (_tmr < _nomTempMor && _klpn == false) {
            _flag = true;
          } else if(_thl < _nomTempHol && _klpn == false){
            _flag = false;
          } else if(_tmr < _nomTempMor && _klpn == true){
            _flag = false;
          } // Дописать метод клапана тут не до конца написано!!!
  }
}
bool Cycle::getKlapan(bool kn){
  _klpn = kn;
  setKlapan (_klpn);
  if(_flag){
   digitalWrite(_klapan,HIGH);
    delay (5);
    digitalWrite(_klapan,LOW);
    delay (5);
    _kn = !_kn;

  } return _kn;
}
uint8_t Cycle::WorkCompressor(bool go){
  if(go){
    _wrkCompr = !_wrkCompr;
  }
    else _wrkCompr =_wrkCompr;
    return _wrkCompr;
 }
/*
if(tmor > nomTempMor && kn == true) {klapan(kn);}
if(tmor >nomTempMor && kn == false){
if(thol > nomTempHol){}
}
*/
