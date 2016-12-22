#include "DoorEngine.hpp"

DoorEngine::DoorEngine(SluiceNetworkHandler * handler, const std::string & door_name)
	: handler(handler), door_name(door_name)
{
}

bool DoorEngine::On()
{
	return false;
}

bool DoorEngine::Off()
{
	return false;
}

void DoorEngine::Update()
{
}

DoorEngineState DoorEngine::GetState()
{
	return DoorEngineState();
}
