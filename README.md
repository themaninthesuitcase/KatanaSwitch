# KatanaSwitch

**KatanaSwitch** is the arduino firmware code for a basic 4 button foot switch for the BOSS Katana 50 amplifer.  

Normally a 2 button latching footswitch is used, one switching channels and the other switching banks.  If you wanted to change from A-1 to B-2 this would require both buttons to be toggled.  This pedal features 4 momentary switches which, via the arduino, gives access to all 4 channels via a single button press.

The Katana 50 footswitch jack is a TRS connection with Tip switching the channel and Ring switching the bank.  To enable footswitching simply insert a TRS cable into the foot switch jack.  This will access to the "panel" but all controls will work as normal.  If not saved any changes made will be lost when switching channels.

*note: This will also work with the Katana 100 line but the GA-FC footswitch will do the same off the shelf.*

## Licencing

This project is considered to be [Creative Commons Attribution-NonCommercial-ShareAlike][cc].  Basically you can make them, but don't sell them.

## Channel switching

The channels and banks are selected by shorting either the tip or ring to the Sleeve.  The map of channels to connections is below, with HIGH meaning the connection is shorted to the sleeve and LOW meaning open circuit.

| Channel | Tip | Ring |
|---------|-----|------|
| A-1 | HIGH | HIGH |
| A-2 | HIGH | LOW |
| B-1 | LOW | HIGH |
| B-2 | LOW | LOW  |

If you connect a TRS cable to the amp end only then it will switch to B-2 as the amp detects the jack but the connections are open.

## Circuit

The firmware assumes the below circuit.  If you create your own then you may need to update the pins used for the switches in and the LED outs.

*note: On the Arduino Nano used pins A6 and A7 are analogue input only and will not function in digital mode as either an input or output.*

![Circuit Diagram](/images/KatanaSwitchCircuit.png)

**For resistors R1-R4 you may need to change the value dependant on your chosen LEDs.**  Use an [LED Calculator][ledcalc], the supply voltage will be 5V, the forward Volatage and current will depend on your LED, check the datasheet.

A PCB design is available for convenience as used in my own pedal.  This is 76x36mm in size, so is a bit awkward to fit an enclosure with the switches and LEDs.  This is something I may address in a future iteration.

The files to make a board can be found in the ```/GerberFiles``` folder.  I used [JLCPCB] in China.

[jlcpcb]: https://jlcpcb.com/
[ledcalc]: http://led.linear1.org/1led.wiz/
[cc]: https://creativecommons.org/licenses/by-nc-sa/4.0/