#include "Valve.hpp"

Valve::Valve(SluiceNetworkHandler* handler, const std::string& door_name, ValvePosition position)
	: handler(handler), door_name(door_name), position(position)
{
}

bool Valve::Open()
{
	std::string output;
	if (!handler->ExchangeMessage("SetDoor" + door_name + "Valve" + std::to_string((int)position) + ":open;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}
	return true;
}

bool Valve::Close()
{
	std::string output;
	if (!handler->ExchangeMessage("SetDoor" + door_name + "Valve" + std::to_string((int)position) + ":close;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}
	return true;
}

ValveState Valve::GetState() const
{
	return state;
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
