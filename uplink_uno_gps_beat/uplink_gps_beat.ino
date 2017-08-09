#include <SoftwareSerial.h>

 #include <Wire.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(2, 3);
SoftwareSerial mySerial(11,10);
 
static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
 
int cnt = 0;
String data="AT+SEND 01";
 
void setup()
{
  Serial.begin(115200);
   mySerial.begin(38400);
    Wire.begin();
  ss.begin(9600);
}
 
void loop()
{
  int rateValue;
  String fstring="0";
  float flat, flon;
  float lat,lon;
  String slat,slon;
  unsigned long age, date, time, chars = 0;
  unsigned short sentences = 0, failed = 0;
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
  Wire.requestFrom(0xA0 >> 1, 1); 
 

  if(Wire.available()) {

     unsigned char c = Wire.read();   // receive heart rate value (a byte)
   
    
    gps.f_get_position(&flat, &flon, &age);
    print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
    print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
    Serial.println(c);
    //Serial.print(".");
    
    cnt++;
    if( cnt >= 10 )
    {
      if(c<=100){
        fstring += String(c);
      }else{
        fstring = String(c);
      }

      lat= flat * 1000000; 
      lon= flon * 1000000; 
      data = "AT+SEND 01";
      slat = String(lat);
      slon = String(lon);
     slat.remove(8);
     slon.remove(9);
      data += String(slat);
      data += String(slon);
      data += fstring;
      
      if (c!=0){
      Serial.println(data);
      mySerial.println(data);
      }
      cnt = 0;
      delay(5000);
    }
  }
  delay(20);
  
}
 
static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
 
static void print_float(float val, float invalid, int len, int prec)
{
  if (val == invalid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartdelay(0);
}
