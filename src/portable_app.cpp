#include "app_entry.h"
#include "portable_app.h"
#include "iformatedoutput.h"
#include "ikeyboard.h"
#include "ipomodorologic.h"

IFormatedOutput* output = 0;
IKeyboard* keyboard = 0;
IPomodoroLogic* pomodoro = 0;
int prev_millis = 0;
KEYPRESS_EVENT prev_event = KEYPRESS_NONE;
#define UPDATE_MILLIS_DELTA 1000
//для теста на платформе делать меньше...
#define WORK_TIME_MINUTES 30.0f
#define RELAX_TIME_MINUTES 5.0f

void app_setup()
{
    platform_prepare();
    output = makeOutputer(); 
    keyboard = makeKeyboard();
    pomodoro = makeLogic(WORK_TIME_MINUTES, RELAX_TIME_MINUTES);
}

void app_loop()
{
    platform_prepare_loop_iter();
	KEYPRESS_EVENT evnt = keyboard->update();
    int ms = platform_millis();
    if ( ((evnt!=KEYPRESS_NONE) && (evnt != prev_event)) || 
         ((ms - prev_millis) >= UPDATE_MILLIS_DELTA))
    {
        int delta_ms = ms - prev_millis;
        pomodoro->process(evnt, delta_ms,output);
        prev_event = evnt;
        prev_millis = ms;
    }
}

