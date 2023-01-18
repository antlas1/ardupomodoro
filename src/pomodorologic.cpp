#include "ipomodorologic.h"
#ifndef ARDUINO
#include <memory>
#endif

class PomodoroLogic : public IPomodoroLogic {
public:
    PomodoroLogic(float worktime_minutes, float sleeptime_minutes) :
        state_(POMODORO_NONE_STATE),
        curr_cycle_(0),
        curr_minutes(0.0f),
        work_minutes(worktime_minutes),
        sleep_minutes(sleeptime_minutes)
    {
    }
    void process(KEYPRESS_EVENT event, int ms_delay, IFormatedOutput* output) override
    {
        curr_minutes += static_cast<float>(ms_delay) / (1000.0f * 60.0f);
        bool next_action = (event != KEYPRESS_NONE);
        switch (state_) {
        case POMODORO_NONE_STATE:
            state_ = POMODORO_WAIT_START_WORK;
            output->display(curr_cycle_, state_);
            break;
        case POMODORO_WAIT_START_WORK:
            if (next_action) {
                state_ = POMODORO_PROCESS_WORK;
                curr_minutes = 0.0f;
                output->display(curr_cycle_, state_);
            }
            break;
        case POMODORO_PROCESS_WORK:
            if (curr_minutes >= work_minutes) {
                state_ = POMODORO_WAIT_START_RELAX;
                output->display(curr_cycle_, state_);
            }
            break;
        case POMODORO_WAIT_START_RELAX:
            if (next_action) {
                state_ = POMODORO_PROCESS_RELAX;
                curr_minutes = 0.0f;
                output->display(curr_cycle_, state_);
            }
            break;
        case POMODORO_PROCESS_RELAX:
            if (curr_minutes >= sleep_minutes) {
                state_ = POMODORO_WAIT_START_WORK;
                curr_minutes = 0.0f;
                output->display(curr_cycle_, state_);
                curr_cycle_++;
            }
            break;
        }
    }
private:
    POMODORO_STATE state_;
    uint8_t curr_cycle_;
    float curr_minutes;
    const float work_minutes;
    const float sleep_minutes;
};

#ifndef ARDUINO

IPomodoroLogic* makeLogic(float worktime_minutes, float sleeptime_minutes)
{
    static auto logic = std::make_unique<PomodoroLogic>(worktime_minutes, sleeptime_minutes);
    return logic.get();
}

#else

IPomodoroLogic* makeLogic(float worktime_minutes, float sleeptime_minutes)
{
    return new PomodoroLogic(worktime_minutes, sleeptime_minutes);
}

#endif