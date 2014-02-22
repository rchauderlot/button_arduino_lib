#ifndef _BUTTON_
#define _BUTTON_


#include "Arduino.h"

class Button {

public:

  Button(int pin, void(*buttonPressedCallback)(void), long debounceDelay);
  Button(int pin, void(*buttonPressedCallback)(void), long debounceDelay, void(*buttonLongPressedCallback)(void), long longPressRecognitionDelay, long longPressRepetitionDelay);
  void update();
    
    
private:

  int  _pin;
  void (*_buttonPressedCallback)(void);

  long _debounceDelay;
  int  _buttonState; // Debounced state
  int  _lastButtonState; // transitory state
  long _lastDebounceTime;

  void (*_buttonLongPressedCallback)(void);
  boolean _longPressRecognized;
  long _longPressRepetitionDelay;  
  long _longPressRecognitionDelay;
  long _lastLongPressTime;
  
  
};

#endif /* _BUTTON_ */
