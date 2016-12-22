#pragma once
#include <string>
#include "SluiceNetworkHandler.hpp"
#include "TrafficLight.hpp"
#include "Valve.hpp"
#include "DoorEngine.hpp"
#include "DoorLock.hpp"

enum DoorState
{
	DoorStateLocked,
	DoorStateClosed,
	DoorStateOpen,
	DoorStateClosing,
	DoorStateOpening,
	DoorStateStopped,
	DoorStateMotorDamage
};

class Door
{
protected:
	SluiceNetworkHandler* handler;
	std::string name;
	DoorState state;
private:
	DoorEngine* engine;
	DoorLock* lock;
public:
	Door(SluiceNetworkHandler* handler, const std::string& door_name);
	Door(SluiceNetworkHandler* handler, const std::string& door_name, DoorEngine* engine);
	Door(SluiceNetworkHandler* handler, const std::string& door_name, DoorLock* lock);
	Door(SluiceNetworkHandler* handler, const std::string& door_name, DoorEngine* engine, DoorLock* lock);
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
	DoorState GetState();
};