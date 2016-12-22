#pragma once
#include "SluiceNetworkHandler.hpp"
#include "Sluice.hpp"

class SluiceLogic
{
private:
	int sluice_nummer;
	SluiceNetworkHandler* handler;
	Sluice* sluice;
public:
	SluiceLogic(int sluice_nummer);
	~SluiceLogic();
	bool Schutten();
	bool Vrijgeven();
	bool Alarm();
	bool Herstel();
	void Update();
};