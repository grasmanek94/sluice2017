#pragma once
#include <string>
#include "SluiceNetworkHandler.hpp"

enum ValvePosition
{
	ValvePositionHigh = 1,
	ValvePositionMid,
	ValvePositionLow
};

enum ValveState
{
	ValveStateClosed,
	ValveStateOpen
};

class Valve
{
private:
	SluiceNetworkHandler* handler;
	std::string door_name;
	ValvePosition position;
	ValveState state;
public:
	Valve(SluiceNetworkHandler* handler, const std::string& door_name, ValvePosition position);
	bool Open();
	bool Close();
	ValveState GetState() const;
};