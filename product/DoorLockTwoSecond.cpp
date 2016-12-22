#include "DoorLockTwoSecond.hpp"

DoorLockTwoSecond::DoorLockTwoSecond(SluiceNetworkHandler* handler, const std::string& door_name)
	: DoorLock(handler, door_name)
{
}

bool DoorLockTwoSecond::Lock()
{
	return false;
}

bool DoorLockTwoSecond::Unlock()
{
	return false;
}

void DoorLockTwoSecond::Update()
{
}
