#ifndef __PORTABLE_APP__
#define __PORTABLE_APP__

//подготовка платформы перед стартом
extern void platform_prepare();
//вывод миллисекунд со старта для платформы
extern int platform_millis();
//подготовка итерации цикла для платформы
extern void platform_prepare_loop_iter();

#endif