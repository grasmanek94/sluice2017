#pragma once
#include <string>
#include <map>
#include "SluiceNetworkHandler.hpp"
#include "TrafficLight.hpp"
#include "Valve.hpp"
#include "Timer.hpp"

enum DoorState
{
	DoorStateLocked,
	DoorStateClosed,
	DoorStateOpen,
	DoorStateClosing,
	DoorStateOpening,
	DoorStateStopped,
	DoorStateMotorDamage,
	DoorStateUnknown
};

class Door
{
protected:
	SluiceNetworkHandler* handler;
	std::string name;
	DoorState state;
	Timer state_update;
public:
	Door(SluiceNetworkHandler* handler, const std::string& door_name);
	virtual ~Door();
	TrafficLight TrafficLightInside;
	TrafficLight TrafficLightOutside;
	Valve ValveLow;
	Valve ValveMid;
	Valve ValveHigh;
	virtual bool Open();
	virtual bool Close();
	virtual bool Stop();
	virtual void Update();
	virtual DoorState GetState();
	DoorState UpdateState();
};

template <typename T = int>
class DoorStateMapper
{
public:
	static DoorState Map(const std::string& input)
	{
		static bool initialised = false;
		static std::map<std::string, DoorState> mapper;
		if (!initialised)
		{
			mapper["doorLocked;"] = DoorStateLocked;
			mapper["doorClosed;"] = DoorStateClosed;
			mapper["doorOpen;"] = DoorStateOpen;
			mapper["doorClosing;"] = DoorStateClosing;
			mapper["doorOpening;"] = DoorStateOpening;
			mapper["doorStopped;"] = DoorStateStopped;
			mapper["motorDamage;"] = DoorStateMotorDamage;
		}

		std::map<std::string, DoorState>::iterator found = mapper.find(input);
		if (found == mapper.end())
		{
			return DoorStateUnknown;
		}
		return found->second;
	}
};