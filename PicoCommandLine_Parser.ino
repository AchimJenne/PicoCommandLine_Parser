/**************************************************/
/*! \brief Automatic generated enum- commands
    \defgroup token_parser
    \sa datetime_t */
/**************************************************/
enum eCmdSt {eNoToken=0,
      eAUTO, eCD, eCLS, eCONFIG, eCOPY, eDATE, eDEL, eDIR,
      eECHO, eFORMAT, eHELP, eMD, ePATH, eRD, eREN, eTEMP,
      eTIME, eTYPE, eVER, eVOL};

/**************************************************/
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <arduino.h>
#include <string.h>
#include "SD-OS_Pico.h"
#include "pico/stdlib.h"
#include "I2C_RTC.h"

#include <SPI.h>
#include <SD.h>
#include <FatFS.h>
/**************************************************/
static DS3231 RTC;
File myFile;

//time_t tiCPU = time(nullptr);
char sLogFn[40]= "start.txt";
char sPath[ILINE]= {"/"};
volatile bool bAuto = false;
bool bRTC = false;
// struct tm ti;
time_t tiUx= 1611198855;  // Jan 21, 2021  3:14:15AM ...RPi Pico Release;
struct timeval tiV;

/**************************************************/

/**************************************************/
void setup() {
  // put your setup code here, to run once:
  char sLine[ILINE];
  Serial.begin(115200);
  // wait on Serial to be available on Leonardo
  while (!Serial){
    delay(10);
  } 
  delay(10);
  pinMode(PIN_LED, OUTPUT);
  analogReadResolution(12);
  analogReadTemp(3.3f);

  Serial.print(S_CLS);
  Serial.println(BOARD_NAME);
  Serial.print(F("CPU- Frequency:   "));
  Serial.print(F_CPU/1000000);
  Serial.println(F(" MHz"));
  Serial.print(F("Pico SDK Version: "));
  Serial.println(PICO_SDK_VERSION_STRING);
  Serial.print(F("Arduino Version:  "));
  Serial.println(ARDUINO_PICO_VERSION_STR);

#if defined MAKERSPI1
  check available SD_Card
  gpio_init(PIN_SS);
  gpio_set_dir(PIN_SS, false);
  gpio_disable_pulls(PIN_SS);
  gpio_put(PIN_SS, 0);
  uint8_t bSD1= 0;
  while ((bSD1= gpio_get(PIN_SS)) == 0)
  {
    delay(100);
    Serial.print(F("No Card ("));
    Serial.print(PIN_SS);
    Serial.print(F(":"));
    Serial.print(bSD1, DEC);
    Serial.print(F(")\e[14D"));
  }
  gpio_deinit(PIN_SS);
  delay(10);
#endif

  // if available, then init SPI-Interface
  SDCRD.setMISO(PIN_MISO);
  SDCRD.setMOSI(PIN_MOSI);
  SDCRD.setSCK(PIN_SCK);
  SDCRD.beginTransaction(SPISettings(SD_SCK_MHZ(SDSPD), MSBFIRST, SPI_MODE0));
  Serial.print(F("Init SD-Card  ... "));
  if (!SD.begin( PIN_SS, SDCRD)) 
  {
     Serial.println(F("failed"));
  } else {
    Serial.println(F("OK"));
  }
  SD.end(); 

  Serial.print(F("CPU- Temperature:  "));
  Serial.println(analogReadTemp(3.3f));

  //*** external RTC Modul ***
  if (RTC.begin()){
    bRTC = true;
    if (!RTC.isRunning()) {
      Serial.println(F("RTC starting"));
      RTC.startClock();
    } 
    if (RTC.getHourMode() != CLOCK_H24) {
      Serial.println(F("RTC set to 24h Format"));
      RTC.setHourMode(CLOCK_H24);
    }
    /* set internal RTC to external RTC values */
    tiV.tv_sec = dateTime2Unix(RTC.getYear(),RTC.getMonth(),RTC.getDay(),RTC.getHours(),RTC.getMinutes(),RTC.getSeconds()) ; 
    tiV.tv_usec = 0;
    settimeofday(&tiV, nullptr);
  
    Serial.print(F("RTC- Temperature:  "));
    Serial.println(RTC.getTemp());
    Serial.print(F("RTC- Date&Time:    "));
    Serial.printf("%2.2d.%2.2d.%4.4d %2.2d:%2.2d:%2.2d\r\n",
                   RTC.getDay(),   RTC.getMonth(),   RTC.getYear(), 
                   RTC.getHours(), RTC.getMinutes(), RTC.getSeconds());  
  }

  time(&tiUx); 
  Serial.print(F("Pico internal RTC: "));
  strftime(sLine, sizeof(sLine), "%0d.%0m.20%0y %0H:%0M:%0S", localtime(&tiUx));
  Serial.print(sLine);
  strftime(sLine, sizeof(sLine), " %0d %B 20%0y (%A) %0H:%0M:%0S", localtime(&tiUx));
  Serial.println(sLine);

  Serial.print(F(">"));
  /***/
}
/**************************************************/
/**
  @brief Interactive VT100- command input 
  @param [in, out] psLine Buffer to read and edit
  @param [in] inChar serial input byte to interpret
*/
bool editLine(char *psLine, char inChar)
{
  static char sBack[ILINE];
  static char sTemp[ILINE];
  static unsigned char iIndx=0;
  static uint8_t iESC= 0;
  static bool bEditMode= false;
      if (inChar == '\r')       // CR key
      {
        for (unsigned int i=1; i<=(strlen(psLine)-iIndx); i++) {
          Serial.print(F("\e[C"));
        }
        iIndx= 0;
        iESC= 0;
        strcpy(&sBack[0], psLine);
        bEditMode= true;
      } else {
        bEditMode= false;
        if (inChar == '\n')   // new line
        {
          Serial.write(inChar);
        } else 
        if ((inChar == '[') && (iESC ==1)) {
          iESC = 2;
        } else 
        if (((inChar == 'A')||(inChar == 'B')) && (iESC ==2)) // cursor up-down
        {
          for (char i=0; i<iIndx; i++) {
            Serial.print(F("\b \b"));
          }
          strcpy(&sTemp[0], psLine);
          strcpy(psLine, &sBack[0]);
          strcpy(&sBack[0], &sTemp[0]);
          Serial.print(F("\e[0G>"));
          Serial.print(psLine);
          iIndx= strlen(psLine);
          iESC= 0;
        } else 
        if ((inChar == 'D') && (iESC ==2)) // key left
        {
          if (iIndx >=1) {
            Serial.print(F("\e[D"));
            iIndx--;
          }
          iESC= 0;
        } else 
        if ((inChar == 'C') && (iESC ==2))  // key right
        {
          if (strlen(psLine) > iIndx) {
            Serial.print(F("\e[C"));
            iIndx++;
          }
          iESC= 0;
        } else 
        if (inChar == C_BS)       // backpace key 
        {
          if (strlen(psLine) >= 1) {
            Serial.print(F("\b"));
            int iLen= strlen(psLine);
            if (iLen> iIndx) {
              for (int iLoop=iIndx; iLoop <= iLen; iLoop++) {
                *(psLine+iLoop-1) = *(psLine+iLoop);
              }
              iIndx--;
              Serial.print(psLine + iIndx);
              Serial.print(F(" \e["));
              Serial.print(iLen - iIndx);
              Serial.print(F("D"));
            } else {
              Serial.print(F(" \b"));
              iIndx--;
              *(psLine+iIndx) = 0x00;
            }            
          }
        } else 
        if (inChar == C_ESC)    // escape key
        {
          if (iESC >= 1) {
            for (char i=0; i<iIndx; i++) {
               Serial.print(F("\b \b"));
            }
            *psLine= 0;
            iIndx= 0;
            bEditMode = false;
            iESC= 0;
          } else {
            iESC= 1;
          }
        } else           
        if (inChar == 0x7f) {
          int iLen= strlen(psLine);
          if (iLen> iIndx) {           
            for (int iLoop=iIndx+1; iLoop <= iLen; iLoop++){
              *(psLine+iLoop-1) = *(psLine+iLoop);
            }
            Serial.print(psLine + iIndx);
            Serial.print(F(" \e["));
            Serial.print(iLen - iIndx);
            Serial.print(F("D"));
          }          
        } else {
          if (iIndx < ILINE) {
            Serial.write(inChar);
            int iLen= strlen(psLine);
            if (iLen> iIndx) {
              for (int iLoop=iLen; iLoop >= iIndx; iLoop--){
                *(psLine+iLoop+1) = *(psLine+iLoop);
              }
              *(psLine+iIndx) = inChar;
              Serial.print(psLine + iIndx + 1);              
              Serial.print(F("\e["));
              Serial.print(iIndx+3);
              Serial.print(F("G"));
              iIndx++;
            } else {
              *(psLine+iIndx) = inChar;
              iIndx++;
              *(psLine+iIndx) = 0x00;
            }
          }
        }
      }
    return (bEditMode);
}
/**************************************************/
void loop() {
char inChar;
  static char sLine[ILINE]; 
  char *psLine= &sLine[0];

  // put your main code here, to run repeatedly:
  if (Serial.available())
  { 
    inChar = (char)Serial.read();
    if (editLine(psLine, inChar))
    {
      /************************************************************/
      // if command
      psLine = strupr(psLine);
      int iRet= fnSDOS_Parser(psLine);
      *psLine= 0;
      Serial.print(S_CR);
    } /* end if */
  }  
}
