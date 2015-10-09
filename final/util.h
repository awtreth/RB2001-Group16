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

  void add(const char character, double* pointer)
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

class NumPrinter
{
  private:
  String var_name[10];
  double* var[10];
  int n_var;
  int period;

  public:

  NumPrinter()
  {
    n_var = 0;
    period = 1000;
  }

  void setPeriod(int new_period)
  {
    this->period = new_period;
  }

  void add(String var_name, double* var_pointer)
  {
    this->var_name[n_var] = var_name;
    this->var[n_var] = var_pointer;
    n_var++;
  }

  void check()
  {
    static long int last_time = millis();
    long int current_time = millis();
    if((current_time-last_time)>this->period)
    {
      Serial.println("*****************************************************");
      for(int i = 0; i < n_var; i++)
      {
        Serial.print(var_name[i].c_str());
        Serial.print(" = ");
        Serial.println(*var[i]);
      }
    }
  }
   
};

#endif
