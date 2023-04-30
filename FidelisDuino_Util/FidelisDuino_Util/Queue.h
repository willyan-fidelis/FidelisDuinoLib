#pragma once


#if defined( ___DEBUG_ON___ )
#include "..\..\FidelisDuino_Timer.h"
#include "..\..\FidelisDuino_EdgeDetection.h"
#else
#include "FidelisDuino_Timer.h"
#include "FidelisDuino_EdgeDetection.h"
#endif


namespace FidelisDuino {
	namespace Queue {
		class Queue {
		

		public:
			struct ControlData {
				int ParMaxQueueSize = 1;
				int StAddPosition = 0;
				int StRemovePosition = 0;
				int StActualQueueSize = 0;
			};
			//Getter (Status)
			int GetMaxQueueSize() { return _controlData.ParMaxQueueSize; }
			int GetAddPosition() { return _controlData.StAddPosition; }
			int GetRemovePosition() { return _controlData.StRemovePosition; }
			int GetActualQueueSize() { return _controlData.StActualQueueSize; }

			void Clear() {
				_controlData.StAddPosition = 0;
				_controlData.StRemovePosition = 0;
				_controlData.StActualQueueSize = 0;
			}
			bool CanRemove()
			{
				if (_controlData.StActualQueueSize > 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			bool Remove() {
				if (_controlData.StActualQueueSize > 0)
				{
					//Atualiza o tamanho da fila:
					_controlData.StActualQueueSize--;
					//Atualiza o ponteiro de inser��o:
					_controlData.StRemovePosition++;
					if (_controlData.StRemovePosition >= _controlData.ParMaxQueueSize)
					{
						_controlData.StRemovePosition = 0;
					}
				}
				else
				{
					//N�o foi possivel remover da fila.
					return false;
				}
			}
			bool CanAdd()
			{
				if (_controlData.StActualQueueSize < _controlData.ParMaxQueueSize)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			bool Add() {
				if (_controlData.StActualQueueSize < _controlData.ParMaxQueueSize)
				{
					//Atualiza o tamanho da fila:
					_controlData.StActualQueueSize++;
					//Atualiza o ponteiro de inser��o:
					_controlData.StAddPosition++;
					if (_controlData.StAddPosition >= _controlData.ParMaxQueueSize)
					{
						_controlData.StAddPosition = 0;
					}
				}
				else
				{
					//N�o foi possivel adicionar a fila.
					return false;
				}
			}

			Queue() {
				_controlData = { 0,0,0,0 };
			}
			void SetSize(int size = 10)
			{
				_controlData = { 0,0,0,0 };
				_controlData.ParMaxQueueSize = size;
			}
			//Restaura fila apartir de dados salvos:
			void SetControlData(ControlData controlData)
			{
				_controlData = controlData;
			}
			ControlData GetControlData()
			{
				return _controlData;
			}
		private:
			ControlData _controlData = { 0,0,0,0 };
		};

		class PlcQueue {
		//Apneas traduzido de https://github.com/willyan-fidelis/PLC-QUEUE/blob/main/EL_QUEUE.scl
		//Essa classe n�o foi usada e testada ainda.
		private:
			int ParMaxQueueSize = 0;
		public:
			bool CmdAdd = false;
			bool CmdRemove = false;
			bool CmdResetQueue = false;
			bool StAdding = false;
			bool StRemoving = false;
			bool StQueueFull = false;
			bool StQueueEmpty = 0;
			int StAddPosition = 0;
			int StRemovePosition = 0;
			int StActualQueueSize = 0;

			void Loop(int ParTimeToTrue, int ParTimeToFalse, bool input, int filter = 0) {
				//Filter option --->

				/*Status Fila Cheia : */
				if (StActualQueueSize >= ParMaxQueueSize)
				{
					StQueueFull = true;
				}
				else
				{
					StQueueFull = false;
				}

				/* Status Adicionando a Fila: */
				if(StAdding)
				{
					StAdding = false;
					/*Incrementa o ponteiro de adi��o : */
					if(StAddPosition >= (ParMaxQueueSize - 1))
					{
						StAddPosition = 0;
					}
					else
					{
						StAddPosition = StAddPosition + 1;
					}
					/*Atualiza o tamanhao atual da fila : */
					StActualQueueSize  = StActualQueueSize + 1;
				}

				/* Comando Adicionar a Fila: */
				if(CmdAdd)
				{
					CmdAdd  = false;
					/*Se a fila n�o estiver cheia podemos adionar um novo elemento : */
					if (!StQueueFull)
					{
						StAdding = false;
					}
				}

				/*Status Fila Vazia : */
				if(StActualQueueSize == 0)
				{
					StQueueEmpty = true;
				}
				else
				{
					StQueueEmpty = false;
				}

				/*Status Removendo a Fila : */
				if (StRemoving)
				{
					StRemoving = false;
					/*Incrementa o ponteiro de remo��o : */
					if (StRemovePosition >= (ParMaxQueueSize - 1))
					{
					StRemovePosition = 0;
					}
					else
					{
					StRemovePosition = StRemovePosition + 1;
					}
					/*Atualiza o tamanhao atual da fila : */
					StActualQueueSize = StActualQueueSize - 1;
				}

				/*Comando Remover da Fila : */
				if (CmdRemove)
				{
					CmdRemove  = false;
					/*Se a fila n�o estiver vazia podemos remover um novo elemento : */
					if(!StQueueEmpty)
					{
						StRemoving = true;
					}
				}

				/*Comando Reset Fila : */
				if (CmdResetQueue)
				{
					CmdResetQueue = false;
					StAddPosition = 0;
					StRemovePosition = 0;
					StActualQueueSize = 0;
				}
			}
			//Getter (Status)
			//bool StTrue() { return _StTrue; }
		};
	}
}