#include "DoorEngineOneSecond.hpp"

DoorEngineOneSecond::DoorEngineOneSecond(SluiceNetworkHandler* handler, const std::string& door_name)
	: DoorEngine(handler, door_name)
{
}

bool DoorEngineOneSecond::On()
{
	return false;
}

bool DoorEngineOneSecond::Off()
{
	return false;
}

void DoorEngineOneSecond::Update()
{
}
