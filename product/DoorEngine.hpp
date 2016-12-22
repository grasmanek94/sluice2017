#pragma once
#include <string>
#include "SluiceNetworkHandler.hpp"

enum DoorEngineState
{
	DoorEngineStateOn,
	DoorEngineStateOff,
	DoorEngineStateDamaged
};

class DoorEngine
{
protected:
	SluiceNetworkHandler* handler;
	std::string door_name;
	DoorEngineState state;
public:
	DoorEngine(SluiceNetworkHandler* handler, const std::string& door_name);
	virtual bool On();
	virtual bool Off();
	virtual void Update();
	DoorEngineState GetState();
};