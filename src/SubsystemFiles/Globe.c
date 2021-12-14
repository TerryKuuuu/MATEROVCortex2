#include "main.h"
#include "SubsystemHeaders/Globe.h"
//Ports
int MiddleClaw = 9;
int RightClaw = 6;
int UpperThruster1 = 3;
int UpperThruster2 = 4;
int LeftThruster = 5;
int RightThruster = 2;
int MiddleThruster = 8;
int MicroROVCollector = 7;

//Helper functions
void SetUpperThruster(int Voltage){
  motorSet(UpperThruster1, Voltage);
  motorSet(UpperThruster2, Voltage);
}

void SetHorizontalThruster(int Left, int Right){
  motorSet(RightThruster, Right);
  motorSet(LeftThruster, Left);
}

void SetMiddleThruster(int Voltage){
  motorSet(MiddleThruster, Voltage);
}

void SetMiddleClaw(int Voltage){
  motorSet(MiddleClaw, Voltage);
}

void SetRightClaw(int Voltage){
  motorSet(RightClaw, Voltage);
}

// void SetMicroROVThruster(int Voltage){
//   motorSet(MicroROVThruster, Voltage);
// }

void SetMicroROVCollector(int Voltage){
  motorSet(MicroROVCollector, Voltage);
}

//Control

void SetMovementControl(){

  int RightJoystickY = joystickGetAnalog(1, 2);
  int LeftJoystickX = joystickGetAnalog(1,4);
  int LeftJoystickY = joystickGetAnalog(1,3);
  int difference = 15;
  int MaxVoltage = 121;

  if (RightJoystickY > -difference && RightJoystickY < difference) {
    RightJoystickY = 0;
  }
  if (LeftJoystickX > -difference && LeftJoystickX < difference) {
    LeftJoystickX = 0;
  }
  if (LeftJoystickY > -difference && LeftJoystickY < difference) {
    LeftJoystickY = 0;
  }

  // if (RightJoystickY > -MaxVoltage && RightJoystickY < MaxVoltage) {
  //   RightJoystickY = MaxVoltage;
  // }
  // if (LeftJoystickX > -MaxVoltage && LeftJoystickX < MaxVoltage) {
  //   LeftJoystickX = MaxVoltage;
  // }
  // if (LeftJoystickY > -MaxVoltage && LeftJoystickY < MaxVoltage) {
  //   LeftJoystickY = MaxVoltage;
  // }
  //
  // SetUpperThruster(RightJoystickY);
  // SetHorizontalThruster(-(LeftJoystickY + LeftJoystickX), -(LeftJoystickY - LeftJoystickX));

  int left = -(LeftJoystickY + LeftJoystickX);
  int right = -(LeftJoystickY - LeftJoystickX);
  int middle = -LeftJoystickY;

  if (left > MaxVoltage) {
    left = MaxVoltage;
  } else if (left < -MaxVoltage) {
    left = -MaxVoltage;
  }

  if (right > MaxVoltage) {
    right = MaxVoltage;
  } else if (right < -MaxVoltage) {
    right = -MaxVoltage;
  }

  if (RightJoystickY > MaxVoltage) {
    RightJoystickY = MaxVoltage;
  } else if (RightJoystickY < -MaxVoltage) {
    RightJoystickY = -MaxVoltage;
  }

  if (middle > MaxVoltage) {
    middle = MaxVoltage;
  } else if (middle < -MaxVoltage) {
    middle = -MaxVoltage;
  }

  SetUpperThruster(RightJoystickY);
  SetHorizontalThruster(left, right); //Brian problem
  SetMiddleThruster(middle);

}

void SetClaw(){
  //2 is down 1 is up

  int MaxVoltage = 100;
  int R1 = joystickGetDigital(1, 6, JOY_UP);
  int R2 = joystickGetDigital(1, 6, JOY_DOWN);
  int L1 = joystickGetDigital(1, 5, JOY_UP);
  int L2 = joystickGetDigital(1, 5, JOY_DOWN);

  SetMiddleClaw(-(MaxVoltage * (L2 - L1)));
  SetRightClaw(-(MaxVoltage * (R2 - R1)));

}

void SetMicroROV(){

  int MaxVoltage = 121;
  int LeftUp = joystickGetDigital(1, 7, JOY_UP);
  int LeftDown = joystickGetDigital(1, 7, JOY_DOWN);
  int RightUp = joystickGetDigital(1, 8, JOY_UP);
  int RightDown = joystickGetDigital(1, 8, JOY_DOWN);

  // SetMicroROVThruster(-(121 * (LeftDown - LeftUp)));
  SetMicroROVCollector(-(MaxVoltage * (RightDown - RightUp)));

}

// void SetBooster(){
//
//   int MaxVoltage = 121;
//   int RightR = joystickGetDigital(1, 8, JOY_RIGHT);
//
//   SetMiddleThruster(MaxVoltage);
//
// }

//Autonomous functions
void Move(int Distance, int LeftVoltage, int RightVoltage, int MiddleVoltage){
  // SetUpperThruster(35);
  SetHorizontalThruster(LeftVoltage, RightVoltage);
  SetMiddleThruster(MiddleVoltage);
  for (int Sec = 0; Sec < Distance; Sec = Sec + 1){
    delay(1000);
  }
  // SetUpperThruster(0);
  SetHorizontalThruster(0, 0);
}
