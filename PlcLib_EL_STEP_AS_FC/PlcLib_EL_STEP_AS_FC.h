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
#include "..\PlcLib_EL_STEP_CTRL\PlcLib_EL_STEP_CTRL.h"
#else
#include "Arduino.h"
#endif


namespace PlcLib {
	namespace EL_STEP_AS_FC {
		//Willyan Fidelis - Engemo Fluid Solution - 05/05/2025
		/*
		Element Digital Output - EL_STEP
		Willyan Fidelis - Engemo Fluid Solution - 02/07/2020

		STEP

		COMMENTS:
		EL_STEP Ã© utilizado sozinho..Crie uma instancia para cada passo
		do processo e forneÃ§a um memoria INT 'passo_atual' para todas as
		instancias da sequencia!
		*/
		struct EL_STEP_AS_FC_INSTANCE {
			bool StActive;
			bool StInactive;
			bool StOnActiveEdge;
			bool StOnInactiveEdge;
			bool StLastActiveStep;
			bool TurnActive;
			bool StOnActive_ONS;
			bool StOnInactive_ONS;
		};

		class EL_STEP_AS_FC
		{
		private:
			EL_STEP_CTRL::EL_STEP_CTRL* StepCtrl;
		public:
			


			EL_STEP_AS_FC_INSTANCE* Instance;//Ponteiro(*) ao invez de referencia(&) porque referencia não permite sua copia, gerando probelams!
			void Constructor(EL_STEP_AS_FC_INSTANCE* _Instance, EL_STEP_CTRL::EL_STEP_CTRL* _StepCtrl) {
				if (_Instance == nullptr) {
					_Instance = new EL_STEP_AS_FC_INSTANCE();
				}
				Instance = _Instance;

				if (_StepCtrl == nullptr) {
					_StepCtrl = new EL_STEP_CTRL::EL_STEP_CTRL();
				}
				StepCtrl = _StepCtrl;
			}
			~EL_STEP_AS_FC() {
				if (Instance != nullptr) {
					delete Instance;
				}         // liberação no destrutor
				if (StepCtrl != nullptr) {
					delete StepCtrl;
				}         // liberação no destrutor
			}
			void Loop(int StepID)
			{
				//Comando para iniciar o passo:
				if (Instance->TurnActive)
				{
					Instance->TurnActive = false;
					StepCtrl->NextStep  = StepID;
				}

				//Passo ativo ou inativo:
				if (StepID == StepCtrl->ActualStep)
				{
					Instance->StActive = true;
					Instance->StInactive = false;
				}
				else
				{
					Instance->StActive = false;
					Instance->StInactive = true;
				}

				//TransiÃ§Ã£o para ativo:
				if (Instance->StActive && !Instance->StOnActive_ONS)
				{
					Instance->StOnActiveEdge = true;
				}
				else
				{
					Instance->StOnActiveEdge = false;
				}
				Instance->StOnActive_ONS = Instance->StActive;

				//TransiÃ§Ã£o para Inativo:
				if (Instance->StInactive && !Instance->StOnInactive_ONS)
				{
					Instance->StOnInactiveEdge = true;
				}
				else
				{
					Instance->StOnInactiveEdge = false;
				}
				Instance->StOnInactive_ONS = Instance->StInactive;

				//Novo! Ultimo passo ativo:
				Instance->StLastActiveStep = StepCtrl->StLastStep = StepID;
			}
		};

	}
}