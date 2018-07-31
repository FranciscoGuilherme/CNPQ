#include <IRremote.h>
#include <AFMotor.h>
#include <Ultrasonic.h>

/*---[DEFININDO PINOS]---*/
#define SINAL A1  /*[PINO IR]*/
#define TRIG1 A5  /*[PINO FSU]*/
#define ECHO1 A4  /*[PINO FSU]*/
#define TRIG2 A3  /*[PINO TSU]*/
#define ECHO2 A2  /*[PINO TSU]*/
#define SPEED 255 /*[VELOCIDADE MOTOR 1]*/ /*{0..255}*/

AF_DCMotor M1(1);                     /*[DEFININDO MORTOR 1]*/
IRrecv irrecv(SINAL);                 /*[SINAL IR]*/
decode_results results;               /*[SINAL DECODIFICADO]*/
Ultrasonic ultrasonic1(TRIG1, ECHO1); /*[CONFIGURACAO FSU]*/
Ultrasonic ultrasonic2(TRIG2, ECHO2); /*[CONFIGURACAO TSU]*/

void setup()
{
  irrecv.enableIRIn(); /*[INICIALIZA RECEPTOR]*/
  M1.setSpeed(SPEED);  /*[VELOCIDADE MOTOR 1]*/
  Serial.begin(9600);
}

void loop() 
{
  /*---[VARIAVEIS]---*/
  float cmSU1, cmSU2;
  long sensorIR;
  long microsec1 = ultrasonic1.timing();
  long microsec2 = ultrasonic2.timing();

  cmSU1 = ultrasonic1.convert(microsec1, Ultrasonic::CM);
  cmSU2 = ultrasonic2.convert(microsec2, Ultrasonic::CM);
    
  if (irrecv.decode(&results))
  {
    sensorIR = results.value;
    irrecv.resume();
  }
  
  if (sensorIR == 16775685)
    M1.run(RELEASE);
  else 
    if (sensorIR == 16769055 || cmSU2 <= 5.0)
      M1.run(FORWARD);
  else 
    if (sensorIR == 16773135 || cmSU1 <= 5.0)
      M1.run(BACKWARD);
}
