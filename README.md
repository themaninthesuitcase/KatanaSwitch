# KatanaSwitch

**KatanaSwitch** is the Arduino firmware code for a basic 4 button foot switch for the BOSS Katana 50 amplifer.

![Completed Foot Switch using 1032L enclosure](/images/IMG_0120.jpg)

Normally a 2 button latching foot-switch is used, one switching channels and the other switching banks. Say you wanted to change from A-1 to B-2 this would require both buttons to be toggled, one to swap channels and the other to swap banks.  This pedal features 4 momentary switches giving access to all 4 channels via a single button press.

The Katana 50 foot-switch jack is a TRS (Stereo) connection with Tip switching the channel and Ring switching the bank.  To enable foot-switching simply insert a TRS cable into the foot switch jack.

*Note: This will also work with the Katana 100 line but the GA-FC foot-switch will do the same off the shelf.*

## Licensing

This project is considered to be [Creative Commons Attribution-NonCommercial-ShareAlike][cc].  Basically you can make them, but don't sell them.

## Channel switching

The channels and banks are selected by shorting either the tip or ring to the Sleeve.  The map of channels to connections is below, with HIGH meaning the connection is shorted to the sleeve and LOW meaning open circuit.

| Channel | Tip | Ring |
|---------|-----|------|
| A-1 | HIGH | HIGH |
| A-2 | HIGH | LOW |
| B-1 | LOW | HIGH |
| B-2 | LOW | LOW |

If you connect a TRS cable to the amp end only then it will switch to B-2 as the amp detects the jack but the connections are open.

## Circuit

The firmware assumes the below circuit.  If you create your own then you may need to update the pins used for the switches in and the LED outs.  These are all defined in constants at the top of the file.

*Note: On the Arduino Nano used pins A6 and A7 are analogue input only and will not function in digital mode as either an input or output.*

![Circuit Diagram](/images/KatanaSwitchCircuit.png)

### Bill Of Materials

 * **A1** Arduino Nano v3
 * **IC1** ILD74 Optocoupler
 * **J1** 1/4" TRS (Stereo) jack socket
 * **R1** 220Ω - Current limited Resistor (CLR) Channel 1*
 * **R2** 220Ω - CLR Channel 2
 * **R3** 220Ω - CLR Channel 3
 * **R4** 220Ω - CLR Channel 4
 * **R5** 220Ω - CLR Optocoupler
 * **R6** 220Ω - CLR Optocoupler

**For resistors R1-R4 you may need to change the value dependent on your chosen LEDs.**  Use an [LED Calculator][ledcalc], the supply voltage will be 5V, the forward voltage and current will depend on your LED, check the datasheet.

A PCB design is available for convenience as used in my own pedal.  This is 76x36mm in size, so is a bit awkward to fit in some enclosures with the switches and LEDs.  This is something I may address in a future iteration.

The files to make a board can be found in the ```/GerberFiles``` folder.  I used [JLCPCB] in China to manufacture the boards.

![JLCPCB made boards](/images/IMG_9425.jpg)

The PCB was laid out with a 1590BB in mind.  My build used a [1032L], though a [Hammond 1590BX][1590bx] is similar in size, though shallower, and will probably work well too if care is taken to fit the PCB.  Using a 4 in line enclosure you will either need to adjust the output pin order, or you will have to use some non-optimal wiring.  See the [Layout-1032L][1032L-branch] branch for the changes I used.

![Internals of my 1032L build](/images/IMG_0117.jpg)

## Known Issues

 * LED for Channel B-2 will remain on dimly at all times.  This is because I used pin 13 which is the pin for the built in LED.  If revised in future I will change this to another pin.

[jlcpcb]: https://jlcpcb.com/
[ledcalc]: http://led.linear1.org/1led.wiz/
[cc]: https://creativecommons.org/licenses/by-nc-sa/4.0/
[1590bx]: http://www.hammondmfg.com/pdf2/1590BX.pdf
[1032L]: http://www.timetravelaudio.co.uk/shop/components/powder-coated-die-cast-aluminium-enclosures/
[1032L-branch]: https://github.com/themaninthesuitcase/KatanaSwitch/tree/Layout-1032L