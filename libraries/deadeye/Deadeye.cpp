#include "Arduino.h"
#include "Deadeye.h"
////////////////////////////////////////////////////////////////////
Target::Target(int ledPin, int buttonPin)
{
	this->ledPin = ledPin;
	this->buttonPin = buttonPin;
	active = false;
	lastButtonState = LOW;
	lastHighTime = 0;

	pinMode(this->ledPin, OUTPUT);
	pinMode(this->buttonPin, INPUT);
}
////////////////////////////////////////////////////////////////////
bool Target::processHit()
{
	if (!active) return false;

	int state = digitalRead(buttonPin);
	if (state == HIGH) {
		lastHighTime = millis(); // Some debounce on resetting:
		
		// Just went high, and we were at low, so we'll always signal:
		if (lastButtonState == LOW) {
			lastButtonState = HIGH;
			return true;
		}
	}

	if ((millis() - lastHighTime) > debounceDelay) {
		// Longer than our debounce, so we want to reset
		lastButtonState = LOW;
	}

	return false;
}
////////////////////////////////////////////////////////////////////
void Target::activate()
{
	active = true;
	digitalWrite(ledPin, HIGH);
}
////////////////////////////////////////////////////////////////////
void Target::deactivate()
{
	active = false;
	digitalWrite(ledPin, LOW);
}
////////////////////////////////////////////////////////////////////
bool Target::isActive() const
{
	return active;
}
////////////////////////////////////////////////////////////////////
void Target::fade(int fade) {
	analogWrite(ledPin, fade);
}
////////////////////////////////////////////////////////////////////