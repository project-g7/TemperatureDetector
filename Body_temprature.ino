#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>

ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int c=0,n=0;
const int buzzer = 9;
const int RED = 13;
const int YELLOW = 12;

void setup () 
{ pinMode(RED, OUTPUT);
     pinMode(YELLOW, OUTPUT);
   pinMode(buzzer, OUTPUT);
    Serial.begin(9600);
    Rtc.Begin();
     mlx.begin();

   
Serial.print("Id");Serial.print("\t");Serial.print("Temprature");Serial.print("\t");Serial.print("Date");Serial.print("\t");Serial.println("Status");

}

void loop () 
{   

     double x=mlx.readObjectTempC();
  if(x>38){  //High Temperature
    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);

     digitalWrite(RED, HIGH);
      digitalWrite(YELLOW, LOW);
     tone(buzzer, 1000); 
        delay(1000);             
        digitalWrite(RED, LOW);       
      } 
      noTone(buzzer);
       if(x>31 && x<38){ //Low Temperature
    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime2(compiled);

     digitalWrite(YELLOW, HIGH);
      digitalWrite(RED, LOW); 
        delay(1000); 
        digitalWrite(YELLOW, LOW);       
      } 
s
  
    

    delay(500); 
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%04u-%02u-%02u"),
             dt.Year(),
            dt.Month(),
            dt.Day()
            );
    Serial.print("1");Serial.print("\t");Serial.print(mlx.readObjectTempC()); Serial.print("*C");Serial.print("\t");Serial.print(datestring);Serial.print("\t");Serial.println("1");
}void printDateTime2(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%04u-%02u-%02u"),
             dt.Year(),
            dt.Month(),
            dt.Day()
            );
    Serial.print("1");Serial.print("\t");Serial.print(mlx.readObjectTempC()); Serial.print("*C");Serial.print("\t");Serial.print(datestring);Serial.print("\t");Serial.println("0");
}
