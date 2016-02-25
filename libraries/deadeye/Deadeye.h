#pragma once
#include "Arduino.h"

class Target
{
public:
	Target(int ledPin, int buttonPin);
	
	void activate();
	void deactivate();
	bool isActive() const;

	// Fade is an int from 0-255
	void fade(int fade);

	bool processHit();
public:
	bool active;
	int ledPin;
	int buttonPin;
	int lastButtonState;

	long lastHighTime;
	static const long debounceDelay = 50;
};