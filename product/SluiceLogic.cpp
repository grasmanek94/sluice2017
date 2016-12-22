#include "SluiceLogic.hpp"

void SluiceLogic::UpdateIdle()
{
}

void SluiceLogic::UpdateSchutten()
{
	switch (state_schutten)
	{
		// 2) De geopende deuren van sluis, 
		// daar waar de waterstand aan beide 
		// zijden gelijk is, worden dan gesloten.
		case SluiceLogicStateSchuttenInternalLowerClosing:
		case SluiceLogicStateSchuttenInternalHigherClosing:
		{
			Door* schutten_to_close = 
				state_schutten == SluiceLogicStateSchuttenInternalLowerClosing ?
				sluice->DoorHigh() : sluice->DoorLow();

			DoorState door_state = schutten_to_close->GetState();
			if (door_state == DoorStateClosed)
			{
				state_schutten = 
					state_schutten == SluiceLogicStateSchuttenInternalLowerClosing ? 
					SluiceLogicStateSchuttenInternalLower : SluiceLogicStateSchuttenInternalHigher;
			}
			else if (door_state != DoorStateClosing)
			{
				// Resume from alarm
				schutten_to_close->Close();
			}
		}
		break;

		// 3) Kwamen de boten van de hoogwaterkant, 
		// dan worden kleppen in de laagwaterdeuren 
		// open gezet zodat het water in de sluis zakt 
		// tot het laagwaterniveau. Vervolgens worden 
		// de deuren aan laagwaterzijde geopend.
		// 
		// 10) Moet het water in de sluis zakken, 
		// dan wordt aan de laagwaterkant de onderste 
		// klep opengezet. 
		case SluiceLogicStateSchuttenInternalLower:
		{
			Door* valve_door = sluice->DoorLow();
			WaterLevel level = sluice->GetWaterLevel();
			if (level != WaterLevelLow)
			{
				if (valve_door->ValveLow.GetState() != ValveStateOpen)
				{
					valve_door->ValveLow.Open();
				}
			}
			else
			{
				valve_door->ValveLow.Close();
				valve_door->Open();
				state_schutten = SluiceLogicStateSchuttenInternalLowerOpening;
			}
		}
		break;

		// 4) Kwamen de boten van de laagwaterkant,
		// dan worden de kleppen in de hoogwaterdeuren 
		// opengezet zodat het water in de sluis 
		// stijgt tot het hoogwater niveau. 
		// 
		// 9) Om het waterniveau te regelen zijn 
		// drie rijen kleppen in de deuren aangebracht. 
		// De onderste rij blijft altijd onderwater. 
		// Als het water in de sluis moet stijgen wordt, 
		// aan de hoogwaterkant, eerst de onderste rij opengezet, 
		// als de tweede rij onder water is wordt ook deze opengezet 
		// en evenzo de derde als die onder water staat
		case SluiceLogicStateSchuttenInternalHigher:
		{
			Door* valve_door = sluice->DoorHigh();
			WaterLevel level = sluice->GetWaterLevel();
			if (level != WaterLevelHigh)
			{
				switch (level)
				{
				case WaterLevelLow:
					if (valve_door->ValveLow.GetState() != ValveStateOpen)
					{
						valve_door->ValveLow.Open();
					}
					break;

				case WaterLevelBelowValve2:
					if (valve_door->ValveLow.GetState() != ValveStateOpen)
					{
						valve_door->ValveLow.Open();
					}
					if (valve_door->ValveMid.GetState() != ValveStateOpen)
					{
						valve_door->ValveMid.Open();
					}
					break;

				case WaterLevelAboveValve2:
					if (valve_door->ValveLow.GetState() != ValveStateOpen)
					{
						valve_door->ValveLow.Open();
					}
					if (valve_door->ValveMid.GetState() != ValveStateOpen)
					{
						valve_door->ValveMid.Open();
					}
					if (valve_door->ValveHigh.GetState() != ValveStateOpen)
					{
						valve_door->ValveHigh.Open();
					}
					break;

				case WaterLevelAboveValve3:
				case WaterLevelHigh:
					break;
				}
			}
			else
			{
				valve_door->ValveLow.Close();
				valve_door->ValveMid.Close();
				valve_door->ValveHigh.Close();
				valve_door->Open();
				state_schutten = SluiceLogicStateSchuttenInternalHigherOpening;
			}
		}
		break;

		case SluiceLogicStateSchuttenInternalLowerOpening:
		case SluiceLogicStateSchuttenInternalHigherOpening:
		{
			Door* schutten_to_open = 
				state_schutten == SluiceLogicStateSchuttenInternalLowerOpening ?
				sluice->DoorLow() : sluice->DoorHigh();

			DoorState door_state = schutten_to_open->GetState();
			if (door_state == DoorStateOpen)
			{
				state_schutten = SluiceLogicStateSchuttenInternalDone;
			}
			else if (door_state != DoorStateOpening)
			{
				schutten_to_open->Open();
			}
		}
		break;

		case SluiceLogicStateSchuttenInternalDone:
		{
			// Do any cleanups here
			state_schutten = SluiceLogicStateSchuttenInternalIdle;
			state_current = SluiceLogicStateIdle;
			// and then exit
		}
		break;
	}
}

void SluiceLogic::UpdateVrijgevenInvaren()
{
}

void SluiceLogic::UpdateVrijgevenUitvaren()
{
}

void SluiceLogic::UpdateAlarm()
{
}

void SluiceLogic::UpdateHerstel()
{
}

SluiceLogic::SluiceLogic(int sluice_nummer)
	: sluice_nummer(sluice_nummer),
	handler(new SluiceNetworkHandler(sluice_nummer)),
	sluice(new Sluice(handler, sluice_nummer)),
	state_current(SluiceLogicStateIdle),
	state_before_alarm(SluiceLogicStateIdle)
{ }

SluiceLogic::~SluiceLogic()
{
	delete sluice;
	sluice = NULL;

	delete handler;
	handler = NULL;
}

// 1) De sluiswachter beslist of de sluis geschut wordt, 
// hij heeft hiervoor per sluis een knop �start�.
bool SluiceLogic::Schutten()
{
	if (state_current != SluiceLogicStateIdle)
	{
		return false;
	}

	// 2) De geopende deuren van sluis, 
	// daar waar de waterstand aan beide zijden gelijk is, 
	// worden dan gesloten.
	Door* schutten_to_close = NULL;
	WaterLevel level = sluice->GetWaterLevel();

	if (level == WaterLevelHigh)
	{
		schutten_to_close = sluice->DoorHigh();
		state_schutten = SluiceLogicStateSchuttenInternalLowerClosing;
	}
	else if (level == WaterLevelLow)
	{
		schutten_to_close = sluice->DoorLow();
		state_schutten = SluiceLogicStateSchuttenInternalHigherClosing;
	}
	else
	{
		return false;
	}

	state_current = SluiceLogicStateSchutten;
	
	if (schutten_to_close->GetState() == DoorStateOpen)
	{
		schutten_to_close->Close();
	}

	return true;
}

// 6) Evenzo staat er aan de ingang van de 
// sluis een verkeerslicht. Boten mogen de 
// sluis pas invaren als de  sluiswachter de 
// sluis hiervoor heeft vrijgegeven en de 
// deuren helemaal geopend zijn. De sluiswachter 
// heeft hiervoor per sluis een knop �vrijgeven voor invaren�. 
bool SluiceLogic::VrijgevenInvaren()
{
	return false;
}

// 5) Om beschadigingen aan de deuren te voorkomen 
// staan bij de sluis verkeerslichten. 
// De boten mogen pas uitvaren als dit verkeerslicht 
// op groen staat. Dit wordt pas op groen gezet 
// als de deuren zeker helemaal geopend zijn 
// en de sluiswachter de sluis heeft vrijgegeven voor uitvaren. 
bool SluiceLogic::VrijgevenUitvaren()
{
	return false;
}

// 11) In een noodsituatie, bv als er iemand in het water is gevallen, 
// kan de sluiswachter ingrijpen door op een knop �alarm� te drukken. 
// Zijn de deuren aan beide zijden gesloten dan worden direct (eventueel) 
// geopende kleppen in de deuren dichtgemaakt om het zakkende of stijgende waterpeil 
// te stabiliseren. Als deuren aan het openen of aan het sluiten zijn wordt deze 
// beweging onmiddellijk gestopt.
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
	switch (state_current)
	{
	case SluiceLogicStateIdle:
		UpdateIdle();
		break;
	case SluiceLogicStateSchutten:
		UpdateSchutten();
		break;
	case SluiceLogicStateVrijgevenInvaren:
		UpdateVrijgevenInvaren();
		break;
	case SluiceLogicStateVrijgevenUitvaren:
		UpdateVrijgevenUitvaren();
		break;
	case SluiceLogicStateAlarm:
		UpdateAlarm();
		break;
	case SluiceLogicStateHerstel:
		UpdateHerstel();
		break;
	}
	sluice->Update();
}
