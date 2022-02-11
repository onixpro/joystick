
#include "joystick_str.h"

#define dataRate RF24_2MBPS //could be lower for more distance
#define paLevel RF24_PA_MIN // could be Lower as well

#define pinJR_X 14
#define pinJR_Y 15
#define pinJL_X 16
#define pinJL_Y 17

#define pinJR_B 4
#define pinJL_B 2

#define pin_led_on 7
#define pin_led_con 8

#define loop_time 200

RF24 radio(9, 10); // CE, CSN
void setup()
{
  Serial.begin(9600);
   Serial.println( "test" );
  printf_begin();
  radio.begin();

  radio.setRetries(15, 15);
  radio.setPayloadSize(payload_size);
  radio.setDataRate(dataRate);
  radio.setPALevel(paLevel);

  radio.openWritingPipe(address);
  radio.stopListening();
  radio.printDetails();

  pinMode(pinJR_X, INPUT);
  pinMode(pinJR_Y, INPUT);
  pinMode(pinJL_X, INPUT);
  pinMode(pinJL_Y, INPUT);
  pinMode(pinJR_B, INPUT_PULLUP);
  pinMode(pinJL_B, INPUT_PULLUP);

  pinMode(pin_led_con, OUTPUT);
  pinMode(pin_led_on, OUTPUT);

  digitalWrite(pin_led_on, HIGH);
  digitalWrite(pin_led_con, LOW);
}
void loop()
{

  struct joystick j1;
  // const char text[] = "Hello World";

  delay(loop_time);
  j1 = {.JR_X = analogRead(pinJR_X),
        .JR_Y = analogRead(pinJR_Y),
        .JR_B = (digitalRead(pinJR_B) ),

        .JL_X = analogRead(pinJL_X),
        .JL_Y = analogRead(pinJL_Y),
        .JL_B = (digitalRead(pinJL_B) )};
  bool is_sended = radio.write(&j1, sizeof(j1));
  if (is_sended)
  {
    digitalWrite(pin_led_con, HIGH);
  }
  else
  {
    digitalWrite(pin_led_con, LOW);
  }
  
  char str[100];
  sprintf(str,"Joystic left:  X: %i, Y: %i, B: %i  ", j1.JL_X,j1.JL_Y ,j1.JL_B);
  Serial.print(str);  
  sprintf(str,"Joystic right: X: %i, Y: %i, B: %i", j1.JR_X,j1.JR_Y ,j1.JR_B);
  Serial.println(str);

  bool b = radio.write(&j1, sizeof(j1));
  Serial.println(b);
  
}
