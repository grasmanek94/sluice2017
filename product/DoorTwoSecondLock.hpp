#pragma once
#include <map>
#include "Door.hpp"
#include "Timer.hpp"

enum DoorTwoSecondLockState
{
	DoorTwoSecondLockStateIdle,
	DoorTwoSecondLockStateClosing
};

enum DoorLockState
{
	DoorLockStateWorking,
	DoorLockStateDamaged,
	DoorLockStateUnknown
};

class DoorTwoSecondLock : public Door
{
private:
	DoorTwoSecondLockState state_two;
	DoorLockState state_lock;

	Timer update_timer;
	Timer lock_timer;

	bool Lock();
	bool Unlock();
	
public:
	DoorTwoSecondLock(SluiceNetworkHandler* handler, const std::string& door_name);
	virtual bool Open() override;
	virtual bool Close() override;
	virtual bool Stop() override;
	virtual void Update() override;
	virtual DoorState GetState() override;
	DoorLockState GetLockState();
	DoorLockState UpdateLockState();
};

template <typename T = int>
class DoorLockStateMapper
{
public:
	static DoorLockState Map(const std::string& input)
	{
		static bool initialised = false;
		static std::map<std::string, DoorLockState> mapper;
		if (!initialised)
		{
			mapper["lockWorking;"] = DoorLockStateWorking;
			mapper["lockDamaged;"] = DoorLockStateDamaged;
		}

		std::map<std::string, DoorLockState>::iterator found = mapper.find(input);
		if (found == mapper.end())
		{
			return DoorLockStateUnknown;
		}
		return found->second;
	}
};