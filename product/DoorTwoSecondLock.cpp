#include "DoorTwoSecondLock.hpp"

DoorTwoSecondLock::DoorTwoSecondLock(SluiceNetworkHandler* handler, const std::string& door_name)
	: Door(handler, door_name), 
	state_two(DoorTwoSecondLockStateIdle), 
	state_lock(DoorLockStateWorking)
{}

bool DoorTwoSecondLock::Lock()
{
	// NOT HIT?!
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
	// NOT HIT?!
	std::string output;
	if (!handler->ExchangeMessage("SetDoorLock" + name + ":off;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}

	state_two = DoorTwoSecondLockStateOpening;

	return true;
}

bool DoorTwoSecondLock::Open()
{
	// NOT HIT?!
	return Unlock();
}

bool DoorTwoSecondLock::Close()
{
	// NOT HIT?!
	state_two = DoorTwoSecondLockStateClosing;

	return Door::Close();
}

bool DoorTwoSecondLock::Stop()
{
	// NOT HIT?!
	return Door::Stop();
}

void DoorTwoSecondLock::Update()
{
	Door::Update();
	if (update_timer.ElapsedMilliseconds() >= 150)
	{
		update_timer.Restart();
		UpdateLockState();
	}

	if (state_two == DoorTwoSecondLockStateIdle)
	{
		return;
	}


	if (state_two == DoorTwoSecondLockStateOpening && state != DoorStateLocked)
	{
		if (Door::Open())
		{
			state_two = DoorTwoSecondLockStateIdle;
		}
	}

	if (state == DoorStateClosed)
	{
		if (state_two == DoorTwoSecondLockStateClosing)
		{
			lock_timer.Restart();
			state_two = DoorTwoSecondLockStateLocking;
		}
		else if(state_two == DoorTwoSecondLockStateLocking && lock_timer.ElapsedMilliseconds() > 250)
		{
			if (Lock())
			{
				state_two = DoorTwoSecondLockStateIdle;
			}
		}
	}
}

DoorState DoorTwoSecondLock::GetState()
{
	if (state_two == DoorTwoSecondLockStateOpening)
	{
		return DoorStateOpening;
	}
	else if (state_two == DoorTwoSecondLockStateClosing ||
		state_two == DoorTwoSecondLockStateLocking)
	{
		return DoorStateClosing;
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
