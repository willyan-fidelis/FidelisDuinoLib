#pragma once

#include "PlcLib_EL_TON.h"


#if defined( ___DEBUG_ON___ )
#include "..\..\FidelisDuinoLib\FidelisDuino_EmulateArduinoCore\FidelisDuino_EmulateArduinoCore\FidelisDuino_EmulateArduinoCore.h"
#else
#include "Arduino.h"
#endif

bool test = false;
PlcLib::EL_TON::EL_TON FirstTON;
PlcLib::EL_TON::EL_TON_INSTANCE* ton_instance;

void setup() {
	//ton_instance = new PlcLib::EL_TON::EL_TON_INSTANCE();//n�o � necessario, aloca��o ja � feita dentro da fun��o Constructor
	FirstTON.Constructor(ton_instance);
}

void loop() {
	//Call the SSW_PLC_SCAN loop:
	PlcLib::SSW_PLC_SCAN::SSW_PLC_SCAN::Loop();
	//Call the TON loop:
	FirstTON.Loop(test, 5000);

	if (FirstTON.Instance->Q)
	{
		Serial.println("After signal time-out!");
	}
}