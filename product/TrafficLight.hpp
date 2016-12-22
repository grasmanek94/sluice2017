#pragma once
#include <string>
#include <map>
#include "SluiceNetworkHandler.hpp"

enum TrafficLightPosition
{
	TrafficLightPositionOuter,
	TrafficLightPositionInner
	
};

enum TrafficLightState
{
	TrafficLightStateOff,
	TrafficLightStateRed,
	TrafficLightStateGreen,
	TrafficLightStateAllOn,
	TrafficLightStateUnknown
};

enum TrafficLightStateInternal
{
	TrafficLightStateInternalOff,
	TrafficLightStateInternalOn,
	TrafficLightStateInternalUnknown
};

class TrafficLight
{
private:
	SluiceNetworkHandler* handler;
	std::string door_name;
	TrafficLightPosition position;
	TrafficLightState state;
	std::string index;
	TrafficLightStateInternal red;
	TrafficLightStateInternal green;
public:
	TrafficLight(SluiceNetworkHandler* handler, const std::string& door_name, TrafficLightPosition position);
	bool Off();
	bool Red();
	bool Green();
	TrafficLightState GetState() const;
	TrafficLightState UpdateState();
};

template <typename T = int>
class TrafficLightStateMapper
{
public:
	static TrafficLightStateInternal Map(const std::string& input)
	{
		static bool initialised = false;
		static std::map<std::string, TrafficLightStateInternal> mapper;
		if (!initialised)
		{
			mapper["on;"] = TrafficLightStateInternalOn;
			mapper["off;"] = TrafficLightStateInternalOff;
		}

		std::map<std::string, TrafficLightStateInternal>::iterator found = mapper.find(input);
		if (found == mapper.end())
		{
			return TrafficLightStateInternalUnknown;
		}
		return found->second;
	}
};