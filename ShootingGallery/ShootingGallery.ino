#include <Deadeye.h>

const int numTargets = 7;
Target targets[numTargets] = { Target(12,4), Target(13,1), Target(0,1), Target(0,1), Target(0,1), Target(0, 1), Target(0,1) };

String inputString = "";
void setup() {
  Serial.begin(9600);
}

void loop() {  
  bool hits[numTargets];
  for (int i = 0; i < numTargets; i++) {
    hits[i] = targets[i].processHit();
  }
  
  for (int i = 0; i < numTargets; i++) {
    if (hits[i]) {
      Serial.write("T");
      Serial.write(i);
      Serial.write("\n");
    }
  }
}

void serialEvent() {
  while (Serial.available()) {
    char input = (char)Serial.read();
    if (input == '\n') {
      interpretCommand();
      inputString = "";
    } else {
      inputString += input;
    }
  }
}

void interpretCommand() {
  switch (inputString[0]) {
    case 'H':
      handleOnEvent();
      break;
    case 'L':
      handleOffEvent();
      break;
  }
}

void handleOnEvent() {
  for (int i = 1; i < inputString.length(); i++) {
    int targetNumber = inputString[i] - '0';
    targets[targetNumber].activate();    
  }
}

void handleOffEvent() {
  for (int i = 1; i < inputString.length(); i++) {
    int targetNumber = inputString[i] - '0';
    targets[targetNumber].deactivate();
  }
}
