/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *
 Code by Simon Monk
 http://www.simonmonk.org
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// For Arduino 1.0 and earlier
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Event.h"

Event::Event(void)
{
	eventType = EVENT_NONE;
}

void Event::update(void)
{
    unsigned long now = millis();
    update(now,255);
}

void Event::update(unsigned long now,byte callbackID)
{
	if (now - lastEventTime >= period)
	{
        int eTemp = eventType;
        lastEventTime = now;
		count++;
        if (repeatCount > -1 && count >= repeatCount)
        {
            eventType = EVENT_NONE;
        }
		switch (eTemp)
		{
			case EVENT_EVERY:
				(*callback)(callbackID);
				break;

			case EVENT_OSCILLATE:
				pinState = ! pinState;
				digitalWrite(pin, pinState);
				break;
		}
	}
}
