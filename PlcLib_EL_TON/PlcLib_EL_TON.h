/*
Date: 2025-05-02
Title: EL_TON
Namespace: PlcLib::EL_TON::EL_TON
Autor: Willyan Sergio Fidelis
Type file: Header
--------------------------------------------Remarks --------------------------------------------
This namespace have classes that help to handle with edge, like a button click and so on.
--------------------------------------------Remarks --------------------------------------------
*/

#pragma once


#if defined( ___DEBUG_ON___ )
#include "..\..\FidelisDuinoLib\FidelisDuino_EmulateArduinoCore\FidelisDuino_EmulateArduinoCore\FidelisDuino_EmulateArduinoCore.h"
#include "..\PlcLib_SSW_PLC_SCAN.h"
#else
#include "Arduino.h"
#endif


namespace PlcLib {
	namespace EL_TON {
		struct EL_TON_INSTANCE {
			unsigned long PT;
			unsigned long ET;
			bool IN;
			bool Q;
		};
		class EL_TON
		{
		public:
			EL_TON_INSTANCE Instance;
			void Constructor(EL_TON_INSTANCE& _Instance) {
				Instance = _Instance;
			}
			void Loop(bool IN, unsigned long PT)
			{
				
				Instance.IN = IN;
				Instance.PT = PT;

				if (Instance.IN)
				{
					if (Instance.ET >= Instance.PT)
					{
						Instance.Q = true;
					}
					else
					{
						Instance.Q = false;
						Instance.ET = Instance.ET + PlcLib::SSW_PLC_SCAN::SSW_PLC_SCAN::SSW_PLC_SCAN_DB_Actual;
					}
				}
				else
				{
					Instance.Q = false;
					Instance.ET = 0;
				}
				
			}
		};
        
	}
}