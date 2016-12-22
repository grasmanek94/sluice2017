#include "TrafficLight.hpp"

// 7) De verkeerslichten zijn rood of groen.
// De sluiswachter kan middels een video circuit 
// de sluis en de verkeerslichten zien. 
TrafficLight::TrafficLight(SluiceNetworkHandler* handler, const std::string& door_name, TrafficLightPosition position)
	:
	handler(handler), door_name(door_name),
	position(position)
{
	if (door_name == "Left")
	{
		index = std::to_string(1 + (int)position);
	}
	else // Right
	{
		index = std::to_string(4 - (int)position);
	}
}

bool TrafficLight::Off()
{
	std::string output;

	if (!handler->ExchangeMessage("SetTrafficLight" + index + "Red:off;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}

	if (!handler->ExchangeMessage("SetTrafficLight" + index + "Green:off;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}

	return true;
}

bool TrafficLight::Red()
{
	std::string output;

	if (!handler->ExchangeMessage("SetTrafficLight" + index + "Red:on;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}

	if (!handler->ExchangeMessage("SetTrafficLight" + index + "Green:off;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}

	return true;
}

bool TrafficLight::Green()
{
	std::string output;

	if (!handler->ExchangeMessage("SetTrafficLight" + index + "Red:off;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}

	if (!handler->ExchangeMessage("SetTrafficLight" + index + "Green:on;", output))
	{
		return false;
	}
	if (!handler->AckOk(output))
	{
		return false;
	}

	return true;
}

TrafficLightState TrafficLight::GetState() const
{
	return state;
}

TrafficLightState TrafficLight::UpdateState()
{
	std::string output;

	if (!handler->ExchangeMessage("GetTrafficLight" + index + "Red;", output))
	{
		red = TrafficLightStateInternalUnknown;
	}
	else
	{
		red = TrafficLightStateMapper<>::Map(output);
	}

	if (!handler->ExchangeMessage("GetTrafficLight" + index + "Green;", output))
	{
		green = TrafficLightStateInternalUnknown;
	}
	else
	{
		green = TrafficLightStateMapper<>::Map(output);
	}

	if (red == TrafficLightStateInternalOff)
	{
		if (green == TrafficLightStateInternalOff)
		{
			state = TrafficLightStateOff;
		}
		else if (green == TrafficLightStateInternalOn)
		{
			state = TrafficLightStateGreen;
		}
		else
		{
			state = TrafficLightStateUnknown;
		}
	}
	else if (red == TrafficLightStateInternalOn)
	{
		if (green == TrafficLightStateInternalOff)
		{
			state = TrafficLightStateRed;
		}
		else if (green == TrafficLightStateInternalOn)
		{
			state = TrafficLightStateAllOn;
		}
		else
		{
			state = TrafficLightStateUnknown;
		}
	}
	else
	{
		state = TrafficLightStateUnknown;
	}

	return state;
}
