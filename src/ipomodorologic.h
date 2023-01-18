#ifndef __I_POMODORO_LOGIC___
#define __I_POMODORO_LOGIC___

#include "keys.h"
#include "iformatedoutput.h"

//логика обработки pomodoro
class IPomodoroLogic {
public:
   virtual void process(KEYPRESS_EVENT event, int ms_delay, IFormatedOutput* output) = 0;
   virtual ~IPomodoroLogic() {};
};

extern IPomodoroLogic* makeLogic(float worktime_minutes, float sleeptime_minutes);

#endif