#pragma once

#include "FidelisDuino_VirtualClock.h"

FidelisDuino::VirtualClock::VirtualClock clk;
namespace LocalTime {
    namespace DateHelper {
        //From chat gpt:
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
    }
}
void setup() {
	clk.SetTime(23, 59, 45, 6);
}

void loop() {
	clk.Update();

	unsigned long _hrs, _min, _sec, _weekDay;
	clk.GetTime(_hrs, _min, _sec, _weekDay);
	Serial.println("Time is: ");
	Serial.print(_hrs);Serial.print(":");Serial.print(_min);Serial.print(" - ");Serial.print(_sec);
	Serial.print(" week: ");Serial.println(_weekDay);

	if (clk.ChangedToNewDay())
	{
		Serial.println("Transition to new day!");
	}
    LocalTime::DateHelper::Fill();
}