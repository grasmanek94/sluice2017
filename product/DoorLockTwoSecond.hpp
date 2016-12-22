#pragma once
#include "DoorLock.hpp"

class DoorLockTwoSecond : public DoorLock
{
public:
	DoorLockTwoSecond(SluiceNetworkHandler* handler, const std::string& door_name);
	virtual bool Lock();
	virtual bool Unlock();
	virtual void Update();
};