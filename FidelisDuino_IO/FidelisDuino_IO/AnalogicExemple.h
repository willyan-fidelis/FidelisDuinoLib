#pragma once

#include "FidelisDuino_Output.h"


#if defined( ___DEBUG_ON___ )
#include "..\..\FidelisDuino_EdgeDetection\FidelisDuino_EdgeDetection\FidelisDuino_EdgeDetection.h"
#else
#include "FidelisDuino_EdgeDetection.h"
#endif

FidelisDuino::IO::Output::AnalogicOutput analog;

void setup() {

}

void loop()
{
	analog.Loop(0, 100, 0, 1023, [](int Target, int Out)->void {
		Serial.print("Changed to: ");
		Serial.println(Target);
	});

	if (Serial.available()) {
		if (Serial.readString() == "100")
		{
			Serial.println("100!");
			analog.Write(100);
		}
		if (Serial.readString() == "5")
		{
			Serial.println("5!");
			analog.Write(5);
		}
		if (Serial.readString() == "0")
		{
			Serial.println("0!");
			analog.Write(0);
		}
		if (Serial.readString() == "fade-on")
		{
			Serial.println("fade-on!");
			analog.FadeOn(12, 10);
		}
		if (Serial.readString() == "fade-off")
		{
			Serial.println("fade-off!");
			analog.FadeOff(0,10);
		}
		if (Serial.readString() == "toggle")
		{
			Serial.println("toggle!");
			analog.ToggleFade(12, 10);
		}
		if (Serial.readString() == "fade-5")
		{
			Serial.println("toggle!");
			analog.Fade(5, 10);
		}
		if (Serial.readString() == "fade-10")
		{
			Serial.println("toggle!");
			analog.Fade(10, 10);
		}
	}
}

