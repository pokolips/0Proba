#include <stdint.h>
#pragma once
#include <Arduino.h>

class Hranenie{
  public:

  void setKn(bool kn){
    _kn = kn;
   }
   bool getKn(){
    return _kn;
   }
  //  uint8_t 
  private:
  bool _kn = false;
  
};