//--------------------------------------------------------------
//Scketch d'allumage d'application avec un arduino
//--------------------------------------------------------------


#include <NewPing.h>

#define TRIGGER_PIN  11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int led=13;
double buff[10]={0,0,0,0,0,0,0,0,0,0};//Buffer de filtrage
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(led,OUTPUT);
}

int FIR(int us) //Effectue un filtre à réponse fini... ok c'est juste une moyenne mais quand meme !
{
  int y=0;
  for(int i=1;i<10;i++)
  {
    y=y+buff[i];
    buff[i-1]=buff[i];
//    Serial.print(buff[i]);
  }
//  Serial.println(' ');
  y=y+us;
  y=y/10;
  buff[9]=us;
  if(/*us>0 &&*/ us<5) //la partie commentée fait bipper le signal quand il passe à 0 à cause de l'offset
  {
    return y;
  }
  else
  {
    return us;
  }
}

void loop() {
  delay(50);                     
  unsigned int uS = sonar.ping(); 
  int us2=uS / US_ROUNDTRIP_CM;
  //us2=FIR(us2);
  if(us2>1 && us2<20)
  {
    digitalWrite(led,HIGH);
    Serial.print("1");
  }
  else
  {
    digitalWrite(led,LOW);
    Serial.print("0");
  }
}
