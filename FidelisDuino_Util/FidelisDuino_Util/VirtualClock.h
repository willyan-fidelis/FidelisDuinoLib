#pragma once


#if defined( ___DEBUG_ON___ )
#include "..\..\FidelisDuino_Timer.h"
#include "..\..\FidelisDuino_EdgeDetection.h"
#else
#include "FidelisDuino_Timer.h"
#include "FidelisDuino_EdgeDetection.h"
#endif

namespace FidelisDuino {
	class VirtalClock {


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
				//Atualiza o ponteiro de insersao:
				_controlData.StRemovePosition++;
				if (_controlData.StRemovePosition >= _controlData.ParMaxQueueSize)
				{
					_controlData.StRemovePosition = 0;
				}
				return true;
			}
			else
			{
				//Nao foi possivel remover da fila.
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
				//Atualiza o ponteiro de insersao:
				_controlData.StAddPosition++;
				if (_controlData.StAddPosition >= _controlData.ParMaxQueueSize)
				{
					_controlData.StAddPosition = 0;
				}
				return true;
			}
			else
			{
				//Nao foi possivel adicionar a fila.
				return false;
			}
		}

		VirtalClock() {
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
}