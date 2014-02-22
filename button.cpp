
#include "button.h"

Button::Button(int pin, void(*buttonPressedCallback)(void), long debounceDelay) {

  _pin = pin;
  _buttonPressedCallback = buttonPressedCallback;
  _buttonLongPressedCallback = 0;
  _debounceDelay = debounceDelay;
  _lastDebounceTime = 0;
  _buttonState = LOW;
  _lastButtonState = LOW;
  _longPressRecognitionDelay = 0;
  _longPressRepetitionDelay = 0;
  _lastLongPressTime = 0;
  _longPressRecognized = false;

  pinMode(_pin, INPUT);
}

Button::Button(int pin, void(*buttonPressedCallback)(void), long debounceDelay, void(*buttonLongPressedCallback)(void), long longPressRecognitionDelay, long longPressRepetitionDelay) {
  _pin = pin;
  _buttonPressedCallback = buttonPressedCallback;
  _buttonLongPressedCallback = buttonLongPressedCallback;
  _debounceDelay = debounceDelay;
  _lastDebounceTime = 0;
  _buttonState = LOW;
  _lastButtonState = LOW;
  _longPressRecognitionDelay = longPressRecognitionDelay;
  _longPressRepetitionDelay = longPressRepetitionDelay;
  _lastLongPressTime = 0;
  _longPressRecognized = false;
    if (_pin >= 0) {
        pinMode(_pin, INPUT);
    }
}

void Button::update() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(_pin);
  long readingTime = millis();

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != _lastButtonState) {
    // reset the debouncing timer
    _lastDebounceTime = readingTime;
  } 
  
  if ((readingTime - _lastDebounceTime) > _debounceDelay) {
    // If a up to down transition detected call the pressed calback
    if (_buttonState == HIGH && reading == LOW) {
      if (!_buttonLongPressedCallback || !_longPressRecognized) {
        _buttonPressedCallback();
      } else if (_longPressRepetitionDelay == 0)  {
       _buttonLongPressedCallback();
      }
      _lastLongPressTime = 0;
      _longPressRecognized=false;
    }
    
   // If a up high transition detected call 
   if (_buttonLongPressedCallback && _longPressRepetitionDelay > 0 && _buttonState == LOW && reading == HIGH) {
      _lastLongPressTime = readingTime;
    }
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    _buttonState = reading;
  }
  
  
  if (_buttonState && _buttonLongPressedCallback && _longPressRecognitionDelay > 0 && !_longPressRecognized && (readingTime - _lastLongPressTime) > _longPressRecognitionDelay) {
    _longPressRecognized = true;
    if (_longPressRepetitionDelay > 0) {
      _buttonLongPressedCallback();
      _lastLongPressTime = readingTime;
    }
  } else if (_buttonState && _longPressRecognized && _longPressRepetitionDelay > 0 && (readingTime - _lastLongPressTime) > _longPressRepetitionDelay) {
    _buttonLongPressedCallback();
    _lastLongPressTime = readingTime;
  }



  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  _lastButtonState = reading;
  

}
