#pragma once

#include "PlcLib_EL_TOF.h"


#if defined( ___DEBUG_ON___ )
#include "..\..\FidelisDuinoLib\FidelisDuino_EmulateArduinoCore\FidelisDuino_EmulateArduinoCore\FidelisDuino_EmulateArduinoCore.h"
#else
#include "Arduino.h"
#endif

bool test = false;
PlcLib::EL_TOF::EL_TOF FisrtStepCtrl;
PlcLib::EL_TOF::EL_TOF_INSTANCE* tof_instance;

void setup() {
	//tof_instance = new PlcLib::EL_TOF::EL_TOF_INSTANCE();//não é necessario, alocação ja é feita dentro da função Constructor
	FisrtStepCtrl.Constructor(tof_instance);
}

void loop() {
	//Call the SSW_PLC_SCAN loop:
	PlcLib::SSW_PLC_SCAN::SSW_PLC_SCAN::Loop();
	//Call the TOF loop:
	FisrtStepCtrl.Loop(test,5000);

	if (FisrtStepCtrl.Instance->Q)
	{
		Serial.println("After signal time-out!");
	}
}