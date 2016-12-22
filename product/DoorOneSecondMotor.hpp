#pragma once
#include "Door.hpp"
#include "Timer.hpp"

class DoorOneSecondMotor : public Door
{
private:
	Timer timer;
public:
	DoorOneSecondMotor(SluiceNetworkHandler* handler, const std::string& door_name);
	virtual bool Open();
	virtual bool Close();
	virtual bool Stop();
	virtual void Update();
};