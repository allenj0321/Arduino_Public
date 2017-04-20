
/* Power loss detection system for Arduino.
    Requirments: Arduion IDE  ( Using 1.8.2)
    Using Arduinio Uno Version 1.0 < 20012 Revision
    This code is strictly to Arduino Standards, Any Arduino should work for this code, even the Third Party versions: Should work on any ARM processor with GCC.
*/
#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x59, 0x67 };   //This mac address must be unique. Currently this shows same as Windows PC.
// change network settings to yours
IPAddress ip( x, x, x, x );     // This is not set to Static. Check DHCP before or PING this address.
IPAddress gateway(  x, x, x, x );
IPAddress subnet( 255, 255, 255, 0 );
long previousTime = 0; // Used for Timing Controls.
long interval = 240000;  // This is 10 Minutes in milliseconds
int in = 0;  // Setting up the changed code
int out = 0; // Setting up the output switch.

// change server to your email server ip or domain. Use Commas not periods.
IPAddress server( x, x, x, x ); //IP GOES here
EthernetClient client;



void setup() {
  pinMode(LED_BUILTIN, OUTPUT); /* This makes my LEDS brighter. */
  Serial.begin(9600); // This is for Debugging purposes only < remove at ship>
  Ethernet.begin(mac, ip, gateway, gateway, subnet); // Initilize Ethernet: Should be About 30 seconds into init.



}

byte sendEmail()
{
  byte thisByte = 0;
  byte respCode;



  if (client.connect(server, 25) == 1) {

  } else {
    Serial.println(F("connection failed")); // This will never been seen.
    return 0;
  }


  // change to your public ip, this is really not needed for OpenRelay
  client.println(F("helo 1.2.3.4"));



  // change to your email address (sender)
  client.println(F("MAIL From: "));


  // change to recipient address

  client.println(F("RCPT To:"""));


  client.println(F("DATA"));



  // change to recipient address
  client.println(F("To: You ")); // Use Lastname, First name/

  // change to your address
  client.println(F("From: Test """));

  client.println(F("Subject: PowerLoss \r\n"));

  client.println(F("PowerLoss!, Will Retry in 20 Minutes"));

  client.println(F("."));


  client.println(F("QUIT"));


  client.stop();
  return 1;
}


/*  while(!client.available()) {
    delay(1);
    loopCount++;
*/


/////////////////////////////////////////Read PIN //////////////////////////////////////////
byte readpin()
{
  // Reading on Pin A2, Can Change to Any Analog Pin on Board.
  in = analogRead(A5);
  if (in  > 16 )  { // This will work for PIN A5, any other pin will give lesser voltage.
    out = 3; // Had to use 3 for this int since orginal state is 3.
  }

}

//////////////// MAIN BODY OF PROGRAM /////////////////////////

void loop() {
  readpin();
  if (out == 3 ) {

    out = 4; // Switch Variable to help contain loop.
    email_timing();
    exit(0);  // Kill the loop.


  }
  /* else if (currentTime - previousTime > interval) {
     sendEmail();
     Serial.println("Email is activating");
     Serial.println("Exiting Loop");
     exit(0); */
}
// email_timing = Initilize Function after five minutes of init.
void email_timing() {
  unsigned long currentTime = 0;
  currentTime = millis();
  if (currentTime > interval) {  //
    sendEmail();
    Serial.println ("Email Non-loop is active");


  }
  else {
    readpin();
  }

}
