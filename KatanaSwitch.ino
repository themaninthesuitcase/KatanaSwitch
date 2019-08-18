//
//  KatanaSwitch.ino
//  KatanaSwitch
//
// Firmware for arduino based channel switching pedal for the
// the Boss Katana 50 Amplifer.
//
//  Created by Chris Pearson on 03/01/2019.
//  Copyright © 2018 Chris Pearson. All rights reserved.
//

// Switching Operations:
// Tip  : Switches between CH1 and CH2
// Ring : Switches between BANK A and BANK B

#define BAUD_RATE 9600

#define BTN_A1 3
#define BTN_A2 11
#define BTN_B1 A4
#define BTN_B2 A0

#define LED_A1 2
#define LED_A2 12
#define LED_B1 A5
#define LED_B2 13

const int debounceMillis = 10;

const int channels = 4;
int lastChannel = 0;

// Pin out Configuration
// NOTE: Analogue pins A6 and A7 are Analog input only on a Nano, we can't really use them here
// 0 based channels are used in the code for simplicity.
// 0 = A-1, 1 = A-2, 2 = B-1 & 3 = B-2
const int buttonPins[channels] = {BTN_A2, BTN_B2, BTN_A1, BTN_B1};
const int ledPins[channels] = {LED_A2, LED_B2, LED_A1, LED_B1};
const int channelPin = A1; // TIP
const int bankPin = A2;    // RING

int channelSettings[channels][2] = {
    // Channel, Bank
    // (Tip, Ring)
    {HIGH, HIGH}, // A1
    {LOW, HIGH},  // A2
    {HIGH, LOW},  // B1
    {LOW, LOW}};  // B2

void setup()
{
  Serial.begin(BAUD_RATE);
  Serial.print("Booting...\n\n");

  // Initialise all the pins, buttons to INPUT_PULLUP, LEDs to OUTPUT
  for (int i = 0; i < channels; i++)
  {
    int led = ledPins[i];
    int button = buttonPins[i];

    // Log some stuff that's usefull when debugging
    Serial.print("CHANNEL: "); Serial.print(i + 1); Serial.print("\n");
    Serial.print("BUTTON PIN: "); Serial.print(button); Serial.print("\n");
    Serial.print("LED PIN: "); Serial.print(led); Serial.print("\n");

    pinMode(button, INPUT_PULLUP); // Set button pins to an input

    pinMode(led, OUTPUT);    // Set the led pin to an output
    digitalWrite(led, HIGH); // Flash them for a pretty start sequence.
    delay(200);
    digitalWrite(led, LOW); // Make sure the LED is off we are done.
  }

  // Setup the channel and bank pins
  pinMode(channelPin, OUTPUT);
  digitalWrite(channelPin, LOW);
  pinMode(bankPin, OUTPUT);
  digitalWrite(bankPin, LOW);

  // Default to the first channel
  setChannel(0);

  Serial.print("Boot completed.\n\n");
}

// Demo mode!
// void loop(){
//   setChannel(0);
//   delay(1000);

//   setChannel(1);
//   delay(1000);

//   setChannel(2);
//   delay(1000);

//   setChannel(3);
//   delay(1000);

// }
void loop()
{
  // Check all the buttons for a press
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
        // Guard against changing to the same channel
        if (i != lastChannel) setChannel(i);

        // If one button is high don't bother testing the rest
        // only one can be on at any one time.
        break;
      }
    }
  }
}

void setChannel(int newChannel)
{
  Serial.print("Changing to channel: "); Serial.print(newChannel); Serial.print("\n");
  Serial.print("Previous channel: "); Serial.print(lastChannel); Serial.print("\n");

  int lastLed = ledPins[lastChannel];
  int newLed = ledPins[newChannel];

  // Update the channel LEDs
  // Turn the last channel LED off
  digitalWrite(lastLed, LOW);

  // Save the new the last channel for the next time we change
  lastChannel = newChannel;

  // Update the output as per the channel selected
  setOutputs(newChannel);

  // Turn on the new channel LED
  digitalWrite(newLed, HIGH);

  Serial.print("Channel changed.\n");
}

void setOutputs(int channel)
{
  digitalWrite(channelPin, channelSettings[channel][0]);
  digitalWrite(bankPin, channelSettings[channel][1]);
}
