#pragma config(Sensor, S1,     PSPNXV4,        sensorI2CCustomFastSkipStates)
#pragma config(Motor,  motorA,          MOT_A,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorB,          MOT_B,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          MOT_C,     tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: mindsensors-ps2ctrl-v4-test1.c $
 */

/**
 * mindsensors-ps2ctrl-v4.h provides an API for the Mindsensors PS2 controller sensor
 * with referee signal receiver.  This program demonstrates how to use that API
 * to control a 3-wheeled omniwheeled robot.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.60 AND HIGHER.

 * Xander Soldaat (xander_at_botbench.com)
 * 02 August 2012
 * version 0.1
 */


#include "mindsensors-ps2ctrl-v4.h"

#define MAXMOTORSPEED 90.0

// Use some trig to culcalate the required power for each motor
void MoveRobot(int angle, int Vb, int rotSpeed) {
  float Vw1, Vw2, Vw3, maxSpeed, norm_factor;
  int iVw1, iVw2, iVw3;

  // This is where the magic happens.  The actual formula is
  // Vw = rotSpeed + Vb * ((cosDegrees(wheelAngle) * cosDegrees(movementAngle)) + (sinDegrees(wheelAngle) * sinDegrees(movementAngle)))
  // I have optimised the formulae below to reduce the number of operations required to calculate the motor speeds
  // since the motorAngle value never changes and cancels some things out, further simplifying the calculations.
  // I like simple!

  Vw1 = rotSpeed + Vb * cosDegrees(angle);
  Vw2 = rotSpeed + Vb * (-0.5 * cosDegrees(angle) + 0.866025 * sinDegrees(angle));
  Vw3 = rotSpeed + Vb * (-0.5 * cosDegrees(angle) - 0.866025 * sinDegrees(angle));

  // This makes sure the motor values never exceed the maximum (MAXMOTORSPEED)
  maxSpeed = max3(abs(Vw1), abs(Vw2), abs(Vw3));

  norm_factor = (maxSpeed > MAXMOTORSPEED) ? (MAXMOTORSPEED / maxSpeed) : 1.0;

  iVw1 = round(Vw1 * norm_factor);
  iVw2 = round(Vw2 * norm_factor);
  iVw3 = round(Vw3 * norm_factor);

  motor[motorA] = iVw1;
  motor[motorB] = iVw2;
  motor[motorC] = iVw3;
}


task main ()
{
  // This is the struct that holds all the info on all buttons and joypads/sticks
  tPSP controller;

  int angle;
  int speed;
  int rotation;

  while (true)
  {
    // Read the state of the buttons
    PSPV4readButtons(PSPNXV4, controller);

    // Two controls are used:
    // The left joystick controls speed and direction
    // The right joystick controls rotational speed

    // Calculate the angle we need to travel at using simple geometry
    angle = radiansToDegrees(atan2(-controller.joystickLeft_x, -controller.joystickLeft_y));

    // This is the length of the vector, which is based on the amount we've moved the
    // joystick in the X and Y directions
    speed = sqrt((controller.joystickLeft_x * controller.joystickLeft_x) +
		                    (controller.joystickLeft_y*controller.joystickLeft_y));

		// Rotation speed is controlled by the right joystick
		rotation = -controller.joystickRight_x;

    displayCenteredTextLine(1, "%d:%d", controller.joystickLeft_x, controller.joystickLeft_y);
    displayCenteredTextLine(3, "%d:%d", controller.joystickRight_x, controller.joystickRight_y);
		displayCenteredTextLine(5, "%d", angle);
		displayCenteredTextLine(6, "%d", speed);
		displayCenteredTextLine(7, "%d", rotation);
		MoveRobot(angle, speed, rotation);
    sleep(100);
  }
  playSound(soundBeepBeep);
  MoveRobot(0, 0, 0);
  while (bSoundActive) EndTimeSlice();
  sleep(100);
}


/*
 * $Id: mindsensors-ps2ctrl-v4-test1.c $
 */
