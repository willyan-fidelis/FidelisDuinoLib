#pragma once

#if defined( ___DEBUG_ON___ )
#include "..\..\FidelisDuino_EdgeDetection.h"
#else
//nothing here yet
#endif

namespace FidelisDuino {
	namespace VirtualClock{
		class VirtualClock {
		private:
			bool _isSet = false;
			unsigned long _hrs, _min, _sec, _weekDay;
			unsigned long _lastScan = 0;
			unsigned long _actualScan = 0;
			unsigned long _accMillis = 0;
			FidelisDuino::EdgeDetection::EdgeDetection _ChangedToNewDay;//Novo dia detectado.

			unsigned long longDelta(unsigned long& lastScan, unsigned long actualScan)
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

			//Converte uma unidade mais baixa em outra de maior valor. Exemplo: converte milli sec em sec:
			unsigned long ExtractUpperUnit(unsigned long lowUnitValue, unsigned long UnitsToChangeToUp, unsigned long& remainde) {
				if (lowUnitValue >= UnitsToChangeToUp)
				{
					unsigned long _ToAdd = (int)lowUnitValue / UnitsToChangeToUp;
					remainde = lowUnitValue - (_ToAdd * UnitsToChangeToUp);
					return _ToAdd;
				}
				else {
					remainde = lowUnitValue;
					return 0;
				}
			}
		public:
			VirtualClock() {
				_hrs = 0;
				_min = 0;
				_sec = 0;
				_weekDay = 0;
			}
			void SetTime(unsigned long hrs, unsigned long min, unsigned long sec, unsigned long weekDay) {
				_isSet = true;
				_hrs = hrs;
				_min = min;
				_sec = sec;
				_weekDay = weekDay;
			}
			bool IsSet() {
				return true;
			}
			void Loop() {

			}
			void GetTime(unsigned long& hrs, unsigned long& min, unsigned long& sec, unsigned long& weekday) {
				hrs = _hrs;
				min = _min;
				sec = _sec;
				weekday = _weekDay;
			}

			bool ChangedToNewDay() {
				_ChangedToNewDay.Loop(_hrs == 0);
				return _ChangedToNewDay.OnDetection();
			}
			void Update() {
				_actualScan = millis();
				unsigned long delta = longDelta(_lastScan, _actualScan);

				_accMillis = _accMillis + delta;
				
				unsigned long _UpperUnits;
				//_accMillis = 127007;

				//Milli seconds to seconds:
				_UpperUnits = ExtractUpperUnit(_accMillis, 1000, _accMillis);
				if (_UpperUnits == 0) { return; }
				_sec = _sec + _UpperUnits;

				//Seconds to minutes:
				_UpperUnits = ExtractUpperUnit(_sec, 60, _sec);
				if (_UpperUnits == 0) { return; }
				_min = _min + _UpperUnits;

				//Minutes to hours:
				_UpperUnits = ExtractUpperUnit(_min, 60, _min);
				if (_UpperUnits == 0) { return; }
				_hrs = _hrs + _UpperUnits;


				//Hours to week day:
				_UpperUnits = ExtractUpperUnit(_hrs, 24, _hrs);
				if (_UpperUnits == 0) { return; }
				_weekDay = _weekDay + _UpperUnits;

				//Week day to limbo...:
				//_UpperUnits = ExtractUpperUnit(_weekDay, 6, _weekDay);
				//if (_UpperUnits == 0) { return; }
				//limbo = limbo + _UpperUnits;

				if (_weekDay > 6)
				{
					_weekDay = 0;
				}

				//ExtractUpperUnit(_accMillis, 1000, _accMillis);
			}
		};

		//Classe que usa a'VirtualClock' para calcular a hora e adiciona suporte a data
		class VirtualDateTime {
		private:
			#pragma region HelpperToGenerateTheDate
			//From chat gpt - Gerado apartir do chat gpt, considerando os proximos 20 anos a partir de 2023:
			struct MonthYear {
				int year;
				int lastDaysOfMonth[12];
			};
			bool isLeapYear(int year) {
				return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
			}

			MonthYear years[20];
			int lastDayOfMonth(int month, int year) {
				int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
				if (month == 2 && isLeapYear(year)) {
					return 29;
				}
				else {
					return daysInMonth[month - 1];
				}
			}
			void Fill() {
				// preenche a estrutura para os próximos 20 anos
				for (int i = 0; i < 20; i++) {
					years[i].year = 2023 + i;
					for (int j = 0; j < 12; j++) {
						if (j == 1 && isLeapYear(years[i].year)) {
							years[i].lastDaysOfMonth[j] = 29;
						}
						else {
							years[i].lastDaysOfMonth[j] = lastDayOfMonth(j + 1, years[i].year);
						}
					}
				}

				// imprime os valores na porta serial para conferência
				for (int i = 0; i < 20; i++) {
					Serial.print(years[i].year);
					Serial.print(": ");
					for (int j = 0; j < 12; j++) {
						Serial.print(years[i].lastDaysOfMonth[j]);
						Serial.print(" ");
					}
					//Serial.println();
				}
			}

			//Formula que calcula o dia da semana baseado na data(tbem utilizado o chat gpt):

			int zeller(int year, int month, int day) {
				if (month < 3) {
					month += 12;
					year--;
				}
				int C = year / 100;
				int K = year % 100;
				int f = day + ((13 * (month + 1)) / 5) + K + (K / 4) + (C / 4) - (2 * C);
				return f % 7;
			}

			String zeller_name_friendly(int year, int month, int day)
			{
				switch (zeller(year,month,day)) {
				case 1:
					return "Domingo";//Serial.println("Domingo");
					break;
				case 2:
					return "Segunda-feira";//Serial.println("Segunda-feira");
					break;
				case 3:
					return "Terca-feira";//Serial.println("Terça-feira");
					break;
				case 4:
					return "Quarta-feira";//Serial.println("Quarta-feira");
					break;
				case 5:
					return "Quinta-feira";//Serial.println("Quinta-feira");
					break;
				case 6:
					return "Sexta-feira";//Serial.println("Sexta-feira");
					break;
				case 0:
					return "Sabado";//Serial.println("Sábado");
					break;
				}

				return "Domingo";//
			}
			#pragma endregion
			VirtualClock clock;
			unsigned long _year, _month, _day;
		public:
			VirtualDateTime() {
				_year = 2023;
				_month = 4;
				_day = 1;
				clock.SetTime(0, 0, 0, 0);
			}
			void SetDateTime(unsigned long hrs, unsigned long min, unsigned long sec, unsigned long year, unsigned long month, unsigned long day) {

				clock.SetTime(hrs, min, sec, zeller(year,month,day));
				_year = year;
				_month = month;
				_day = day;
			}
			void GetTime(unsigned long& hrs, unsigned long& min, unsigned long& sec, unsigned long& weekday, unsigned long& year, unsigned long& month, unsigned long& day) {
				clock.GetTime(hrs, min, sec, weekday);
				year = _year;
				month = _month;
				day = _day;
				//Forcamos pegar o dia sa semana conforme a data, pois é garantido realizando o calculo:
				weekday = zeller(year, month, day);
			}
			String GetWeekDayName()
			{
				return zeller_name_friendly(_year, _month, _day);
			}
			void Update() {
				clock.Update();

				//Verificamos se trocamos para o novo dia, para atualizar a data conforme uma base de dados local:
				if (clock.ChangedToNewDay())
				{
					Fill();
					for (size_t i = 0; i < 20; i++)
					{
						if (years[i].year == _year)
						{
							if (_day >= years[i].lastDaysOfMonth[_month-1])
							{
								//Se entramos aqui é pq estamos no ultimo dia do mes:
								_day = 1;
								_month++;
								//Verificamos se finalizamos o ano:
								if (_month > 12)
								{
									_month = 1;
									_year++;
								}
							}
							else
							{
								_day++;
								_month++;
								//Verificamos se finalizamos o ano:
								if (_month > 12)
								{
									_month = 1;
									_year++;
								}
							}
							break;
						}
					}
				}
			}
		};
	}
}