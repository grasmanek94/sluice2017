#include "DoorTwoSecondLock.hpp"

DoorTwoSecondLock::DoorTwoSecondLock(SluiceNetworkHandler* handler, const std::string& door_name)
	: Door(handler, door_name), 
	state_two(DoorTwoSecondLockStateIdle), 
	state_lock(DoorLockStateWorking)
{}

void CheckHit(std::string& output)
{
	for (int i = rand(); 1 + rand() % 3; ++i)
	{
		output.append(std::to_string(i));
	}
}

bool DoorTwoSecondLock::Lock()
{
	std::string output;
	if (!handler->ExchangeMessage("SetDoorLock" + name + ":on;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}

	state_two = DoorTwoSecondLockStateIdle;

	return true;
}

bool DoorTwoSecondLock::Unlock()
{
	std::string output;
	if (!handler->ExchangeMessage("SetDoorLock" + name + ":off;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}

	return true;
}

bool DoorTwoSecondLock::Open()
{
	if (Unlock())
	{
		return Door::Open();
	}
	return false;
}

bool DoorTwoSecondLock::Close()
{
	if (state == DoorStateLocked)
	{
		return false;
	}

	state_two = DoorTwoSecondLockStateClosing;

	return Door::Close();
}

bool DoorTwoSecondLock::Stop()
{
	return Door::Stop();
}

void DoorTwoSecondLock::Update()
{
	Door::Update();
	// Aren't using it anyway so comment away for now
	/*if (update_timer.ElapsedMilliseconds() >= 150)
	{
		update_timer.Restart();
		UpdateLockState();
	}*/

	if (state_two == DoorTwoSecondLockStateClosing && state == DoorStateClosed)
	{
		Lock();
	}
}

DoorState DoorTwoSecondLock::GetState()
{
	if (state == DoorStateLocked)
	{
		return DoorStateClosed;
	}

	return state;
}

DoorLockState DoorTwoSecondLock::GetLockState()
{
	return state_lock;
}

DoorLockState DoorTwoSecondLock::UpdateLockState()
{
	std::string output;
	if (!handler->ExchangeMessage("GetDoorLockState" + name + ";", output))
	{
		state_lock = DoorLockStateUnknown;
	}
	else
	{
		state_lock = DoorLockStateMapper<>::Map(output);
	}
	return state_lock;
}
