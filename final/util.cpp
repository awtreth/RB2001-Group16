#include "util.h"
#include "Arduino.h"

/**
 * @brief Just a wait duration action
 * 
 * @param duration How long to wait
 * @return 1 for done, 0 for not done
 */
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
