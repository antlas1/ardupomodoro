#include "../iformatedoutput.h"
#include "../ikeyboard.h"
#include "../portable_app.h"
#include <memory>
#include <map>
#include <iostream>

static int curr_platform_ms = 0;

IKeyboard* makeKeyboard()
{
    class StdioKeyboard : public IKeyboard {
        KEYPRESS_EVENT update() override {
            return KEYPRESS_SELECT;
        }
    };
    static auto keyb = std::make_unique<StdioKeyboard>();
    return keyb.get();
}

IFormatedOutput* makeOutputer()
{
    class FormatedOutputStdio : public IFormatedOutput {
    public:
        void display(uint8_t pomodoroCnt, POMODORO_STATE state) const override {
            const std::map<POMODORO_STATE, std::string> desc_states = {
                { POMODORO_NONE_STATE, "POMODORO_NONE_STATE" },
                { POMODORO_WAIT_START_WORK,"POMODORO_WAIT_START_WORK" },
                { POMODORO_PROCESS_WORK, "POMODORO_PROCESS_WORK" },
                { POMODORO_WAIT_START_RELAX, "POMODORO_WAIT_START_RELAX" },
                { POMODORO_PROCESS_RELAX, "POMODORO_PROCESS_RELAX" }
            };
            std::cout << curr_platform_ms << " POMODORO: " << (int)pomodoroCnt << " state: " << desc_states.at(state)  << std::endl;
        }
    };
    static auto disp = std::make_unique<FormatedOutputStdio>();
    return disp.get();
}

void platform_prepare()
{
    //нет спец-подготовки платформы
}

void platform_prepare_loop_iter()
{
    //нет спец-подготовки цикла
}

int platform_millis()
{
    static int curr_ms = 0;
    const int DELTA_MS_EXEC = 10;
    const int MAX_RUN_MS = 1900000;
    curr_ms += DELTA_MS_EXEC;
    curr_platform_ms = curr_ms;
    if (curr_ms >= MAX_RUN_MS)
    {
        std::cout << "MAX_RUN_MS STOP "<< curr_ms<<std::endl;
        //TODO: удаление ресурсов
        exit(EXIT_SUCCESS);
    }
    return curr_ms;
}