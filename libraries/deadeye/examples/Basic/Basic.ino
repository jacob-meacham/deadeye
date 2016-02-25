#include <Deadeye.h>

// Make a new target
Target target(12,4);
void setup() {
  // Activate the target, which will turn on the LED
  target.activate();
}

void loop() {  
  bool wasHit = target.processHit(); // Was the target hit?
  if (wasHit) {
    // Deactivate the target and delay for 3 seconds, before allowing for another hit.
    target.deactivate();
    delay(3000);
  }
}
