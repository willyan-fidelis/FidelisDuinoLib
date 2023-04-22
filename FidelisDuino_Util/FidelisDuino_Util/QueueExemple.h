#pragma once

#include "Queue.h"


#if defined( ___DEBUG_ON___ )
#include "../../FidelisDuino_EmulateArduinoCore.h"
#else
#include "Arduino.h"
#endif

FidelisDuino::Queue::Queue Queue;
String toBeTested = "";
int step = 0;

struct abc {
	bool Active;
	int Button;
	String CameraDataTimeRawResponse;
};
abc ClicksNotSendToCloudQueue[3] = {
  {false,0,"a"},
  {false,0,"b"},
  {false,0,"xxx"},
};

void setup() {
	Queue.SetSize(3);
}

void loop() {
	
	/*
	int size = sizeof(ClicksNotSendToCloudQueue) / sizeof(ClicksNotSendToCloudQueue[0]);
	for (size_t i = 0; i < size; i++)
	{
		abc val = ClicksNotSendToCloudQueue[i];
		if (val.CameraDataTimeRawResponse == "xxx")
		{
			return;
		}
	}
	*/
	if (toBeTested == "can-add" || step == 1)
	{
		if (Queue.CanAdd())
		{
			Serial.print("Yes, it is possible to add on this queue at this moment. Position to be added: ");Serial.println(Queue.GetAddPosition());
		}
		else
		{
			Serial.println("No, it is not possible to add this moment.");
		}
	}
	else if (toBeTested == "can-remove" || step == 2)
	{
		if (Queue.CanRemove())
		{
			Serial.print("Yes, it is possible to remove from this queue at this moment. Position to be removed: ");Serial.println(Queue.GetRemovePosition());
		}
		else
		{
			Serial.println("No, it is not possible to remove this moment.");
		}
	}
	else if (toBeTested == "add" || step == 3)
	{
		if (Queue.CanAdd())
		{
			Serial.print("Before add -> Position to add: ");Serial.println(Queue.GetAddPosition());
			Queue.Add();
			Serial.print("After add -> Position to add: ");Serial.println(Queue.GetAddPosition());

			Serial.print("Queue Size: ");Serial.println(Queue.GetActualQueueSize());
		}
		else
		{
			Serial.println("Sorry it is not possible to add now!");
		}
	}
	else if (toBeTested == "remove" || step == 4)
	{
		if (Queue.CanRemove())
		{
			Serial.print("Before remove -> Position to remove: ");Serial.println(Queue.GetRemovePosition());
			Queue.Remove();
			Serial.print("After remove -> Position to remove: ");Serial.println(Queue.GetRemovePosition());

			Serial.print("Queue Size: ");Serial.println(Queue.GetActualQueueSize());
		}
		else
		{
			Serial.println("Sorry it is not possible to remove now!");
		}
	}
	toBeTested = "";
	step = 0;
}