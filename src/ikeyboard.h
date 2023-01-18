#ifndef __I_KEYBOARD___
#define __I_KEYBOARD___

#include <stdint.h>
#include "keys.h"

//Интерфейс форматирования вывода
class IKeyboard
{
public:
    virtual KEYPRESS_EVENT update() = 0; //обновить и проверить на выходе событие нажатия на кнопку
    virtual ~IKeyboard() {};
};

extern IKeyboard* makeKeyboard();

#endif