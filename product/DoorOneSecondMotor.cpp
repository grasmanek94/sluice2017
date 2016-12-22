#include "DoorOneSecondMotor.hpp"

DoorOneSecondMotor::DoorOneSecondMotor(SluiceNetworkHandler* handler, const std::string& door_name)
	: Door(handler, door_name)
{}

bool DoorOneSecondMotor::Open()
{
	timer.Restart();
	return Door::Close();
}

bool DoorOneSecondMotor::Close()
{
	timer.Restart();
	return Door::Close();
}

bool DoorOneSecondMotor::Stop()
{
	return Door::Stop();
}

void DoorOneSecondMotor::Update()
{
	Door::Update();

	if ((state == DoorStateOpening || state == DoorStateClosing) && timer.ElapsedMilliseconds() > 800)
	{
		state == DoorStateOpening ?
			Open() :
			Close();
	}
}
