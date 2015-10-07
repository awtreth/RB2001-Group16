#ifndef UTIL_H
#define UTIL_H

#include "Arduino.h"

//return values for smart movments (for FRED and DriveTrain)
enum {NOT_DONE_YET = 0, DONE = 1};

//For param Tuning
class ParamParser
{
  private:

  char char_code[10];
  double* variables[10];
  int n_cmd;

  public:

  ParamParser(){n_cmd = 0; /*Serial.begin(38400);*/}

  void new_cmd(const char character, double* pointer)
  {
    char_code[n_cmd] = character;
    variables[n_cmd] = pointer;
    n_cmd++;
  }

  void check()
  {
    if(Serial.available())
    {
      String str = Serial.readString();
      char op = str.charAt(0);

      Serial.print(str);
      
      for (int i = 0; i < n_cmd; i++)
      {
        if(op == char_code[i])
        {
          Serial.print(":   ");
          Serial.print(*variables[i]);
          Serial.print("->");
          *variables[i] = str.substring(1).toFloat();
          Serial.println(*variables[i]);
          return;
        }
      }
      Serial.println(":   Invalid Command");
    }
  }
};

#endif
