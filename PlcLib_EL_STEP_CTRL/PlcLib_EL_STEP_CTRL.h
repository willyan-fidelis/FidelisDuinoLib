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
	namespace EL_STEP_CTRL {
		
		struct MicroStep {
			int NextStep;
			int ActualStep;
			bool StOnStepChangeEdge;
			unsigned long StActualStepRunningTime;
			bool StLastStep;
		};
		
		class EL_STEP_CTRL
		{
		private:
			int* InOutExternalStep;
			int* InOutExternalMicroStep;
		public:
			int NextStep = 0;
			int ActualStep = 0;
			//bool Start = false;
			bool StOnStepChangeEdge = false;
			unsigned long StActualStepRunningTime = 0;
			int StLastStep = 0;
			MicroStep MicroStep;


			//InOutExternalStep* Instance;//Ponteiro(*) ao invez de referencia(&) porque referencia não permite sua copia, gerando probelams!
			void Constructor(int* _InOutExternalStep, int* _InOutExternalMicroStep) {
				if (_InOutExternalStep == nullptr) {
					_InOutExternalStep = new int();
				}
				InOutExternalStep = _InOutExternalStep;
				if (_InOutExternalMicroStep == nullptr) {
					_InOutExternalMicroStep = new int();
				}
				InOutExternalMicroStep = _InOutExternalMicroStep;
			}
			~EL_STEP_CTRL() {
				if (InOutExternalStep != nullptr) {
					delete InOutExternalStep;
				}         // liberação no destrutor
				if (InOutExternalMicroStep != nullptr) {
					delete InOutExternalMicroStep;
				}         // liberação no destrutor
			}
			void Loop(int& Start)
			{
				//To ensure to run this code once we need call it only when start is true(first call)
				if (Start)
				{
					//Micro Step --->
					MicroStep.StOnStepChangeEdge = false;

					if (MicroStep.ActualStep != MicroStep.NextStep)
					{
						//Salvamos o ultimo micro passo executado:
						MicroStep.StLastStep = MicroStep.ActualStep;
						//Trocamos de micro passo:
						MicroStep.ActualStep = MicroStep.NextStep;
						MicroStep.StOnStepChangeEdge = true;
						MicroStep.StActualStepRunningTime = 0;
						//Step externo é uma interface externa(dataview,IHM) para ler e alterar o passo atual:
						*InOutExternalMicroStep = MicroStep.NextStep;

					}
					//Micro Step <---

					//Step externo é uma interface externa(dataview,IHM) para ler e alterar o passo atual:
					if (/*Para acessar o valor da variavel do ponteiro, colocamos o * na frente*/*InOutExternalStep != ActualStep)
					{
						NextStep  = *InOutExternalStep;
					}
					//MicroStep externo é uma interface externa(dataview,IHM) para ler e alterar o passo atual:
					if (/*Para acessar o valor da variavel do ponteiro, colocamos o * na frente*/*InOutExternalMicroStep != MicroStep.ActualStep)
					{
						MicroStep.NextStep = *InOutExternalMicroStep;
					}
					StOnStepChangeEdge = false;
					//Step change detected:
					if (ActualStep != NextStep)
					{
						//Salvamos o ultimo passo executado:
						StLastStep = ActualStep;
						//Trocamos de passo:
						ActualStep = NextStep;
						StOnStepChangeEdge = true;
						MicroStep.StOnStepChangeEdge = true;
						StActualStepRunningTime = 0;
						MicroStep.StActualStepRunningTime = 0;
						//Step externo é uma interface externa(dataview,IHM) para ler e alterar o passo atual:
						*InOutExternalStep = NextStep;
						InOutExternalMicroStep = 0;
						MicroStep.NextStep = 0;
						MicroStep.ActualStep = 0;

						//Must run it again(not tested yet):
						//#Start := TRUE;
					}
					else
					{
						Start = false;
						StActualStepRunningTime = StActualStepRunningTime + PlcLib::SSW_PLC_SCAN::SSW_PLC_SCAN::SSW_PLC_SCAN_DB_Actual;
						MicroStep.StActualStepRunningTime = MicroStep.StActualStepRunningTime + PlcLib::SSW_PLC_SCAN::SSW_PLC_SCAN::SSW_PLC_SCAN_DB_Actual;
					}
				}

				/*
					//Step change detected:
					IF(#ActualStep <> #NextStep) THEN
					#ActualStep : = #NextStep;
				ELSE
					#Start : = FALSE;
				END_IF;
				*/
			}
		};

	}
}