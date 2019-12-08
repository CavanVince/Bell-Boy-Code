/***************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/index.php?route=product/product&product_id=1121>

 ***************************************************
 This example shows the basic function of library for DFPlayer.

 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)

 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

/*Link to download library https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299 */
/*Click DFPlayer Mini SKU DFR0299*/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

int offButton = 12;
int pirSensor = 7;
bool isOff = true;
int val = 0;
int buttonVal = 0;


void setup()
{
  pinMode(offButton, INPUT);
  pinMode(pirSensor, INPUT);
  randomSeed(analogRead(6));
  
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));



  myDFPlayer.volume(15);  //Set volume value. From 0 to 30
  //myDFPlayer.play(1); //This is for debugging
}

void loop()
{
  val = digitalRead(pirSensor);
  buttonVal = digitalRead(offButton);
  
   if(isOff && buttonVal == LOW)
  {
    isOff = false;
    delay(1000);
  }
  else if(isOff == false && buttonVal == LOW)
  {
    isOff = true;
    delay(1000);  
  }
  if(val == HIGH && isOff == false)
  {
    myDFPlayer.play(random(1,41));
    delay(32000);
    myDFPlayer.stop();
  }

    
}
