https://github.com/user-attachments/assets/145927b7-b68a-468a-8b0a-571980a8af83

# PMW3389 Custom DIY Mouse

A fully custom gaming mouse using a PixArt PMW3389.

2 versions. 3.3V/8MHz Arduino Pro Micro (ATmega32U4) and Seeed Studio XIAO ESP32C3.

I also intend for this mouse to be easily repairable.

Be sure to read [BOM.md](docs/BOM.md)

## Key Features

- High performance sensor: 16,000 DPI via PixArt PMW3389
- Modular and Repairable
	- Hotswap Main Switches: Uses Mill-Max 3305 so can be replaced with no soldering
	- Replaceable MCU: Mounted using through-hole pin headers
- Wireless and wired versions.
- Sensor communication through SPI

## Version Comparison

|Features|v2 (Wired)|v3 (Wireless)|
|---|---|---|
|MCU|3.3V/8MHz Arduino Pro Micro (ATmega32U4)|Seeed Studio XIAO ESP32C3|
|Connectivity|Micro-USB|Bluetooth / 2.4GHz Wireless|
|Power Source|Micro-USB|LiPo Battery|
|Production Files|[Files v2](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/tag/2.0)|[Files v3](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/tag/3.0)|

## How To Use

**DETAILED INSTRUCTIONS and BOM [HERE](docs/BOM.md)**

1. Order the PCB from a PCB manufacturer (e.g. JLCPCB) with files from specific release.
2. Either:
   - Order PCBA for the SMD components, or
   - Purchase the SMD components and hand solder them.
3. Purchase the components listed in the BOM that are not included in PCBA.
4. Hand solder/install the components not included in PCBA.
5. Download the PMW3389 library.
	- For Wired: [Arduino Library](Firmware/Arduino/README.md) for instructions.
	- For Wireless: **NOT COMPLETED**
6. Download Firmware
	- For Wired: [Arduino Firmware](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/2.0/Mouse.Firmware.ino)
	- For Wireless: **NOT COMPLETED**
7. Flash the firmware to the MCU.
8. Download and print the 3D models.
	- For Wired: [Top](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/2.0/Mouse.Shell.top.gcode.3mf) + [Bottom](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/2.0/Mouse.Shell.bottom.gcode.3mf) + [Scroll](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/2.0/Mouse.Shell.knob.gcode.3mf)
	- For Wireless: **NOT COMPLETED**
9. Add threaded heat inserts to the shell.
10. **For Wireless Only**:
	- **Not Completed** Will include power switch and battery stuff.
11. Assemble the mouse.

## Components

- Sensor: PixArt PMW3389 and LM19-LCT Lens

- MCU: 3.3V/8MHz Arduino Pro Micro (ATmega32U4) or Seeed Studio XIAO ESP32C3

- Switches: 2 x Huano Blue Shell Pink Dot Mouse Switches 

- Scroll Wheel: Rotary Encoder w/Switch (EC11)

- Hot Swap Socket for Switches: 6 x Mill-Max 3305

- SMD Components (0805)
	- 1 x 13 ohm resistor
	- 1 x 10k ohm resistor
	- 5 x 0.1uF capacitor
	- 3 x 10uF capacitor
	- 1 x 4.7uF capacitor
	- 1 x XC6206-1.8V LDO

- PTFE Mouse Skates

- Micro USB Cable for v2 or USB-C cable for v3 charging

- Mounting Hardware
	- 7 x Heat Inserts M2 x 3 x 3.2
	- 3 x M2 x 4 Screw
	- 4 x M2 x 7 Screw

- **FOR V3 ONLY**:
	- 500mAh battery with JST connector
	- SPDT / 1P2T PCB slide switch

## Pinout

|Component|Usage|v2 (3.3v/8MHz Pro Micro)|v3 (XIAO ESP32)|
|---|---|---|---|
|**PMW3389**|NCS|D10|D3|
||MOSI|D16 (MOSI)|D10 (MOSI)|
||MISO|D14 (MISO)|D9 (MISO)|
||SCLK|D15 (SCLK)|D8 (SCLK)|
||MOT|D2 (INT 1)|D4|
|**Rotary Encoder w/Switch**|Rotary Encoder A|D3 (INT 0)|D6|
||Rotary Encoder B|D7 (INT 6)|D0|
||Encoder Switch S2 (Middle Click)|D8|D7|
|**Switches**|Switch 1 (Left Click)|D4|D1|
||Switch 2 (Right Click)|D9|D2|

## Documentation & Credits

- [Build & Design Log](CHANGELOG.md)
- [Third-Party Credits & Libraries](CREDITS.md)
- [MIT License](LICENSE)
