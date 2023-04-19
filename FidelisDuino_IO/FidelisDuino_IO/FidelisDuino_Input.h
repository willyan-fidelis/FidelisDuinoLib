#pragma once


#if defined( ___DEBUG_ON___ )
#include "..\..\FidelisDuino_Timer.h"
#include "..\..\FidelisDuino_EdgeDetection.h"
#else
#include "FidelisDuino_Timer.h"
#include "FidelisDuino_EdgeDetection.h"
#endif

namespace FidelisDuino {
	namespace IO {
		namespace Input {
			//Can also be called 'Digital Transi��o'. This is the smaller state machine.
			//States: StFalse | StChangeToTrue | StTrue | StChangeToFalse
			//Event: Events are based on 'input' changes.
			class InputStateMachine {
			private:
				FidelisDuino::Timer::TON _ParTimeToTrue;
				FidelisDuino::Timer::TON _ParTimeToFalse;
				bool _StTrue = false;
				bool _StFalse = false;
				bool _StCtTrue = false;
				bool _StCtFalse = false;
				FidelisDuino::EdgeDetection::EdgeDetection _StOnTrueEdge;
				FidelisDuino::EdgeDetection::EdgeDetection _StOnFalseEdge;

				FidelisDuino::EdgeDetection::EdgeDetection _StOnCtTrue;//New!
				FidelisDuino::EdgeDetection::EdgeDetection _StOnCtFalse;//New!

				//Filter option --->
				bool _firstScan = true; //Para garantir que n�o conte e n�o dispare nenhum evento antes da entrada ter sido alterada.
				bool _lastInput = false;
				bool _isChanging = false; //Esta mudando de estado
				bool _ChangeDirection = false; //Dire��o da mudan�a
				bool _Changed = false; //Finalizou a mudan�a
				FidelisDuino::Timer::TON _FilterToChange;
				bool _filterDone = false;
				bool _filterDone_ons = true;
				bool _FilterTrueStateIsValid = false;
				bool _FilterFalseStateIsValid = false;
				//Filter option <---
			public:
				void Loop(int ParTimeToTrue, int ParTimeToFalse, bool input, int filter = 0) {
					//Filter option --->
					if (filter > 0)
					{
						//Primeiro scan:
						if (_firstScan)
						{
							_firstScan = false;
							_lastInput = input;
						}
						//Detectou mudan�a de estado(quando estava parado sem uma outra detec��o de mudan�a em curso):
						if ((_lastInput != input) && !_isChanging)
						{
							_isChanging = true;
							_ChangeDirection = input;
							_filterDone = false;
						}
						//Verifica se o o tempo do filtro foi superado:
						_FilterToChange.Loop(filter);
						if (_isChanging && (_ChangeDirection == input))
						{
							_FilterToChange.Input();
						}
						else {
							_isChanging = false;
						}
						//Por fim atualiza o last state da entrada:
						_lastInput = input;
						//Verifica se o filtro foi superado:
						if(_FilterToChange.GetOutput()){
							_filterDone = true; _isChanging = false;
							_FilterTrueStateIsValid = _ChangeDirection == true ? true : false;
							_FilterFalseStateIsValid = _ChangeDirection == false ? true : false;
						}

						if (_filterDone && !_filterDone_ons)
						{
							//Serial.println("Filter has been checked!");
						}
						_filterDone_ons = _filterDone;
					}
					else {
						_FilterTrueStateIsValid = true;
						_FilterFalseStateIsValid = true;
						_filterDone = true;
					}
					//Filter option <---


					_ParTimeToTrue.Loop(ParTimeToTrue);
					_ParTimeToFalse.Loop(ParTimeToFalse);

					if (input && _FilterTrueStateIsValid && _filterDone)
					{
						_ParTimeToTrue.Input();
					}
					if (!input && _FilterFalseStateIsValid && _filterDone)
					{
						_ParTimeToFalse.Input();
					}

					_StTrue = _ParTimeToTrue.GetOutput();
					_StFalse = _ParTimeToFalse.GetOutput();

					_StCtTrue = !_StTrue && _ParTimeToTrue.GetInput();
					_StCtFalse = !_StFalse && _ParTimeToFalse.GetInput();

					_StOnTrueEdge.Loop(_StTrue);
					_StOnFalseEdge.Loop(_StFalse);

					_StOnCtTrue.Loop(_StCtTrue);//New!
					_StOnCtFalse.Loop(_StCtFalse);//New!
				}
				//Getter (Status)
				bool StTrue() { return _StTrue; }
				//Getter (Status)
				bool StFalse() { return _StFalse; }
				//Getter (Status)
				bool StCtTrue() { return _StCtTrue; }
				//Getter (Status)
				bool StCtFalse() { return _StCtFalse; }
				//Getter (Status)
				bool StOnTrueEdge() { return _StOnTrueEdge.OnDetection(); }
				//Getter (Status)
				bool StOnFalseEdge() { return _StOnFalseEdge.OnDetection(); }

				bool StOnCtTrue() { return _StOnCtTrue.OnDetection(); } //New!
				bool StOnCtFalse() { return _StOnCtFalse.OnDetection(); } //New!
			};
		}
	}
}