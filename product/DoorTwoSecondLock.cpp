#include "DoorTwoSecondLock.hpp"
#include "DoorLockTwoSecond.hpp"

DoorTwoSecondLock::DoorTwoSecondLock(SluiceNetworkHandler* handler, const std::string& door_name)
	: Door(handler, door_name, new DoorLockTwoSecond(handler, door_name))
{}
