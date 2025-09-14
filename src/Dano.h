#pragma once
#include <stdint.h>

#define compr  5    // реле компрессора
#define fanPin  6    // пин вентилятора
#define releKN  7    // Электромагнит
#define knopOsv 10  //кнопка
#define zslnk  11    //Контакт заслонки
#define LedT  13    // 

#include <Arduino.h>
#include <string.h> 
using namespace std;

//GyverNTC therm1(0, 10000, 3950);  // морозилка
//GyverNTC therm2(1, 10000, 3950);  //  холодилка
//GyverNTC therm3(2, 1000, 4950);  //  испарилка (испарение)

const int8_t minTempMor = 2;                 // Минимальна+я температура морозилки 
const int8_t nomTempMor = 10;                // Рабочая температура морозилки
const int8_t maxTempMor = 15;                 // Высокая температура
const int8_t minTempHol = 15;                   // Минимальная температура холодильника
const int8_t nomTempHol = 18;                   // Номинальная температура холодильника
const int8_t maxTempHol = 20;                   // Максимальная температура холодильника
const int8_t minTempIsp = 44;                   // Минимальная температура испарителя 
const int8_t nomTempIsp = 50;                   // Номинальная температура испарителя
const int8_t maxTempIsp = 60;                   // Максимальная температура испарителя
const int8_t targetTemp = 18;                   // Средняя температура холодильной камеры
const int8_t targetDefrostTemp = 10;           //Установленная температура разморозки 
const unsigned long compReadTime = 60000;  //60000   //Интервал считывания температуры 600001 минута компрессора 
const unsigned long heatReadTime = 20000;     //Интервал считывания температуры 10 секунд вентилятора
const unsigned long compWorkTime = 1800000;   //Максимальное время непрерывной 5 минут работы компрессора 
//const unsigned long fenWorkTime = 300000;    //Максимальное время непрерывной 30 минут работы вентилятора 
const unsigned long compRestTime = 1600000;    //Время паузы на охлаждение компрессора (сделать 15 минут)
const unsigned long defrostTime = 43200000;   //Интервал запуска цикла разморозки (??????????????????)
const unsigned long comprEndTimes = 900000;
const unsigned long comprCycleTime = 1200000;
unsigned long periodTime = 0;
//Переменные
unsigned long lastDefrostTime;
unsigned long timing, timing1;
// **************************
uint32_t myTimer1, myTimer2, myTimer3, myTimer4;
// **************************
String spisok [5] {"Xol", "Mor", "Fen", "YES"};
// String spisok1 [3] {"Work;", "Kompr;", "Sthet;"};
//bool isEmagnUp = true; // Проверка переключения электромагнита
bool isCheckingPass = true;  //Проверка /Старые/00000 ?????
bool isCheckFen = false;// Включение фена
bool kn ;//= false; Переключатель клапана
bool isFan = false;
uint8_t isComprOn = 0; //переменная отключения компрессора.
bool isEmagnUp = false;
bool isProvKlap = false; 
bool goStop = false;
bool flag = 0;
volatile bool isWorkKlap = false;
//bool knopOsv = LOW;
bool workHol = false;
bool workMor = false;
//int t1 = 0;
int summMor; // разница температур морозильника
int summHol; // разница температур холодильника
int stch = 0;
int tNaw = 0;
uint8_t prKn = 0;
const int delStatic = 30000;
uint8_t sbros = 0; 
const uint8_t vs; // Счётчик
const uint8_t my_sthet; // переменная счёта циклов функции
const uint8_t klapWork = 15; // Время паузы переключения клапана

int8_t tmor; // Температура морозилки
int8_t thol; // температура холодильной камеры
int8_t tisp; // температура испарителя
int8_t isSummIsp; // Разница сумм испарителя
//unsigned long timing; // Переменная для хранения точки отсчета
static uint8_t tog = 0;
static uint32_t oldtime = millis();
// char myString s;

String s; // Состояние клапана
String s1; // счёттчик
String wrk; //переменная устройства
String imp; //показ импульса с Pin2
String s4; //Рабочая функция
String kl; // состояние клапана
String com;
String emagn; // Электромагнит (клапан)
String provH; // Проверка?
String devis; 
String Ustr;  // устройство
String zslk;   // положение заслонки 
//void isr();
void comprEndCycle();
void proverkaKn();
bool klapan(bool kn);
void draw(void);
void isr();
void awr(); 
/*volatile uint32_t debounce;
 void isr() {
  // оставим 100 мс таймаут на гашение дребезга
  // CHANGE не предоставляет состояние пина, 
  // придётся узнать его при помощи digitalRead
   if (millis() - debounce >= 7 && digitalRead(2)) {
    debounce = millis();}   
    // ваш код по прерыванию по высокому сигналу   
 }*/