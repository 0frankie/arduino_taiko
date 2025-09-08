# arduino_taiko
A Taiko-inspired game implemented on an Arduino Uno-R3

> Note: Code is very unoptimized at the moment. There were a lot of hoops we had to jump through because the R3 didn't support multithreading, e.g., the loops of `delay(1)` waiting for user input.

## Demo
![arduino_taiko_demo.gif](resources/arduino_taiko_demo.gif)
> full video is available at `resources/arduino_taiko_demo.mp4`

## Schematic
![arduino_taiko_schematic.png](resources/arduino_taiko_schematic.png)

## Playing a different song
If you want to input a custom song, use [MrReadBeard's XML to Arduino Parser](https://github.com/MrRedBeard/DotNet-MXL-Parsing-for-Arduino?tab=readme-ov-file), then replace one of the melody and duration arrays with the contents of the output.
> Because of the limited amount of RAM on an Arduino Uno, the song might need to be cut down in duration and melody.
