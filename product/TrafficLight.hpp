#pragma once
#include <string>
#include "SluiceNetworkHandler.hpp"

enum TrafficLightPosition
{
	TrafficLightPositionInner,
	TrafficLightPositionOuter
};

enum TrafficLightState
{
	TrafficLightStateOff,
	TrafficLightStateRed,
	TrafficLightStateGreen
};

class TrafficLight
{
private:
	SluiceNetworkHandler* handler;
	std::string door_name;
	TrafficLightPosition position;
	TrafficLightState state;
public:
	TrafficLight(SluiceNetworkHandler* handler, const std::string& door_name, TrafficLightPosition position);
	bool Off();
	bool Red();
	bool Green();
	TrafficLightState GetState() const;
};