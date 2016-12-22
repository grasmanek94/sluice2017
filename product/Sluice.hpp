#pragma once
#include <map>
#include "SluiceNetworkHandler.hpp"
#include "Door.hpp"
#include "DoorTwoSecondLock.hpp"
#include "DoorOneSecondMotor.hpp"
#include "Timer.hpp"

enum WaterLevel
{
	WaterLevelLow,
	WaterLevelBelowValve2,
	WaterLevelAboveValve2,
	WaterLevelAboveValve3,
	WaterLevelHigh,
	WaterLevelUnknown
};

class Sluice
{
private:
	SluiceNetworkHandler* handler;
	int sluice_nummer;
	Door* door_low;
	Door* door_high;
	WaterLevel water_level;
	Timer water_level_timer;
	WaterLevel UpdateWaterLevel();
public:
	Sluice(SluiceNetworkHandler* handler, int sluice_nummer);
	~Sluice();
	WaterLevel GetWaterLevel();
	Door* DoorLow();
	Door* DoorHigh();
	void Update();
};

template <typename T = int>
class WaterLevelMapper
{
public:
	static WaterLevel Map(const std::string& input)
	{
		static bool initialised = false;
		static std::map<std::string, WaterLevel> mapper;
		if (!initialised)
		{
			mapper["low;"] = WaterLevelLow;
			mapper["belowValve2;"] = WaterLevelBelowValve2;
			mapper["aboveValve2;"] = WaterLevelAboveValve2;
			mapper["aboveValve3;"] = WaterLevelAboveValve3;
			mapper["high;"] = WaterLevelHigh;
		}

		std::map<std::string, WaterLevel>::iterator found = mapper.find(input);
		if (found == mapper.end())
		{
			return WaterLevelUnknown;
		}
		return found->second;
	}
};