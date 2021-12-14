#ifndef GLOBE_H
#define GLOBE_H

void SetUpperThruster(int Voltage);
void SetHorizontalThruster(int Left, int Right);
void SetMiddleThruster(int Voltage);
void SetMiddleClaw(int Voltage);
void SetRightClaw(int Voltage);
void SetMicroROVCollector(int Voltage);

void SetMovementControl();
void SetClaw();
void SetMicroROV();
void SetBooster();
void Move(int Distance, int LeftVoltage, int RightVoltage, int MiddleVoltage);

#endif
