#include "Door.hpp"

Door::Door(SluiceNetworkHandler* handler, const std::string& door_name)
	: handler(handler),
	name(door_name),
	state(DoorStateClosed),
	TrafficLightInside(handler, door_name, TrafficLightPositionInner),
	TrafficLightOutside(handler, door_name, TrafficLightPositionOuter),
	ValveLow(handler, door_name, ValvePositionLow),
	ValveMid(handler, door_name, ValvePositionMid),
	ValveHigh(handler, door_name, ValvePositionHigh)
{
	if (handler == NULL)
	{
		throw std::invalid_argument("handler == nullptr");
	}
}

Door::~Door()
{
}

DoorState Door::UpdateState()
{
	std::string output;
	if (!handler->ExchangeMessage("GetDoor" + name + ";", output))
	{
		state = DoorStateUnknown;
	}
	else
	{
		state = DoorStateMapper<>::Map(output);
	}
	return state;
}

DoorState Door::GetState()
{
	return state;
}

bool Door::Open()
{
	std::string output;
	if (!handler->ExchangeMessage("SetDoor" + name + ":open;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}
	return true;
}

bool Door::Close()
{
	std::string output;
	if (!handler->ExchangeMessage("SetDoor" + name + ":close;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}
	return true;
}

bool Door::Stop()
{
	std::string output;
	if (!handler->ExchangeMessage("SetDoor" + name + ":stop;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}
	return true;
}

void Door::Update()
{
	if (state_update.ElapsedMilliseconds() >= 150)
	{
		state_update.Restart();
		UpdateState();
		ValveLow.UpdateState();
		ValveMid.UpdateState();
		ValveHigh.UpdateState();
		//TrafficLightInside.UpdateState();
		//TrafficLightOutside.UpdateState();
	}
}
