#pragma once
#include "SluiceNetworkHandler.hpp"
#include "Sluice.hpp"

enum SluiceLogicState
{
	SluiceLogicStateIdle,
	SluiceLogicStateSchutten,
	SluiceLogicStateVrijgevenInvaren,
	SluiceLogicStateVrijgevenUitvaren,
	SluiceLogicStateAlarm,
	SluiceLogicStateHerstel
};

enum SluiceLogicStateSchuttenInternal
{
	SluiceLogicStateSchuttenInternalIdle,
	SluiceLogicStateSchuttenInternalLowerClosing,
	SluiceLogicStateSchuttenInternalHigherClosing,
	SluiceLogicStateSchuttenInternalLower,
	SluiceLogicStateSchuttenInternalHigher,
	SluiceLogicStateSchuttenInternalLowerOpening,
	SluiceLogicStateSchuttenInternalHigherOpening,
	SluiceLogicStateSchuttenInternalDone
};

class SluiceLogic
{
private:
	int sluice_nummer;
	SluiceNetworkHandler* handler;
	Sluice* sluice;
	SluiceLogicState state_current;
	SluiceLogicState state_before_alarm;

	void UpdateIdle();

	void UpdateSchutten();
	SluiceLogicStateSchuttenInternal state_schutten;

	void UpdateVrijgevenInvaren();
	void UpdateVrijgevenUitvaren();
	void UpdateAlarm();
	void UpdateHerstel();

	
public:
	SluiceLogic(int sluice_nummer);
	~SluiceLogic();

	bool Schutten();
	bool VrijgevenInvaren();
	bool VrijgevenUitvaren();
	bool Alarm();
	bool Herstel();
	void Update();
};