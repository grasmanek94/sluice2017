#pragma once
#include "DoorEngine.hpp"

class DoorEngineOneSecond : public DoorEngine
{
public:
	DoorEngineOneSecond(SluiceNetworkHandler* handler, const std::string& door_name);
	virtual bool On();
	virtual bool Off();
	virtual void Update();
};