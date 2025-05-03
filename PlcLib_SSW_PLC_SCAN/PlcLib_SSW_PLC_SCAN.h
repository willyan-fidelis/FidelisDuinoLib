/*
Date: 2025-05-02
Title: EL_TON
Namespace: PlcLib::SSW_PLC_SCAN::SSW_PLC_SCAN
Autor: Willyan Sergio Fidelis
Type file: Header
--------------------------------------------Remarks --------------------------------------------
This namespace have classes that help to handle with edge, like a button click and so on.
--------------------------------------------Remarks --------------------------------------------
*/

#pragma once


#if defined( ___DEBUG_ON___ )
#include "..\..\FidelisDuinoLib\FidelisDuino_EmulateArduinoCore\FidelisDuino_EmulateArduinoCore\FidelisDuino_EmulateArduinoCore.h"
#else
#include "Arduino.h"
#endif


namespace PlcLib {
	namespace SSW_PLC_SCAN {
		class SSW_PLC_SCAN {
		private:
			static unsigned long _lastScan;
			static unsigned long _actualScan;
			static unsigned long longDelta(unsigned long& lastScan, unsigned long actualScan)
			{
				unsigned long delta;

				if (actualScan >= lastScan)//Normal condition:
				{
					delta = actualScan - lastScan;
				}
				else if (actualScan < lastScan) //Overflow condition:
				{
					delta = (4294967295 - lastScan) + lastScan;
				}
				lastScan = actualScan;
				return delta;
			}
		public:
			static unsigned long SSW_PLC_SCAN_DB_Actual;
			static void Loop()
			{
				_actualScan = millis();
				SSW_PLC_SCAN_DB_Actual = longDelta(_lastScan, _actualScan);
			}
		};
		//Definição da variável estática (obrigatória em C++)
		unsigned long SSW_PLC_SCAN::_lastScan = 0;
		unsigned long SSW_PLC_SCAN::_actualScan = 0;
		unsigned long SSW_PLC_SCAN::SSW_PLC_SCAN_DB_Actual = 0;
	}
}