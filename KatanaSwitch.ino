//
//  KatanaSwitch.ino
//  KatanaSwitch
//
//  Created by Chris Pearson on 03/01/2019.
//  Copyright © 2018 Chris Pearson. All rights reserved.
//

// Switching Operations:
// Tip  : Switches between CH1 and CH2
// Ring : Switches between BANK A and BANK B

const int debounceMillis = 10;

const int channels = 4;
int channel = 0;
int lastChannel = 0;

// Pin out Configuration
int buttonPins[channels] = {3, 11, A6, A0};
int ledPins[channels] = {2, 12, A7, 13};
const int channelPin = A3;
const int bankPin = A4;

int channelSettings[channels][2] = {
    // Channel, Bank
    // (Tip, Ring)
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
    digitalWrite(ledPins[i], LOW);        // Make sure the LED is off
  }

  pinMode(channelPin, OUTPUT);
  pinMode(bankPin, OUTPUT);

  // Default to the first channel
  setChannel(0);
}

void loop()
{
  // Test all the buttons for a press
  for (int i = 0; i < channels; i++)
  {
    // Using INPUT_PULL up so HIGH is off, LOW is on.
    if (digitalRead(buttonPins[i]) == LOW)
    {
      // Super basic debouce as the complexity of managing multiple inputs isn't necessary.
      // This is blocking but it shouldn't matter much as we're not checking lots of stuff.
      delay(debounceMillis);

      if (digitalRead(buttonPins[i]) == LOW)
      {
        setChannel(i);
        // If one button is high don't bother testing the rest
        // only one can be on at any one time.
        break;
      }
    }
  }
}

void setChannel(int channel)
{
  // Toggle the LEDs
  // Turn the last channel LED off
  digitalWrite(lastChannel, LOW);

  // Update the last channel for the next time we change
  lastChannel = channel;

  // Update the output as per the channel selected
  setRelays(channel);

  // Turn on the new channel LED
  digitalWrite(ledPins[channel], HIGH);
}

void setRelays(int channel)
{
  digitalWrite(channelPin, channelSettings[channel][0]);
  digitalWrite(bankPin, channelSettings[channel][1]);
}