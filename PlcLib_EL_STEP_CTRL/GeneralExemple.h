#pragma once

#include "PlcLib_EL_STEP_CTRL.h"


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

void setup() {
	//_InOutExternalStep = new int();
	//_InOutExternalMicroStep = new int();
	//FisrtStepCtrl.Constructor(_InOutExternalStep, _InOutExternalMicroStep);
	FisrtStepCtrl.Constructor(&InOutExternalStep, &InOutExternalMicroStep);
}

void loop() {
	//Call the SSW_PLC_SCAN loop:
	PlcLib::SSW_PLC_SCAN::SSW_PLC_SCAN::Loop();
	//Call the Step Ctrl loop:
	int Start = true;
	FisrtStepCtrl.Loop(Start);

	if (FisrtStepCtrl.StOnStepChangeEdge)
	{
		Serial.println("Step was changed!");
		if (FisrtStepCtrl.ActualStep == 120)
		{
			FisrtStepCtrl.NextStep = 200;
		}
		if (FisrtStepCtrl.ActualStep == 140)
		{
			//*_InOutExternalStep = 300;
			InOutExternalStep = 300;
		}
	}
}