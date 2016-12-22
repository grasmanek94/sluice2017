#include "Valve.hpp"

Valve::Valve(SluiceNetworkHandler * handler, const std::string & door_name, ValvePosition position)
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
