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
	namespace EL_TOF {
		struct EL_TOF_INSTANCE {
			unsigned long PT;
			unsigned long ET;
			bool IN;
			bool Q;
			bool _STARTED;
		};
		class EL_TOF
		{
		public:
			EL_TOF_INSTANCE* Instance;//Ponteiro(*) ao invez de referencia(&) porque referencia não permite sua copia, gerando probelams!
			void Constructor(EL_TOF_INSTANCE* _Instance) {
				if (_Instance == nullptr) {
					_Instance = new EL_TOF_INSTANCE();
				}
				Instance = _Instance;
			}
			~EL_TOF() {
				if (Instance != nullptr) {
					delete Instance;
				}         // liberação no destrutor
			}
			void Loop(bool IN,unsigned long PT)
			{

				Instance->IN = IN;
				Instance->PT = PT;
				

				if (Instance->IN)
				{
					Instance->Q = true;
					Instance->ET = 0;
					Instance->_STARTED = true;
					
				}
				else
				{
					if (Instance->_STARTED)
					{
						if (Instance->ET >= Instance->PT)
						{
							Instance->Q = false;
							Instance->_STARTED = false;
						}
						else
						{
							Instance->Q = true;
							Instance->ET = Instance->ET + PlcLib::SSW_PLC_SCAN::SSW_PLC_SCAN::SSW_PLC_SCAN_DB_Actual;
						}
					}
				}

			}
		};

	}
}