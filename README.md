# Plywood 7 Segment Digital Clock

Design is done with [FreeCAD](https://www.freecadweb.org/) (Plywood-7-Segment-Digital-Clock.FCStd). This file contains all the source models for 3D printing and the paths for CNC machining (you might have to re-create the paths for your CNC machine but you can use the FreeCAD file for this). My paths are generated to use with a [GRBL](https://github.com/gnea/grbl/wiki) based machine.

## License

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

## Schematic

Connect 5 volts from the micro usb breakout board to the 5 volt (VIN) pin on the ESP module.  
Connect Ground from the micro usb breakout board to the Ground on the ESP module.  
Connect 5 volts from the usb breakout board to 5 volt on the LED strip.  
Connect Ground from the usb breakout board to Ground on the LED strip.  
Connect pin D6 from the ESP module to the Data line on the LED strip.  
Connect pin D8 from the ESP module to one side of the button and connect the other side of the button to 3.3V of the ESP module.  

To power the clock you can use a regular 5V 2A power supply.

| Components                   |
| -------------                |
| ESP8266 Wi-Fi module         |
| USB break out board          |
| 5V 2A power supply           |
| Wires                        |
| Mini breadboard              |

## Indexes of LEDs (2 per segment):

```

    47 46        33 32            17 16        3  2
  48     45    34     31        18     15    4      1
  49     44    35     30   29   19     14    5      0
    57 56        43 42            27 26       13 12
  50     55    36     41   28   20     25    6     11
  51     54    37     40        21     24    7     10 
    52 53        38 39            22 23        8  9
    
```

## YouTube video

<a href="https://youtu.be/EQGggxqPL-g" target="_blank"><img src="https://img.youtube.com/vi/EQGggxqPL-g/0.jpg" 
alt="Click to view: Plywood Clock" width="500" border="1" /></a>
