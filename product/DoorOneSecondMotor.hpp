#pragma once
#include "Door.hpp"
#include "Timer.hpp"

class DoorOneSecondMotor : public Door
{
private:
	Timer timer;
public:
	DoorOneSecondMotor(SluiceNetworkHandler* handler, const std::string& door_name);
	virtual bool Open() override;
	virtual bool Close() override;
	virtual bool Stop() override;
	virtual void Update() override;
};