void setup()
{
Serial.begin(115200);//Set baudrate
}
void loop()
{
//Print a string on the serial channel
Serial.println("Hello World!");
delay(5000);// Introduce a delay
}
