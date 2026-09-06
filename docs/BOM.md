# PMW3389 Custom DIY Mouse - Bill of Materials

## Build information

|Item|Specification|
|---|---|
|**Project**|PMW3389 Custom DIY Mouse|
|**Quantity**|1 Mouse|
|**PCB**|Custom Designed|
|**Revisions Supported**|v2|

## 1. PCB

|Item|Required?|v2 (Wired)|v3 (Wireless)|
|---|---|---|---|
|**PCB Gerbers**|Yes|[Gerbers v2]()|[Gerbers v3]()|

This PCB can be assembled by PCB manufacturer or assembled by hand.

## 2. Surface Mount Components (Placed in PCBA)

|PCB Reference|Qty|Component|Part Number/Value|Package|Notes|
|---|---|---|---|---|---|
|U2|1|LDO Regulator|XC6206-1.8V|SOT-23|XC6206-series 1.8 V LDO; equivalent parts must match the schematic's electrical and pinout requirements.|
|R1|1|Resistor|13 Ω|0805|-|
|R2|1|Resistor|10 kΩ|0805|-|
|C1|1|Capacitor|4.7uF|0805|-|
|C2, C3, C6, C8, C10|5|Capacitor|0.1uF/100nF|0805|-|
|C5, C7, C9|3|Capacitor|10uF|0805|-|
**THERE IS NO C4**

## 3. Through Hole Components (Not in PCBA)

These components are intentionally excluded from PCBA and must be installed by hand.

|Item|Quantity|Notes|
|---|---|---|
|Arduino Pro Micro ATmega32U4 3.3V/8MHz|1|**MUST BE 3.3V/8MHz** Microcontroller for mouse|
|PMW3389|1|Mouse sensor|
|EC11|1|**Should be 15mm and "Plum Handle".**Rotary encoder (Scroll Wheel)|
|Mill-Max 3305 socket|6|Allows for Hot-Swappable switches|
|Huano Blue Shell Pink Dot|2|Mouse switches (Buttons)|
|12-Pin Male Pin Header, 2.54mm Pitch, 1×12|2|Should come with Pro Micro|
|12-Pin Female Pin Header, 2.54mm Pitch, 1×12|2|Allows for replaceable Microcontroller|

## 4. Other Stuff

|Item|Quantity|Notes| 
|---|---|---|
|LM-19-LCT Lens|1|Lens for PMW3389, usually sold together|
|PTFE Mouse Skates|5-10|Placed on bottom of mouse to allow for smooth movement|
|USB Cable|1|Get 1m+|

## 5. 3D Printed Parts
|Item|Source|Notes|
|---|---|---|
|Top Shell|[Top Shell 3mf](Mechanical/v2/STLs/Mouse Shell top.3mf)|Keep at rotation, it helps with stepping|
|Bottom shell|[Bottom Shell 3mf](Mechanical/v2/STLs/Mouse Shell bottom.3mf)|-|
|Scroll Knob|[Scroll Knob 3mf](Mechanical/v2/STLs/Mouse Shell knob.3mf)|-|

## 6. Mounting Hardware

|Item|Quantity|Notes|
|---|---|---|
|M2 x 3 x 3.2 Heat Inserts|7|-|
|M2 x 6 Screws|4|-|
|M2 x 4 Screws|3|-|

## 7. Overall Manufacturing

### PCB

- Quantity: 1
- Download [GBR Files](https://github.com/aSharcc/PMW3389-Arduino-Custom-Mouse/releases/download/2.0/DIY_Mouse.zip)
- Download PCBA Files [BOM](https://github.com/aSharcc/PMW3389-Arduino-Custom-Mouse/releases/download/2.0/bom.csv) and [CPL](https://github.com/aSharcc/PMW3389-Arduino-Custom-Mouse/releases/download/2.0/positions.csv)
- Order from PCB manufacturer e.g. [JLCPCB](https://cart.jlcpcb.com/quote)
- PCBA is optional for small surface mount components but can be hand-soldered
- All components not included in PCBA must be installed by hand as required by the design.

### Purchasing Parts

Do not purchase the components listed in **Section 2: Surface Mount Components**.

These components will be supplied and assembled by the PCB manufacturer.

The components in **Section 3: Through Hole Components** must still be purchased separately and installed by hand.

### Shell

- 3D print the following files:
    - [Top Shell](Mechanical/v2/STLs/Mouse Shell top.3mf)
    - [Bottom Shell](Mechanical/v2/STLs/Mouse Shell bottom.3mf)
    - [Scroll Knob](Mechanical/v2/STLs/Mouse Shell knob.3mf)
- Insert heat inserts into the holes on the top and bottom shell

### Firmware

You can use either Arduino IDE or VS Code with PlatformIO extension

#### Arduino IDE

##### Library

You can install the PMW3389 library using either method:

**Option 1 — Included library**

1. Download [Firmware.zip](https://github.com/aSharcc/PMW3389-Arduino-Custom-Mouse/releases/download/2.0/Firmware.zip).
2. Open Arduino IDE.
3. Go to **Sketch → Include Library → Add .ZIP Library...**
4. Select `Firmware.zip`.

**Option 2 — Arduino Library Manager**

1. Open Arduino IDE.
2. Open **Library Manager**.
3. Search for `PMW3389`.
4. Install the library by **sharc !!**.

##### Selecting Correct Board

**If you upload the code with the wrong board you can brick your arduino!!**

1. Open Arduino IDE
2. Click **File->Preferences or Arduino->Preferences**
3. Find **Additional Boards Manager URLs** field
4. Paste this link:
``` markdown
https://raw.githubusercontent.com/sparkfun/Arduino_Boards/main/IDE_Board_Manager/package_sparkfun_index.json
```
5. Click **OK**
6. Click **Tools->Board->Board Manager**
7. Search for `SparkFun AVR Boards`
8. Click **Tools->Board->Sparkfun AVR Boards**
9. Select your board
10. Click **Tools->Processor**
11. Select **3.3V/8MHz**

##### Mouse Code

1. Download [Basic Mouse](Firmware/examples/BasicMouse/BasicMouse.ino)
2. Plug in Arduino Pro Micro
3. Open with Arduino IDE
4. Select COM port with Arduino Pro Micro
5. Click **Upload** in top left

#### VSCode w/ PlatformIO

1. Download [Firmware Directory](Firmware)
2. Open **Firmware/examples/BasicMouse/BasicMouse.ino**
3. Click **Upload** in bottom left