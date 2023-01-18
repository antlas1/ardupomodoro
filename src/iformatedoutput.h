#ifndef __I_FORMATED_OUTPUT___
#define __I_FORMATED_OUTPUT___

#include <stdint.h>

enum POMODORO_STATE {
     POMODORO_NONE_STATE, //не начали
     POMODORO_WAIT_START_WORK, //ожидаем начало работы
     POMODORO_PROCESS_WORK, //работаем в помидорке
     POMODORO_WAIT_START_RELAX, //ожидаем начало отдыха
     POMODORO_PROCESS_RELAX, //отдыхаем
};

//Интерфейс форматирования вывода
class IFormatedOutput
{
public:
    virtual void display(uint8_t pomodoroCnt, POMODORO_STATE state) const = 0; //вывести общее число помидор
    virtual ~IFormatedOutput() {};
};

extern IFormatedOutput* makeOutputer();

#endif