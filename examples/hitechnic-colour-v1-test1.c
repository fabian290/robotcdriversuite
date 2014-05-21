#pragma config(Sensor, S1,     HTCS,                sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-colour-v1-test1.c $
 */

/**
 * hitechnic-colour-v1.h provides an API for the HiTechnic Color Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Changed the intro and info displayed
 * - 0.3: More comments
 * - 0.4: Removed common.h from includes
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.60 AND HIGHER.

 * Xander Soldaat (xander_at_botbench.com)
 * 20 February 2011
 * version 0.4
 */

#include "hitechnic-colour-v1.h"

task main () {
  int red = 0;
  int green = 0;
  int blue = 0;
  int _color = 0;
  string _tmp;

  displayCenteredTextLine(0, "HiTechnic");
  displayCenteredBigTextLine(1, "COLOUR");
  displayCenteredTextLine(3, "Test 1");
  displayCenteredTextLine(5, "Connect sensor");
  displayCenteredTextLine(6, "to S1");
  sleep(2000);

  eraseDisplay();
  while (true) {
    // Read the currently detected colour from the sensor
    _color = HTCSreadColor(HTCS);

    // If colour == -1, it implies an error has occurred
    if (_color < 0) {
      displayTextLine(4, "ERROR!!");
      sleep(2000);
      stopAllTasks();
    }

    // Read the RGB values of the currently colour from the sensor
    // A return value of false implies an error has occurred
    if (!HTCSreadRGB(HTCS, red, green, blue)) {
      displayTextLine(4, "ERROR!!");
      sleep(2000);
      stopAllTasks();
    }

    displayCenteredTextLine(0, "Color: %d", _color);
    displayCenteredBigTextLine(1, "R  G  B");

    eraseRect(0,10, 99, 41);
    fillRect( 0, 10, 30, 10 + (red+1)/8);
    fillRect(35, 10, 65, 10 + (green+1)/8);
    fillRect(70, 10, 99, 10 + (blue+1)/8);
    StringFormat(_tmp, " %3d   %3d", red, green);
    displayTextLine(7, "%s   %3d", _tmp, blue);

    sleep(100);
  }
}

/*
 * $Id: hitechnic-colour-v1-test1.c $
 */
