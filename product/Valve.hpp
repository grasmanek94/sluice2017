#pragma once
#include <string>
#include <map>
#include "SluiceNetworkHandler.hpp"

enum ValvePosition
{
	ValvePositionLow = 1,
	ValvePositionMid,
	ValvePositionHigh
};

enum ValveState
{
	ValveStateClosed,
	ValveStateOpen,
	ValveStateUnknown
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
	ValveState UpdateState();
};


template <typename T = int>
class ValveStateMapper
{
public:
	static ValveState Map(const std::string& input)
	{
		static bool initialised = false;
		static std::map<std::string, ValveState> mapper;
		if (!initialised)
		{
			mapper["closed;"] = ValveStateClosed;
			mapper["open;"] = ValveStateOpen;
		}

		std::map<std::string, ValveState>::iterator found = mapper.find(input);
		if (found == mapper.end())
		{
			return ValveStateUnknown;
		}
		return found->second;
	}
};