#pragma config(Sensor, S1,     MSPPS,                sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#include "mindsensors-pressure.h"

task main () {
  long abspressure;
  long gaugepressure;

  // set the sensor to kilo Pascals
  MSPPSsetUnit(MSPPS, MSPPS_UNIT_PSI);

  sleep(100);
  MSPPSsetRefPressure(MSPPS);
  sleep(100);

  displayCenteredTextLine(0, "Mindsensors");
  displayCenteredBigTextLine(1, "PPS-v3");
  displayCenteredTextLine(3, "Test 1");
  sleep(2000);

  // Read the current pressure and feed that to the ref pressure
  // abspressure = MSPPSreadAbsPressure(MSPPS);
  // MSPPSsetRefPressure(MSPPS, abspressure);

  // you can also do this
  MSPPSsetRefPressure(MSPPS);

  while (true) {
    eraseDisplay();

    abspressure = MSPPSreadAbsPressure(MSPPS);
    gaugepressure = MSPPSreadGaugePressure(MSPPS);

    displayTextLine(0,"MSPPS Test 1");

    displayTextLine(2, "Pressure (KPA):");
    displayTextLine(3, "Abs: %d", abspressure);
    displayTextLine(4, "Gauge: %d", gaugepressure);
    sleep(100);
  }
}

/*
 * $Id: mindsensors-pressure-test1.c $
 */
