/*
 * Let's raise some infrared hell!
 *
 * The Arduino Discordian Remote is designed to create confusion
 * and disruption at your local mall.
 * Build it, disguise it the best you can and leave it in front
 * a wall of TVs.
 * It's designed to be activated by motion, and to send random
 * infrared commands to the most popular TV brands for 10 seconds
 * after a movement was detected.
 *
 * All hail discordian!
 *
 * Copyright (c) 2012 Davide Alberani <da@erlug.linux.it>
 *
 * TODO /ideas:
 * - support other brands.
 * - send random raw commands.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <IRremote.h>

/* Customize your project. */

// Uncomment to turn on debugging over serial port.
//#define DEBUG
// Uncomment and set, to force the use of a single brand.
//#define FORCED_BRAND RC5

// Pin of the IR emitter.
const int EMITTER_PIN = 3;
// Pin of the PIR sensor.
const int PIR_PIN = 7;
// Start after X ms (PIR sensors are slow to settle).
const unsigned long START_DELAY = 30000;
// Emit random commands for X ms, after a movement was detected.
const unsigned long BURST_LENGTH = 10000;


/* Things you have to change to support other brands. */

#define NUMBER_OF_BRANDS 8
const unsigned int BRANDS[NUMBER_OF_BRANDS] = {NEC, SONY, RC5, RC6, DISH, SHARP, JVC, PANASONIC};

// Command length (in bits) for different versions of the Sony protocol.
#define NUMBER_OF_SONY_VERSIONS 3
const int sonyVersions[NUMBER_OF_SONY_VERSIONS] = {12, 15, 20};


/* Nothing to configure below.  Go away. */

IRsend irsend;
unsigned long lastMotionTime = 0;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(EMITTER_PIN, OUTPUT);
  Serial.begin(9600);
  delay(START_DELAY);
#ifdef DEBUG
  Serial.println("Start messing with IR devices");
#endif
}


void loop() {
  unsigned long currentTime = millis();
  if (digitalRead(PIR_PIN)) {
    lastMotionTime = currentTime;
  }
  if ((currentTime - lastMotionTime) < BURST_LENGTH) {
    sendCommand(randomBrand());
  }
}


/**
  Return a random brand.
 */
unsigned int randomBrand() {
#ifdef FORCED_BRAND
  return FORCED_BRAND;
#else
  return BRANDS[random(NUMBER_OF_BRANDS)];
#endif
}


/**
  Given a brand and the number of command bits,
  return the upper limit for the command.
 */
unsigned int upperLimitForBrand(unsigned int brand, int nbits) {
  switch (brand) {
    case RC5:
      if (nbits == 11) {
        return 64;
      } else {
        return 128;
      }
      break;
    case SONY:
      return 128;
      break;
    default:
      // I don't know about other protocols...
      return 256;
  }
}


/**
  Return a possible length of commands (in bits)
  for the given brand.
 */
int nbitsForBrand(unsigned int brand) {
  switch (brand) {
    case JVC:
      return 16;
      break;
    case NEC:
      return 16;
      break;
    case SHARP:
      return 15;
      break;
    case RC5:
      return random(11, 13);
      break;
    case RC6:
      return 16;
      break;
    case SONY:
      return sonyVersions[random(NUMBER_OF_SONY_VERSIONS + 1)];
      break;
    default:
      return 12; // XXX: is this reasonable?
  }
}


/**
  Send a random command to the specified brand of devices.
 */
void sendCommand(unsigned int brand) {
  int nbits = nbitsForBrand(brand);
  unsigned long command = random(upperLimitForBrand(brand, nbits));
#ifdef DEBUG
  Serial.print("Brand: ");
  Serial.print(brand);
  Serial.print(", Command: ");
  Serial.println(command);
#endif
  switch (brand) {
    case NEC:
      irsend.sendNEC(command, nbits);
      break;
    case SONY:
      // According to the protocol, Sony
      // commands must be sent three times.
      for (int i = 0; i < 3; i++) {
        irsend.sendSony(command, nbits);
      }
      break;
    case RC5:
      irsend.sendRC5(command, nbits);
      break;
    case RC6:
      irsend.sendRC6(command, nbits);
      break;
    case DISH:
      irsend.sendDISH(command, nbits);
      break;
    case SHARP:
      irsend.sendSharp(command, nbits);
      break;
    case JVC:
      irsend.sendJVC(command, nbits, random(2));
      break;
    case PANASONIC:
      irsend.sendPanasonic(random(2), command);
    // TODO: also send raw data?
  }
  // XXX: introduce a delay?
}

