#pragma once

#include "FidelisDuino_VirtualClock.h"

FidelisDuino::VirtualClock::VirtualDateTime clk;

void setup() {
	clk.SetDateTime(23, 59, 45,2023,12,31);
}

void loop() {
	clk.Update();

	unsigned long _hrs, _min, _sec, _weekDay, _year,_month, _day;
	clk.GetTime(_hrs, _min, _sec, _weekDay, _year, _month, _day);
	Serial.println("Time is: ");
	Serial.print(_hrs);Serial.print(":");Serial.print(_min);Serial.print(" - ");Serial.println(_sec);
	Serial.println("Date is: ");
	Serial.print(_year);Serial.print("-");Serial.print(_month);Serial.print("-");Serial.println(_day);
	Serial.print(" week: ");Serial.println(clk.GetWeekDayName());
}