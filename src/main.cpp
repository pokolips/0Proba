#include <Arduino.h>

#include <Wire.h>
#include <OneWire.h>
#include <U8glib.h>
#include "Temperature.h"
#include "Dano.h"
#include "Cycle.h"
#include "Hranenie.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);
Temperature termo;
Cycle cycl;
Hranenie sklad;

//####### Функция температуры #######
void getTempAdd() {
  termo.setTemperature();     //Запрос на считывание температуры с датчиков
  thol = termo.getTempHol();  //Получение температуры холодильной камеры
  tmor = termo.getTempMor();  //Получение температуры морозильной камеры
}
// *************Функция дисплея*******************************************
void displ_Vvod() {

  u8g.firstPage();
  delay(1000);
  do {
    draw();
  } while (u8g.nextPage());
}
// *************Функция дисплея******************************************
void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

// *************Функция дисплея******************************************
void text_Prob() {

  u8g_prepare();
  u8g.setPrintPos(0, 0);
  u8g.print(F(" Xol: "));
  //u8g.setPrintPos(7, 0);
  u8g.print(thol);
  u8g.setPrintPos(48, 0);
  u8g.print(F(" Mor: "));
  //u8g.setPrintPos(40,0);
  u8g.print(tmor);
  u8g.setPrintPos(100, 0);
  //u8g.print(F(" n"));
  // u8g.setPrintPos(74, 0);  ---- ???????
     u8g.print(tisp);
  u8g.setPrintPos(4, 12);
  u8g.print F("Work:");
  u8g.print(wrk);  // работа устройства (камеры)F("Work:")
                   u8g.setPrintPos(56, 18);
                   //   u8g.print(wrk); // переменная устройства
                   //   u8g.setPrintPos(64, 12);
                    u8g.print (F("Compr:")); //"Klap: "com
                   //   // u8g.print (": "); //(knopOsv);
                    u8g.print (s); //(knopOsv);
                    u8g.setPrintPos(0, 24);
                    u8g.print(F("workMor:"));
                    u8g.print(workMor);
                   //   u8g.setPrintPos(68, 24);
                   //   u8g.print (F("imp: "));
                   // // myString s;
                   //   u8g.print(imp);
  u8g.setPrintPos(0, 36);
  u8g.print(F("time: "));
  //   u8g.print(s4);//"time: "
  u8g.print(s1);
  //   //u8g.print(isWorkKlap); //s4 "/ "
  //   u8g.print(emagn);
     u8g.setPrintPos(68, 36);
     u8g.print(com);//   u8g.print(stm);
  //   u8g.print(summHol);
  //   u8g.print(F(":"));
  //   u8g.print(summMor);
     u8g.setPrintPos(0, 48);
     u8g.print(F("SummMor:"));
     u8g.print(isSummIsp);
  //   u8g.setPrintPos(68, 48);
  //   u8g.print(F("New:"));
  //     u8g.print(vs);
}
// *************Функция дисплея******************************************
uint8_t draw_state = 0;
void draw(void) {
  //u8g_prepare();
  text_Prob();
}
// *********************setup()******************************************
void setup() {
  Serial.begin(9600);
  //Инициализация выхода компрессора
  pinMode(compr, OUTPUT);
  digitalWrite(compr, LOW);
  //Инициализация выхода вентилятора
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);
  //Инициализация реле клапана
  pinMode(releKN, OUTPUT);
  digitalWrite(releKN, LOW);

  pinMode(knopOsv, INPUT);  // бывшая кнопка надо заменить
  digitalWrite(knopOsv, LOW);
  pinMode(zslnk, OUTPUT);  // Заслонка
  digitalWrite(zslnk, HIGH);
  //Инициализация индикатора цикла вентилятора
  pinMode(LedT, OUTPUT);
  digitalWrite(LedT, LOW);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  // digitalWrite (LedT, HIGH);

  lastDefrostTime = millis();
  digitalWrite(LedT, LOW);
  // Вывод на экран
  u8g.firstPage();  //Запускает процесс вывода на экран.
  do {
    u8g.setFont(u8g_font_9x15);
    u8g.setPrintPos(12, 10);
    u8g.print(F("AristMin "));
    u8g.setPrintPos(8, 35);
    u8g.print(F(" _0Proba "));  //Написать download?
    u8g.setPrintPos(15, 45);
    u8g.print(F("09.09.2025 "));
  } while (u8g.nextPage());  //Заканчивает вывод на экран

  delay(30000);  //900000; 15 минут
  prKn == 1;
  comprEndCycle();  //Функция задержки
  //getTempAdd();     //Получение температуры
  //proverkaKn();// Функция проверки положения клапана
  //if (prKn == 1) {
    proverkaKn();  // Функция проверки положения клапана
    prKn == 0;
    
    isComprOn == 0;
  //}
  attachInterrupt(0, isr, RISING);
  attachInterrupt(1, awr, RISING);
}

// ***********Прерывания***************
volatile uint32_t debounce;
void isr() {
  // оставим 100 мс таймаут на гашение дребезга
  // CHANGE не предоставляет состояние пина,
  // придётся узнать его при помощи digitalRead
  if (millis() - debounce >= 7 && digitalRead(2)) {
    debounce = millis();
  }
  // ваш код по прерыванию по высокому сигналу
}
volatile uint32_t debounce1;
void awr() {
  // оставим 100 мс таймаут на гашение дребезга
  // CHANGE не предоставляет состояние пина,
  // придётся узнать его при помощи digitalRead
  if (millis() - debounce1 >= 100 && digitalRead(3)) {
    debounce = millis();
  }
  // ваш код по прерыванию по высокому сигналу
}


//##################### Основной цикл  #####################
void loop() {
  /*Проверяет температуру, переменную отключения компрессора, состояние клапана.*/
  // uint8_t tmpr = 0;
  // bool error;
    unsigned long currentMillis = millis();
  if (isComprOn == 1 && flag == false) {
    digitalWrite(compr, HIGH);
  } else if (isComprOn == 0 || flag == true) {
    digitalWrite(compr, LOW);
    comprEndCycle();
  }

  if (millis() - myTimer1 >= 30000) {
    myTimer1 = millis();  // сбросить таймер
    getTempAdd();
    isComprOn = cycl.goCompr(thol, tmor);
    kn = sklad.getKn();
    delay(5);
  }

  if (digitalRead(compr) == HIGH) {// Ещё одна ошибка
    s = (F("ON"));                          //Повторения не будет?----------
    if (millis() - myTimer4 >= 2400000) {
      myTimer4 = millis();  // сбросить таймер
      flag = true;// Флаг подняли
      stch = 0;
      isComprOn == 0;
      //comprEndCycle();  
      delay(5);
    }
    

  if (!isLoadOn && currentMillis - previousMillis >= intervalOff) {
      // Включаем нагрузку после интервала выключения
        isLoadOn = true;
        previousMillis = currentMillis;
        digitalWrite(fanPin, HIGH);
      } else if (isLoadOn && currentMillis - previousMillis >= intervalOn) {
        // Выключаем нагрузку после интервала включения
        isLoadOn = false;
        previousMillis = currentMillis;
        digitalWrite(fanPin, LOW);
      }

  }

  if (isCheckingPass) {
    getTempAdd();                  // Проверяем тем-ру
    termo.setTempOld(thol, tmor);  // Записываем в память
      // считанную температуру передаём в класс getOldTemp();
    isCheckingPass = !isCheckingPass;
  }
  if (millis() - myTimer2 >= 30000) {
    myTimer2 = millis();  // сбросить таймер
    uint8_t temOld = termo.getOldTemp();
    switch (temOld) {
        //##############################################################
        /*/ Нужно исправить в классе Temperature -> uint8_t getOldTemp(); 
 температурныый расчёт (Подправлено, требует проверки.) */
      case 0: isCheckingPass = termo.getCheckPasss(); break;
      //case 1:isCheckingPass = termo.getCheckPasss(); workHol = false; break;
      //case 2:isCheckingPass = termo.getCheckPasss(); workHol = true; break;
      case 3:
        isCheckingPass = termo.getCheckPasss();
        workMor = false;
        break;
      case 4:
        isCheckingPass = termo.getCheckPasss();
        workMor = true;
        break;

      default:
        isCheckingPass = termo.getCheckPasss();  //посмотреть...getCheckPasss Это функция. Если вы хотите её вызвать, после неё нужно поставить круглые скобки
        break;
    }  //isCheckingPass = termo.getCheckPasss;
    delay(5);
  }
  //проверяем: если кн == фолсе тогда переменная уст. в фалсе иначе если кн == труе переменная уст. труе.
  // if (klapWork && flag) { klapan; }
  //     Serial.println(thol);
  //     Serial.println(tmor);

  //-------- Вывод на дисплей -------------     
 if (millis() - myTimer3 >= 60000) {
    myTimer3 = millis();  // сбросить таймер
    getTempAdd();// Получаем температуру
    if(digitalRead(5) == HIGH){
      wrk = (F("GO "));
    }else if(digitalRead(5) == LOW){
      wrk = (F("STOP "));
    }
    stch++;
    s1 = stch;
    displ_Vvod();//выводим на дисплей
    delay(5);
  }

  delay(100);
}
//###################################
void comprEndCycle() {
  // Сюда поставить таймер из гайвера ? Зачем?
  if (digitalRead(compr) == HIGH) {
    digitalWrite(compr, LOW);
    s = (F("OFF"));
  }
  com = (F("Compr"));
  // kl = "PAUSE";
  wrk = (F("PAUSE"));
  // imp = isWorkKlap;
  s4 = (F("EndCy"));
  //s1 = (F("P"));
  //provH = (F("cEndC"));
  int i = 15;

  unsigned long comprTimeStamp = millis();  //Время включения компрессора
  while (millis() - comprTimeStamp < comprEndTimes) {
    getTempAdd();
    i--;
    s1 = i;
    displ_Vvod();
    delay(60000);  // Сюда поставить таймер из гайвера
  }
  wrk = (F("START "));
  goStop = true;
  isComprOn = 1;
  flag = false;
}
// =================================================
void proverkaKn() {
  /*Проверяем */ 
  //cycl.goCompr(isCheckingCompr);
  if (digitalRead(compr) == LOW) {
    digitalWrite(compr, HIGH);
    s = (F("ON"));
  }
  wrk = (F("PROVERKA "));
  uint8_t stchet = 0;
  getTempAdd();
  int8_t thl = thol;
  int8_t tmr = tmor;
  kn = sklad.getKn();
  bool klpn = true;
  int i = 0;
  while (klpn == true && i <= 80) {
    stchet++;
    getTempAdd();
    if ((thol + 2) <= thl) {
      kn = true;
      klpn = false;
      com = (F("thol"));
    } else if ((tmor + 2) <= tmr) {
      kn = false;
      klpn = false;
      com = (F("tmor"));
    }else (F("net "));
    i++;
    s1 = i;
    isSummIsp = (tmor + 2) - tmr; // было неправильно
    workMor = klpn;
    // if(i == 18) {digitalWrite(7, HIGH);
    // delay(30000);
    // digitalWrite(7,
    // LOW);
    // }
    displ_Vvod();
    delay(30000);
  }
  if (kn == true) {
    kn = klapan(kn);
    delay(3000);
    prKn = 1;
  } else prKn = 0;
  // if(prKn == 1 && i <= 15){prKn = 1// нужна проверка клапана}
  //     }
  sklad.setKn(kn);
  comprEndCycle();
}
//-----------------------
bool klapan(bool kn) {
  kn = true;
  return kn;
}
//-----------------------
String deice(bool kn) {
  if (kn) {
    wrk = spisok[0];
  } else if (!kn) {
    wrk = spisok[1];
  }
  return wrk;
}
