# Raspberry PICO: PicoCommandLine_Parser
A simple ASCII commandline- interface (CLI) with prinary File- functions and comfort. Supports VT100-Terminal emulation (like TeraTerm, PUTTY, GTKTerm and other) on the USB-Port.
![Pico_SD-OS](https://github.com/user-attachments/assets/2fbff618-61a3-431b-95c4-c61678a272d7)

Typical Terminal screen (TerTerm) after PICO startup.

If do you like to build your own **Arduino** project on **Raspberry Picos (I-II)** with **SD-Cards** and if do you need filehandling, may be you can find this function helpful.
- SD-Cards on SPI 0 and 1, tested on 3.5 Inch graphic boards, tested with Cytron Maker Board.
  
- supports the **PICO-Realtime clock**
  
- **DS3231** external RTC support
  
- supports multible boards **PICO-I-II**; PICO 2350 with 1.47 Inch Display and SD-Card
  
**CD**, **MD**, **RD** - directory handling

**CONFIG** - shows the SPI- configuration

**DEL** - removing file

**DIR** - shows the directory

**DATE** and **TIME** - get and set time/date value

**TYPE** - list an ASCII-File on your terminal

**CLS** - clean the VT100 screen and set the cursor position top-left

**TEMP** - get the RTC- chip (DS3231 if available)
 and CPU- temperature

**VER** - shows some software informations

**VOL** - list the SD-Card information

This function is a simple platform for your own software project

The main- function is a rapid running loop (like other ARDUINO software designs). It means, this function is polling the terminal interface. There is no “event-driven” interface in ARDUINO available. This means, your enhancement must have fast functions! Otherwise the Input-buffer should be increased and/or the second core should do some work.

**Needed:**
A Raspberry Pico I or II and a SD-Card on SPI0 or SPI1. A DS3231 RTC could be helpful – but not needed for testing this software.
 
-	ARDUINO development package
-	The Raspberry Pico development enhancement from Earle F. Phillhower (the ARDUINO 2040 package does not support any used functions)
-	The SD-Card functions are an important part of this packages

**Hint:**
Accessing the SD-Card with SDIO is much faster than SPI! But some board are not supporting this interface. In critical applications it could be a good idea to use the SDIO-Interface. But you have to check/change any “SD.begin” statement. 
Please find some SD-Card configurations in “SD-OS_Pico.h”. Here you can define your own setup.

The token parser (SD-OS_Parser.ino) was an automatic generated code block. It is a binary search algorithm, makes it faster than sequential searching. Hand coded enhancements could be difficult! It is better to place your enhancement into a separate function.

**Restrictions:**
The error handling is not complete 
longer pathnames could be a problem

Released into the public domain without warranty.
No warranty on the software sourcecode/function, hardware and/or system applications.

It is my private project without any comercial aspects. I used the **ARDUINO** develment platform and the **Raspberry Pico enhancements from Earle F. Phillhower III**.
I used it with respect of they work!
