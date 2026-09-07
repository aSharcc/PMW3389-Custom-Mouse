# Third-Party Credits 

This project was developed using the following third-party resources for
reference, comparison, and component integration.

## Firmware & Technical References

* **PixArt PMW3389 Datasheet:** [PixArt Imaging](https://www.pixart.com/products-detail/4/PMW3389DM-T3QU/)

* **PMW3360/PMW3389 Breakout Board:** [kbjunky/PMW3360](https://github.com/kbjunky/PMW3360/) — MIT License.
  Used to compare and verify hardware designs.

* **PMW3389 Arduino Firmware References:**
  * [Creasento/PWM3389_Arduino](https://github.com/Creasento/PWM3389_Arduino/) — GNU GPL v3.0.
  * [mrjohnk/PMW3389DM](https://github.com/mrjohnk/PMW3389DM/) — used as a reference for understanding PMW3389 communication.

  These projects were used for reference and comparison during development.
  The firmware in this project was written independently.

## KiCad Symbols and Footprints

* **PMW3389 Footprint:** [SnapEDA / PixArt PMW3360DM-T2QU](https://www.snapeda.com/parts/PMW3360DM-T2QU/PixArt/view-part/) — SnapEDA licensing terms / applicable Design Exception.

* **Arduino Pro Micro Footprint:** [SnapEDA / SparkFun DEV-12587](https://www.snapeda.com/parts/DEV-12587/SparkFun%20Electronics/view-part/)

* **Seeed Studio XIAO ESP32C3:** [SnapEDA / XIAO ESP32C3](https://www.snapeda.com/parts/XIAO%20ESP32C3/Seeed%20Studio/view-part/)

* **Mouse Switch Footprint:** [SnapEDA / Omron D2FC-F-7N(100M)](https://www.snapeda.com/parts/D2FC-F-7N(100M)/Omron/view-part/)

* **Other Components:** KiCad built-in libraries — [KiCad](https://www.kicad.org/).

## 3D CAD References

The following third-party 3D models were used during mechanical development
for component placement, clearance checking, and shell design.

These models are not part of the original design work of this project.

* **PMW3360 Sensor:** [GrabCAD](https://grabcad.com/library/pmw3360dm-mouse-sensor-1)
* **Arduino Pro Micro USB-C:** [GrabCAD](https://grabcad.com/library/arduino-pro-micro-usb-type-c-1)
* **Kailh Mouse Switch:** [GrabCAD](https://grabcad.com/library/tiny-switch-kailh-mouse-1)
* **EC11 Rotary Encoder:** [GrabCAD](https://grabcad.com/library/ec11-rotary-encoder-dode-switch-15mm-1)
* **2.54mm Female Pin Header:** [GrabCAD](https://grabcad.com/library/2-54mm-female-pin-header-1)
* **2.54mm Male Pin Header:** [GrabCAD](https://grabcad.com/library/2-54mm-male-pin-header-1)

The PMW3360 model is used as a mechanical reference for the PMW3389 because
the relevant physical package/footprint is shared.

The female and male pin header models are provided under the
**Free Digital Asset Commercial License v1.9**. Where these models are
redistributed, the original license text is retained with the files.