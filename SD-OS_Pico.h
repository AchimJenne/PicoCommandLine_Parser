/****************************************************************************/
/*  SD-Card configuration                                                   */
/*                                                                          */
/*                                            Achim Jenne 18.10.2025        */
/****************************************************************************/
#ifndef SDOS_PICO
#define ILINE 80

/**************************************************/
#define WS35SPI1

/*! \brief MYSPI0                                 
    \ingroup SDOS_PICO 
    */
#if defined MYSPI0
#define SDCRD SPI
#define SDSPD 16
#define PIN_MISO PIN_SPI0_MISO
#define PIN_MOSI PIN_SPI0_MOSI
#define PIN_SCK PIN_SPI0_SCK
#define PIN_SS PIN_SPI0_SS
#elif defined MYSPI1
#define SDCRD SPI1
#define SDSPD 16
#define PIN_MISO PIN_SPI1_MISO
#define PIN_MOSI PIN_SPI1_MOSI
#define PIN_SCK PIN_SPI1_SCK
#define PIN_SS PIN_SPI1_SS
#elif defined MAKERSPI1
// If you have all 4 DAT pins wired up to the Pico you can use SDIO mode
// const int RP_CLK_GPIO = 10; // Set to CLK GPIO
// const int RP_CMD_GPIO = 11; // Set to CMD GPIO
// const int RP_DAT0_GPIO = 12; // Set to DAT0 GPIO.
// const int RP_DAT0_GPI1 = 13;
// const int RP_DAT0_GPI2 = 14;
// const int RP_DAT0_GPI3 = 15;
#define SDCRD SPI1
#define SDSPD 40
#define PIN_MISO 12
#define PIN_MOSI 11
#define PIN_SCK 10
#define PIN_SS 15
#elif defined WS35SPI1
// If you have all 4 DAT pins wired up to the Pico you can use SDIO mode
// const int RP_CLK_GPIO = 10; // Set to CLK GPIO
// const int RP_CMD_GPIO = 18; // Set to CMD GPIO
// const int RP_DAT0_GPIO = 19; // Set to DAT0 GPIO.
// const int RP_DAT0_GPI1 = 20;
// const int RP_DAT0_GPI2 = 21;
// const int RP_DAT0_GPI3 = 22;
#define SDCRD SPI1
#define SDSPD 40
#define PIN_MISO 12
#define PIN_MOSI 11
#define PIN_SCK 10
#define PIN_SS 22
#elif defined WS147SPI1
/*! \brief WS147SPI1                                 
    \ingroup SDOS_PICO 
    */
// If you have all 4 DAT pins wired up to the Pico you can use SDIO mode
// const int RP_CLK_GPIO = 10; // Set to CLK GPIO
// const int RP_CMD_GPIO = 11; // Set to CMD GPIO
// const int RP_DAT0_GPIO = 12; // Set to DAT0 GPIO.    
#define SDCRD SPI1
#define SDSPD 40
#define PIN_MISO 12
#define PIN_MOSI 11
#define PIN_SCK 10
#define PIN_SS 15
#endif

/**************************************************/
#define C_BS  0x08
#define C_ESC 0x1b
#define S_CLS F("\e[0H\e[2J")
#define S_CR  F("\r\n>")
uint64_t dateTime2Unix(int , int , int , int , int , int );
  int day, mon, year;
  int hour, minute, second;
#define SDOS_PICO
#endif