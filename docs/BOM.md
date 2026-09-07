# PMW3389 Custom DIY Mouse - Bill of Materials

**Shop links to components in [BOM.csv](../BOM.csv)**

## Build information

|Item|Specification|
|---|---|
|**Project**|PMW3389 Custom DIY Mouse|
|**Quantity**|1 Mouse|
|**PCB**|Custom Designed|
|**Revisions Supported**|v2, v3|

## 1. PCB

|Item|Required?|v2 (Wired)|v3 (Wireless)|
|---|---|---|---|
|**PCB Gerbers**|Yes|[Gerbers v2](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/2.0/DIY_Mouse.zip)|[Gerbers v3](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/3.0/Mouse_v3.zip)|
|**PCBA BOM**|Only for PCBA|[BOM v2](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/2.0/bom.csv)|[BOM v3](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/3.0/bom.csv)|
|**PCBA POSITONS**|Only for PCBA|[Positions v2](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/2.0/positions.csv)|[Positions v3](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/3.0/positions.csv)|

This PCB can be assembled by PCB manufacturer with PCBA or assembled by hand.

## 2. Surface Mount Components (Placed in PCBA)

### v2
|PCB Reference|Qty|Component|Part Number/Value|Package|Notes|
|---|---|---|---|---|---|
|U2|1|LDO Regulator|XC6206-1.8V|SOT-23|XC6206-series 1.8 V LDO; equivalent parts must match the schematic's electrical and pinout requirements.|
|R1|1|Resistor|13 Ω|0805|-|
|R2|1|Resistor|10 kΩ|0805|-|
|C1|1|Capacitor|4.7uF|0805|-|
|C2, C3, C6, C8, C10|5|Capacitor|0.1uF/100nF|0805|-|
|C5, C7, C9|3|Capacitor|10uF|0805|-|
**THERE IS NO C4**

### v3
|PCB Reference|Qty|Component|Part Number/Value|Package|Notes|
|---|---|---|---|---|---|
|C1-C5|5|Capacitor|0.1uF/100nF|0805|-|
|C6-C8|3|Capacitor|10uF|0805|-|
|C9|1|Capacitor|4.7uF|0805|-|
|R1|1|Resistor|13 Ω|0805|-|
|R2, R3|2|Resistor|10 kΩ|0805|-|
|U3|1|LDO Regulator|SOT-23|XC6206-series 1.8 V LDO; equivalent parts must match the schematic's electrical and pinout requirements.|

## 3. Through Hole Components (Not in PCBA)

These components are intentionally excluded from PCBA and must be installed by hand.

### v2

|Item|Quantity|Notes|
|---|---|---|
|Arduino Pro Micro ATmega32U4 3.3V/8MHz|1|**MUST BE 3.3V/8MHz** Microcontroller for mouse|
|PMW3389|1|Mouse sensor|
|EC11|1|**Should be 15mm and "Plum Handle".**Rotary encoder (Scroll Wheel)|
|Mill-Max 3305 socket|6|Allows for Hot-Swappable switches|
|Huano Blue Shell Pink Dot|2|Mouse switches (Buttons)|
|12-Pin Male Pin Header, 2.54mm Pitch, 1×12|2|Should come with Microcontroller, check when purchasing|
|12-Pin Female Pin Header, 2.54mm Pitch, 1×12|2|Allows for replaceable Microcontroller|

### v3

|Item|Quantity|Notes|
|---|---|---|
|Seeed Studio XIAO ESP32-C3|1|Wireless Microcontroller for mouse|
|PMW3389|1|Mouse sensor|
|EC11|1|**Should be 15mm and "Plum Handle".** Rotary encoder (Scroll Wheel)|
|Mill-Max 3305 socket|6|Allows for Hot-Swappable switches|
|Huano Blue Shell Pink Dot|2|Mouse switches (Buttons)|
|12-Pin Male Pin Header, 2.54mm Pitch, 1×7|2|Should come with Microcontroller, check when purchasing|
|12-Pin Female Pin Header, 2.54mm Pitch, 1×7|2|Allows for replaceable Microcontroller|

## 4. Other Stuff

### v2 and v3

|Item|Quantity|Notes| 
|---|---|---|
|LM-19-LCT Lens|1|Lens for PMW3389, usually sold together|
|PTFE Mouse Skate Dots|5-10|Placed on bottom of mouse to allow for smooth movement|
|USB Cable|1|Get 1m+ / **USB micro for v2 / USB C for v3**|


## 5. 3D Printed Parts

|Item|v2 (wired)|v3 (wireless)|Notes|
|---|---|---|---|
|Top Shell|[Top v2](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/2.0/Mouse.Shell.top.gcode.3mf)|In progress|Keep at rotation, it makes the shell smoother|
|Bottom shell|[Bottom v2](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/2.0/Mouse.Shell.bottom.gcode.3mf)|In progress|-|
|Scroll Knob|[Scroll v2](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/2.0/Mouse.Shell.knob.gcode.3mf)|In progress|-|

## 6. Mounting Hardware

### v2 and v3

|Item|Quantity|Notes|
|---|---|---|
|M2 x 3 x 3.2 Heat Inserts|7|-|
|M2 x 6 Screws|4|-|
|M2 x 4 Screws|3|-|

## 7. Overall Manufacturing

### PCB

- Quantity: 1
- Download [Gerber Files](#1-pcb)
- Download PCBA Files [BOM](#1-pcb) and [CPL](#1-pcb)
- Order from PCB manufacturer e.g. [JLCPCB](https://cart.jlcpcb.com/quote)
- PCBA is optional for small surface mount components but can be hand-soldered
- All components not included in PCBA must be installed by hand as required by the design.

### Purchasing Parts

**If using PCBA** do not purchase the components listed in **Section 2: Surface Mount Components** .

These components will be supplied and assembled by the PCB manufacturer.

The components in **Section 3: Through Hole Components** must still be purchased separately and installed by hand.

### Shell

- 3D print the following files:
    - [Top Shell](#5-3d-printed-parts)
    - [Bottom Shell](#5-3d-printed-parts)
    - [Scroll Knob](#5-3d-printed-parts)
- Insert heat inserts into the holes on the top and bottom shell

### v2 Firmware

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

### v3 firmware

**In progress**