#include "TrafficLight.hpp"

// 7) De verkeerslichten zijn rood of groen.
// De sluiswachter kan middels een video circuit 
// de sluis en de verkeerslichten zien. 
TrafficLight::TrafficLight(SluiceNetworkHandler * handler, const std::string & door_name, TrafficLightPosition position)
{
}

bool TrafficLight::Off()
{
	return false;
}

bool TrafficLight::Red()
{
	return false;
}

bool TrafficLight::Green()
{
	return false;
}

TrafficLightState TrafficLight::GetState() const
{
	return TrafficLightState();
}
