#pragma once

#if defined( ___DEBUG_ON___ )
#include "../../FidelisDuino_EmulateArduinoCore/FidelisDuino_EmulateArduinoCore/FidelisDuino_EmulateArduinoCore.h"
#else
#include "Arduino.h"
#endif

namespace FidelisDuino {
	namespace Util {
		namespace Logger {
			//private:
			bool Private_enabled_fatal = true;
			bool Private_enabled_error = true;
			bool Private_enabled_info = true;
			bool Private_enabled_debug = true;

			//public:

			bool Fatal() { return Private_enabled_fatal; }
			bool Error() { return Private_enabled_error; }
			bool Info() { return Private_enabled_info; }
			bool Debug() { return Private_enabled_debug; }

			bool Fatal(String text)//(const char* text)
			{
				if (!Private_enabled_fatal)
				{
					return false;
				}
				Serial.print("--- FATAL ---> ");
				Serial.print(text);
				return true;
			}
			bool Error(String text)//(const char* text)
			{
				if (!Private_enabled_error)
				{
					return false;
				}
				Serial.print("--- ERROR ---> ");
				Serial.print(text);
				return true;
			}
			bool Info(String text)//(const char* text)
			{
				if (!Private_enabled_info)
				{
					return false;
				}
				Serial.print("--- INFO  ---> ");
				Serial.print(text);
				return true;
			}
			bool Debug(String text)//(const char* text)
			{
				if (!Private_enabled_debug)
				{
					return false;
				}
				Serial.print("--- DEBUG ---> ");
				Serial.print(text);
				return true;
			}
			//ln:
			bool Fatalln(String text)
			{
				if (!Private_enabled_fatal)
				{
					return false;
				}
				Serial.print("--- FATAL ---> ");
				Serial.println(text);
				return true;
			}
			bool Errorln(String text)
			{
				if (!Private_enabled_error)
				{
					return false;
				}
				Serial.print("--- ERROR ---> ");
				Serial.println(text);
				return true;
			}
			bool Infoln(String text)
			{
				if (!Private_enabled_info)
				{
					return false;
				}
				Serial.print("--- INFO  ---> ");
				Serial.println(text);
				return true;
			}
			bool Debugln(String text)
			{
				if (!Private_enabled_debug)
				{
					return false;
				}
				Serial.print("--- DEBUG ---> ");
				Serial.println(text);
				return true;
			}

			//f:
			bool Fatalf(const char* text, ...)
			{
				if (!Private_enabled_fatal)
				{
					return false;
				}
				Serial.print("--- FATAL ---> ");
				Serial.printf(text);
				return true;
			}
			bool Errorf(const char* text, ...)
			{
				if (!Private_enabled_error)
				{
					return false;
				}
				Serial.print("--- ERROR ---> ");
				Serial.printf(text);
				return true;
			}
			bool Infof(const char* text, ...)
			{
				if (!Private_enabled_info)
				{
					return false;
				}
				Serial.print("--- INFO  ---> ");
				Serial.printf(text);
				return true;
			}
			bool Debugf(const char* text, ...)
			{
				if (!Private_enabled_debug)
				{
					return false;
				}
				Serial.print("--- DEBUG ---> ");
				Serial.printf(text);
				return true;
			}
		}
	}
}