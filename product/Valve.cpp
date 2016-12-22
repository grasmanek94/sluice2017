#include "Valve.hpp"

Valve::Valve(SluiceNetworkHandler* handler, const std::string& door_name, ValvePosition position)
	: handler(handler), door_name(door_name), position(position)
{
}

bool Valve::Open()
{
	return false;
}

bool Valve::Close()
{
	return false;
}

ValveState Valve::GetState() const
{
	return ValveState();
}

ValveState Valve::UpdateState()
{
	std::string output;
	if (!handler->ExchangeMessage("GetDoor" + door_name + "Valve" + std::to_string((int)position) + ";", output))
	{
		state = ValveStateUnknown;
	}
	else
	{
		state = ValveStateMapper<>::Map(output);
	}
	return state;
}
