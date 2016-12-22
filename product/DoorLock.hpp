#pragma once
#include <string>
#include "SluiceNetworkHandler.hpp"

enum DoorLockState
{
	DoorLockStateWorking,
	DoorLockStateDamaged
};

class DoorLock
{
protected:
	SluiceNetworkHandler* handler;
	std::string door_name;
	DoorLockState state;
public:
	DoorLock(SluiceNetworkHandler* handler, const std::string& door_name);
	virtual bool Lock();
	virtual bool Unlock();
	virtual void Update();
	DoorLockState GetState();
};