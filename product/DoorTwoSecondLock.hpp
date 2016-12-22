#pragma once
#include "Door.hpp"

class DoorTwoSecondLock : public Door
{
public:
	DoorTwoSecondLock(SluiceNetworkHandler* handler, const std::string& door_name);
};