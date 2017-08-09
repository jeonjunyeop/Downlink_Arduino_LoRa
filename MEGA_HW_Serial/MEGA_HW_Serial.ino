
void setup()
{
    
  Serial.begin(38400);
   while (!Serial) {
  }
  Serial.println("Serial TEST"); // FOR DEBUG
  
  Serial3.begin(38400);
   while (!Serial3) {
  }
  Serial3.println("Serial1 TEST"); // FOR DEBUG

}

void loop()
{
  if(Serial3.available()){
   //Serial.write(Serial3.read());
   Serial.write(Serial3.read());
 }
}
