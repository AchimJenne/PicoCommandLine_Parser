# Raspberry PICO: PicoCommandLine_Parser
Arduino CommandLine_Parser for Rasp-Pi.

A simple ASCII commandline- interface (CLI) with prinary File- functions and comfort. Supports VT100-Terminal emulation (like TeraTerm, PUTTY, GTKTerm and other) on the USB-Port.
![Pico_SD-OS](https://github.com/user-attachments/assets/2fbff618-61a3-431b-95c4-c61678a272d7)

Typical Terminal screen (TeraTerm) after PICO startup.

If do you like to build your own **Arduino** project on **Raspberry Picos (I-II)** with **SD-Cards** and if do you need filehandling, may be you can find this function helpful.
- SD-Cards on SPI 0 and 1, tested on 3.5 Inch graphic boards, tested with Cytron Maker Board.
  
- supports the **PICO-Realtime clock**
  
- **DS3231** external RTC support
  
- supports multible boards **PICO-I-II**; PICO 2350 with 1.47 Inch Display and SD-Card<BR/>

## Available commands
- **CD**, **MD**, **RD** - directory handling<BR/>
- **CONFIG** - shows the SPI- configuration<BR/>
- **DEL** - removing file<BR/>
- **DIR** - shows the directory<BR/>
- **DATE** and **TIME** - get and set time/date value<BR/>
- **TYPE** - list an ASCII-File on your terminal<BR/>
- **CLS** - clear the VT100 screen and set the cursor position top-left<BR/>
- **TEMP** - get the RTC- chip (DS3231 if available) and CPU-internal (Die) temperature<BR/>
- **VER** - shows some software informations<BR/>
- **VOL** - list the SD-Card information<BR/>

This function is a simple platform for your own software project<BR/>
The main- function is a rapid running loop (like other ARDUINO software designs). It means, this function is polling the terminal interface. There is no “event-driven” interface in ARDUINO available. This means, your enhancement must have fast functions! Otherwise the Input-buffer should be increased and/or the second core should do some work.<BR/>

## Needed:
A Raspberry Pico I or II and a SD-Card on SPI0 or SPI1. A DS3231 RTC could be helpful – but not needed for testing this software.<BR/>
 
-	ARDUINO development package. I used IDE 2.3.4
-	The Raspberry Pico development enhancement from Earle F. Phillhower III (the ARDUINO MBed RP2040 package doesn't support some functions)
-	The SD-Card functions are part of this packages

## Hint:
Accessing the SD-Card with SDIO is much faster than SPI! But some board are not supporting this interface. In critical applications it could be a good idea to use the SDIO-Interface. But you have to check/change “SD.begin” parameter. 
Please find some SD-Card configurations in “SD-OS_Pico.h”. Here you can define your own setup.<BR/>

The token parser (SD-OS_Parser.ino) is automatic generated code. It is a binary search tree algorithm, faster than sequential searching. Hand coded enhancements could be difficult! It is better to place your enhancement into a separate function.<BR/>

## Restrictions:
- The error handling is not complete 
- longer pathnames could be a problem
![IMG_0584_cut_comp](https://github.com/user-attachments/assets/25883f65-68be-4058-8885-b6e8334d9b79)

Released into the public domain without warranty.<BR/>
No warranty on the software sourcecode/function, hardware and/or system applications.<BR/>

It is my private project without any comercial aspects. I used the **ARDUINO** develment platform and the **Raspberry Pico enhancements from Earle F. Phillhower III**.<BR/>
I used it with respect of they work!<BR/>
