#include "Sluice.hpp"

WaterLevel Sluice::UpdateWaterLevel()
{
	std::string output;
	if (!handler->ExchangeMessage("GetWaterLevel;", output))
	{
		water_level = WaterLevelUnknown;
	}
	else
	{
		water_level = WaterLevelMapper<>::Map(output);
	}

	return water_level;
}

// 8) De sluisdeuren worden bediend met een hydraulische installatie.
// Deze installatie mag alleen bekrachtigd worden om de deuren te openen 
// als het water aan beide zijden van de deur op gelijk niveau is.
// Er is een detectie die aanspreekt als het waterniveau aan beide zijden 
// van de deur gelijk is. 
Sluice::Sluice(SluiceNetworkHandler* handler, int sluice_nummer)
	: handler(handler), sluice_nummer(sluice_nummer)
{
	if (handler == NULL)
	{
		throw std::invalid_argument("handler");
	}

	switch (sluice_nummer)
	{
	case 1:
	case 2:
		door_low = new Door(handler, "Left");
		door_high = new Door(handler, "Right");
		break;
	case 3:
		door_low = new DoorTwoSecondLock(handler, "Left");
		door_high = new DoorTwoSecondLock(handler, "Right");
		break;
	case 4:
		door_low = new DoorOneSecondMotor(handler, "Left");
		door_high = new DoorOneSecondMotor(handler, "Right");
		break;
	default:
		throw std::invalid_argument("sluice_nummer");
		break;
	}
}

Sluice::~Sluice()
{
	delete door_low;
	door_low = NULL;

	delete door_high;
	door_high = NULL;
}

WaterLevel Sluice::GetWaterLevel()
{
	return water_level;
}

Door* Sluice::DoorLow()
{
	return door_low;
}

Door* Sluice::DoorHigh()
{
	return door_high;
}

void Sluice::Update()
{
	if (water_level_timer.ElapsedMilliseconds() >= 50)
	{
		water_level_timer.Restart();
		UpdateWaterLevel();
	}
	door_low->Update();
	door_high->Update();
}
