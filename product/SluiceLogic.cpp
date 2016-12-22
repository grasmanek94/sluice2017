#include "SluiceLogic.hpp"

SluiceLogic::SluiceLogic(int sluice_nummer)
	: sluice_nummer(sluice_nummer),
	handler(new SluiceNetworkHandler(sluice_nummer)),
	sluice(new Sluice(handler, sluice_nummer))
{
}

SluiceLogic::~SluiceLogic()
{
	delete sluice;
	sluice = NULL;

	delete handler;
	handler = NULL;
}

bool SluiceLogic::Schutten()
{
	return false;
}

bool SluiceLogic::VrijgevenInvaren()
{
	return false;
}

bool SluiceLogic::VrijgevenUitvaren()
{
	return false;
}

bool SluiceLogic::Alarm()
{
	return false;
}

bool SluiceLogic::Herstel()
{
	return false;
}

void SluiceLogic::Update()
{
	sluice->Update();
}
