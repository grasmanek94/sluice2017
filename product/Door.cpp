#include "Door.hpp"

Door::Door(SluiceNetworkHandler* handler, const std::string& door_name)
	: Door(handler, door_name, new DoorEngine(handler, door_name), new DoorLock(handler, door_name))
{}

Door::Door(SluiceNetworkHandler * handler, const std::string & door_name, DoorEngine * engine)
	: Door(handler, door_name, engine)
{}

Door::Door(SluiceNetworkHandler * handler, const std::string & door_name, DoorLock * lock)
	: Door(handler, door_name, lock)
{}

Door::Door(SluiceNetworkHandler * handler, const std::string & door_name, DoorEngine * engine, DoorLock * lock)
	: handler(handler),
	name(door_name),
	state(DoorStateClosed),
	TrafficLightInside(handler, door_name, TrafficLightPositionInner),
	TrafficLightOutside(handler, door_name, TrafficLightPositionOuter),
	ValveLow(handler, door_name, ValvePositionLow),
	ValveMid(handler, door_name, ValvePositionMid),
	ValveHigh(handler, door_name, ValvePositionHigh),
	engine(engine),
	lock(lock)
{
	if (handler == NULL || engine == NULL || lock == NULL)
	{
		throw std::invalid_argument("handler, engine or lock == nullptr");
	}
}

Door::~Door()
{
	delete engine;
	engine = NULL;

	delete lock;
	lock = NULL;
}

DoorState Door::GetState()
{
	if (engine->GetState() == DoorEngineStateDamaged)
	{
		state = DoorStateMotorDamage;
	}
	return state;
}

bool Door::Open()
{
	return false;
}

bool Door::Close()
{
	return false;
}

bool Door::Stop()
{
	return false;
}

void Door::Update()
{
	engine->Update();
	lock->Update();
}
