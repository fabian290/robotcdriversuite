#pragma config(Sensor, S1,     LLEADER,             sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: mindsensors-lineleader-test2.c $
 */

/**
 * mindsensors-lineleader.h provides an API for the Mindsensors LineLeader Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.60 AND HIGHER.

 * Xander Soldaat (xander_at_botbench.com)
 * 28 November 2009
 * version 0.2
 */

#include "mindsensors-lineleader.h"

task main {
  byte sensor = 0;
  tByteArray signalstr;

  while (true) {
    // Fetch the data from the sensor
    sensor = LLreadResult(LLEADER);

    // Re75ad the raw sensor data (8 bit data)
    LLreadSensorRaw(LLEADER, signalstr);

    // This clears the entire area occupied by the small rectangles
    eraseRect(6,62, 91, 43);
    for (int i = 0; i < 8; i++) {
      // Draw the rectangles for the signal strength first
      drawRect(6+(i*11),62, 14+(i*11), 50);
      fillRect(6+(i*11),51+signalstr[i]/10, 14+(i*11), 50);
      // Draw a black rectangle if the sensor has detected the line,
      // a hollow one when nothing has been detected.
      if ((sensor >> i) & 1) {
        fillRect(6+(i*11),48, 14+(i*11), 43);
      } else {
        drawRect(6+(i*11),48, 14+(i*11), 43);
      }
    }
    // Display the actual signal strength for each sensor
    for (int i = 0; i < 7; i+=2) {
      displayTextLine(i/2+3, "S: %3d S: %3d", (int)signalstr[i], (int)signalstr[i+1]);
    }
    sleep(50);
  }
}

/*
 * $Id: mindsensors-lineleader-test2.c $
 */
