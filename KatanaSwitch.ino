//
//  KatanaSwitch.ino
//  KatanaSwitch
//
//  Created by Chris Pearson on 03/01/2019.
//  Copyright © 2018 Chris Pearson. All rights reserved.
//

const int debounceMillis = 10;

const int channels = 4;
int channel = 0;
int lastChannel = 0;

int buttonPins[channels] = {3, 4, 5, 6};
int ledPins[channels] = {7, 8, 9, 10};
const int channelPin = 1;
const int bankPin = 2;

int channelSettings[channels][2] = {
    // Channel, Bank
    {LOW, LOW},
    {HIGH, LOW},
    {LOW, HIGH},
    {HIGH, HIGH}};

void setup()
{
  // initialise all the pins, buttons to INPUT_PULLUP, LEDS to OUTPUT
  for (int i = 0; i < channels; i++)
  {
    pinMode(buttonPins[i], INPUT_PULLUP); // Set button pin to an input
    pinMode(ledPins[i], OUTPUT);          // Set the led pin to an output
    digitalWrite(ledPins[i], LOW);        // Make sure the Led is off
  }

  pinMode(channelPin, OUTPUT);
  pinMode(bankPin, OUTPUT);

  setChannel(0);
}

void loop()
{
  // Test all the buttons for a press
  for (int i = 0; i < channels; i++)
  {
    if (digitalRead(buttonPins[i]) == LOW)
    { // Using INPUT_PULL up so HIGH is off, LOW is on.

      delay(debounceMillis); // super basic debouce as we don't want to add too much delay.

      if (digitalRead(buttonPins[i]) == LOW)
      {
        setChannel(i);
        break; // if one button is high don't bother testing the rest
      }
    }
  }
}

void setChannel(int channel)
{
  // Toggle the LEDs
    digitalWrite(lastChannel, LOW);
    lastChannel = channel;
    digitalWrite(ledPins[i], HIGH);

    setRelays(channel);
}

void setRelays(int channel)
{
  digitalWrite(channelPin, channelSettings[channel][0]);
  digitalWrite(bankPin, channelSettings[channel][1]);
}