#pragma config(Sensor, S1,     HTTMUX,              sensorAnalogInactive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-touchmux-test1.c $
 */

/**
 * hitechnic-touchmux.h provides an API for the HiTechnic Touch Sensor MUX.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.60 AND HIGHER.

 * Xander Soldaat (xander_at_botbench.com)
 * 25 November 2009
 * version 0.2
 */

#include "hitechnic-touchmux.h"

task main () {
  displayCenteredTextLine(0, "HiTechnic");
  displayCenteredBigTextLine(1, "TMUX");
  displayCenteredTextLine(3, "Test 1");
  displayCenteredTextLine(5, "This is for the");
  displayCenteredTextLine(6, "Touch MUX");
  sleep(2000);
  while (true) {
    eraseDisplay();
    displayTextLine(0, "HT Touch MUX");

    // Get the raw data from the sensor, this is not processed
    // by the driver in any way.
    displayTextLine(1, "Raw: %d", SensorValue[HTTMUX]);

    // Go through each possible touch switch attached to the TMUX
    // and display whether or not is active (pressed)
    for (int i = 1; i < 5; i++) {
      if (HTTMUXisActive(HTTMUX, i))
        displayTextLine(i+2, "Touch %d: on", i);
      else
        displayTextLine(i+2, "Touch %d: off", i);
    }

    // Display the binary value of the active touch switches
    // 0 = no touch, 1 = touch 1 active, 2 = touch 2 active, etc.
    // touch 1 + touch 2 active = 1 + 2 = 3.
    displayTextLine(7, "Status: %d", HTTMUXgetActive(HTTMUX));
    sleep(50);
  }
}

/*
 * $Id: hitechnic-touchmux-test1.c $
 */
