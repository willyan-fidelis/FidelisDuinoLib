#pragma once

#include "FidelisDuino_Timer.h"

FidelisDuino::Timer::Ticker ticker;

FidelisDuino::Timer::Chronometer chrono;

void setup() {

}

void loop()
{
	//Exemplo rapido chrono --->
	chrono.Start();
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	long result = chrono.Stop();
	//Exemplo rapido chrono <---

	ticker.Loop();

	if (Serial.available()) {
		if (Serial.readString() == "attach")
		{
			Serial.println("attach!");
			ticker.attach(3000, []()->void {
				Serial.println("Ticked one more time!");
				}, []()->void {
					Serial.println("Last time!");
				},3);
		}
		if (Serial.readString() == "detach")
		{
			Serial.println("detach!");
			ticker.detach();
		}
	}
}

