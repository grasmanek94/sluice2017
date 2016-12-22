#include "DoorLock.hpp"

DoorLock::DoorLock(SluiceNetworkHandler* handler, const std::string& door_name)
{
}

bool DoorLock::Lock()
{
	return false;
}

bool DoorLock::Unlock()
{
	return false;
}

DoorLockState DoorLock::GetState()
{
	return DoorLockState();
}

void DoorLock::Update()
{

}
