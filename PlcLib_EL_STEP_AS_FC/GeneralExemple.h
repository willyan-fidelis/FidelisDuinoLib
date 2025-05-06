#pragma once

#include "PlcLib_EL_STEP_AS_FC.h"


#if defined( ___DEBUG_ON___ )
#include "..\..\FidelisDuinoLib\FidelisDuino_EmulateArduinoCore\FidelisDuino_EmulateArduinoCore\FidelisDuino_EmulateArduinoCore.h"
#else
#include "Arduino.h"
#endif

bool test = false;
//int* _InOutExternalStep;
int InOutExternalStep;
//int* _InOutExternalMicroStep;
int InOutExternalMicroStep;
PlcLib::EL_STEP_CTRL::EL_STEP_CTRL FisrtStepCtrl;
PlcLib::EL_STEP_AS_FC::EL_STEP_AS_FC STEP_000;
PlcLib::EL_STEP_AS_FC::EL_STEP_AS_FC STEP_010;
PlcLib::EL_STEP_AS_FC::EL_STEP_AS_FC STEP_020;

PlcLib::EL_STEP_AS_FC::EL_STEP_AS_FC_INSTANCE STEP_000_INSTANCE;
PlcLib::EL_STEP_AS_FC::EL_STEP_AS_FC_INSTANCE STEP_010_INSTANCE;
PlcLib::EL_STEP_AS_FC::EL_STEP_AS_FC_INSTANCE STEP_020_INSTANCE;

void setup() {
	//_InOutExternalStep = new int();
	//_InOutExternalMicroStep = new int();
	//FisrtStepCtrl.Constructor(_InOutExternalStep, _InOutExternalMicroStep);
	FisrtStepCtrl.Constructor(&InOutExternalStep, &InOutExternalMicroStep);
	STEP_000.Constructor(&STEP_000_INSTANCE,&FisrtStepCtrl);
	STEP_010.Constructor(&STEP_010_INSTANCE, &FisrtStepCtrl);
	STEP_020.Constructor(&STEP_020_INSTANCE, &FisrtStepCtrl);
}

void loop() {
	//Call the SSW_PLC_SCAN loop:
	PlcLib::SSW_PLC_SCAN::SSW_PLC_SCAN::Loop();
	//Call the Step Ctrl loop:
	int Start = true;
	while (Start)
	{
		STEP_000.Loop(000);
		STEP_010.Loop(010);
		STEP_020.Loop(020);

		FisrtStepCtrl.Loop(Start);
	}

	//Active edge:
	if (STEP_000_INSTANCE.StOnActiveEdge)
	{
		Serial.println("On step 000 active!");
	}
	if (STEP_010_INSTANCE.StOnActiveEdge)
	{
		Serial.println("On step 010 active!");
	}
	if (STEP_020_INSTANCE.StOnActiveEdge)
	{
		Serial.println("On step 020 active!");
	}
	//Inactive edge:
	if (STEP_000_INSTANCE.StOnInactiveEdge)
	{
		Serial.println("On step 000 inactive edge!");
	}
	if (STEP_010_INSTANCE.StOnInactiveEdge)
	{
		Serial.println("On step 010 inactive edge!");
	}
	if (STEP_020_INSTANCE.StOnInactiveEdge)
	{
		Serial.println("On step 020 inactive edge!");
	}
}