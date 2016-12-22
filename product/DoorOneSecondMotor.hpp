#pragma once
#include "Door.hpp"

class DoorOneSecondMotor : public Door
{
public:
	DoorOneSecondMotor(SluiceNetworkHandler* handler, const std::string& door_name);
};