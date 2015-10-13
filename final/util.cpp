#include "util.h"
#include "Arduino.h"
int waitDuration(unsigned int duration)
{
  static unsigned long start = millis();
  static bool newWait = true;

  if (newWait)
  {
    start = millis();
    newWait = false;
  }

  if ((millis() - start) > duration) {
    newWait = true;
    return DONE;
  }
  return NOT_DONE_YET;
}
