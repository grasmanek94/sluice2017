#pragma once
#include "SluiceNetworkHandler.hpp"
#include "Door.hpp"
#include "DoorTwoSecondLock.hpp"
#include "DoorOneSecondMotor.hpp"

enum WaterLevel
{
	WaterLevelLow,
	WaterLevelBelowValve2,
	WaterLevelAboveValve2,
	WaterLevelAboveValve3,
	WaterLevelHigh
};

class Sluice
{
private:
	SluiceNetworkHandler* handler;
	int sluice_nummer;
	Door* door_low;
	Door* door_high;
public:
	Sluice(SluiceNetworkHandler* handler, int sluice_nummer);
	~Sluice();
	WaterLevel GetWaterLevel();
	Door* DoorLow();
	Door* DoorHigh();
	void Update();
};