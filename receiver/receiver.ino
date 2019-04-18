#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();


#define pin1 6
#define pin2 7
#define codeA -12127
#define codeB -12126

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on pin 2
  pinMode(pin1, OUTPUT);
  digitalWrite(pin1, HIGH);
  pinMode(pin2, OUTPUT);
  digitalWrite(pin2, HIGH);
}

void loop() {
  static unsigned long previousMillis = 0;
  
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    
    if (value == 0) {
      Serial.println("Unknown encoding");
      
    } else {
      if (value == codeA) {
        Serial.println("Received A");
        digitalWrite(pin2, HIGH);
        digitalWrite(pin1, LOW);   
        previousMillis = millis();
                        
      }
      if (value == codeB) {
        Serial.println("Received B");
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);                        
        previousMillis = millis();
      }
      
    }

    mySwitch.resetAvailable();
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
     previousMillis = currentMillis;
     digitalWrite(pin2, HIGH);
     digitalWrite(pin1, HIGH); 
  }
}
