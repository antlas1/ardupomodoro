#include <Arduino.h>
#include <LcdKeypad.h>
#include <SpinTimer.h>
#include "../iformatedoutput.h"
#include "../ikeyboard.h"
#include "../portable_app.h"

LcdKeypad* myLcdKeypad = 0;

// Implement specific LcdKeypadAdapter in order to allow receiving key press events
class MyLcdKeypadAdapter : public LcdKeypadAdapter, public IKeyboard
{
public:
  void handleKeyChanged(LcdKeypad::Key newKey) override
  {
      if (LcdKeypad::UP_KEY == newKey)
      {
          keypress_ = KEYPRESS_UP;
      }
      else if (LcdKeypad::DOWN_KEY == newKey)
      {
          keypress_ = KEYPRESS_DOWN;
      }
      else if (LcdKeypad::SELECT_KEY == newKey)
      {
          keypress_ = KEYPRESS_SELECT;
      }
      else if (LcdKeypad::LEFT_KEY == newKey)
      {
          keypress_ = KEYPRESS_LEFT;
      }
      else if (LcdKeypad::RIGHT_KEY == newKey)
      {
          keypress_ = KEYPRESS_RIGHT;
      }
  }
  
  KEYPRESS_EVENT update() 
  {
      //если нажата клавиша, то обрабатываем и очищаем сразу же
      if (keypress_ != KEYPRESS_NONE)
      {
          KEYPRESS_EVENT send_event = keypress_;
          keypress_ = KEYPRESS_NONE;
          return send_event;
      }
      return keypress_;
  }
private:
  KEYPRESS_EVENT keypress_;
};

IKeyboard* makeKeyboard()
{
    // Attach the specific LcdKeypadAdapter implementation (dependency injection)
    MyLcdKeypadAdapter* adapter = new MyLcdKeypadAdapter();
    myLcdKeypad->attachAdapter(adapter);
    return adapter;
}

class LcdOutputter : public IFormatedOutput
{
public:
  LcdOutputter(LcdKeypad* lcdKeypad)
  : lcdKeypad_(lcdKeypad)
  { 
  }
  void display(uint8_t pomodoroCnt, POMODORO_STATE state) const
  {
      lcdKeypad_->setCursor(0, 0);   // position the cursor at beginning of the first line
      lcdKeypad_->print("POMODOROS: "); 
      lcdKeypad_->print(pomodoroCnt);
      lcdKeypad_->setCursor(0, 1);            // position the cursor at beginning of the second line
      switch (state)
      {
          case POMODORO_NONE_STATE:       
              lcdKeypad_->print("               "); 
              break;
          case POMODORO_WAIT_START_WORK:  
              lcdKeypad_->print("PRESS FOR WORK "); 
              lcdKeypad_->setBackLightOn(true); 
              break;
          case POMODORO_PROCESS_WORK:     
              lcdKeypad_->print("WORKING...     "); 
              lcdKeypad_->setBackLightOn(false); 
              break;
          case POMODORO_WAIT_START_RELAX: 
              lcdKeypad_->print("PRESS FOR RELAX"); 
              lcdKeypad_->setBackLightOn(true); 
              break;
          case POMODORO_PROCESS_RELAX:    
              lcdKeypad_->print("RELAXING...    "); 
              lcdKeypad_->setBackLightOn(false); 
              break;
      }
  }
private:
   LcdKeypad*  lcdKeypad_;
};

IFormatedOutput* makeOutputer()
{
    return new LcdOutputter(myLcdKeypad);
}

void platform_prepare()
{
    //должны заранее подготовить кнопки
    myLcdKeypad = new LcdKeypad();
}

void platform_prepare_loop_iter()
{
    scheduleTimers();  // Get the timer(s) ticked, in particular the LcdKeypad dirver's keyPollTimer
}

int platform_millis()
{
    return millis();
}