#include "DoorOneSecondMotor.hpp"
#include "DoorEngineOneSecond.hpp"

DoorOneSecondMotor::DoorOneSecondMotor(SluiceNetworkHandler* handler, const std::string& door_name)
	: Door(handler, door_name, new DoorEngineOneSecond(handler, door_name))
{}
