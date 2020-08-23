//Setup
const int threshold = 768; //At which position BFL activated
const int thresholdBrake = 100; //At which position Breaklight activated
const float delayBFLSeconds = 0.5; //How long you need to break hard until blinking starts in Seconds
const int bflFrequence = 2; //Times per Second
const float offTime = 0.20; //BL off ratio 
#define blOut 2 //Breaklights Output
#define bpPoti 14 //Poti Input
#define activeSwitch 7 //Switch to Activate BFL
#define inputPedalSwitch 5 //Original Pedal Switch
#define arduinoReady 3 //Output to Relais

//Define Variables (Do not change)  
const int delayTime = 50;
const int delayBFL = (1000*delayBFLSeconds)/delayTime; 
const int frequenceTimeOff = (1000/bflFrequence*offTime);
const int frequenceTimeOn = (1000/bflFrequence) - frequenceTimeOff;
int forcedBreakeCounter = 0;
long previousMillis = 0;
long previousTimeOff = 0;
long previousTimeOn = 0;
int bflActive = false;

//Process Potentiometer (Or Acceleration Sensor) Input
bool checkForBreaking(int thresholdBrake) 
{ 
    int breakPedalForce = analogRead(bpPoti); //Get Pedal Position
    if(breakPedalForce > thresholdBrake){
      return true;
    }else{
      return false;
    } 
} 

//Breaklights
void activateBL(bool status){
  if(status){
    digitalWrite(blOut, HIGH);
  }else{
    digitalWrite(blOut, LOW);
  }
}

//Toggle BFL Function on/off with dip
bool activateBFLFunction(){
  if(digitalRead(activeSwitch) == 0){
    return false;
  }else{
    return true;
  }
}

//Use OEM Switch as Fallback
bool oemSwitchActive(){
  if(digitalRead(inputPedalSwitch)){
    return true;
  }else{
    return false;
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(bpPoti, INPUT); // Breakpedal potentiometer
  pinMode(blOut, OUTPUT); // Output to Breaklights
  pinMode(activeSwitch, INPUT); // Switch
  pinMode(inputPedalSwitch, INPUT); //Breakpedal Switch (OEM)
  pinMode(arduinoReady, OUTPUT); //Set Arduino Ready for Relais (otherwise normal Switch function is given)
  digitalWrite(arduinoReady, HIGH);
  bflActive = activateBFLFunction(); //Activate BFL Function
  //Serial.println(bflActive);
  Serial.println("Initialized");
}

void loop()
{
  Serial.println(oemSwitchActive());
  long currentMillis = millis();
  if(currentMillis - previousMillis > delayTime){ //Non-blocking delay
    previousMillis = currentMillis;
    
    //Break Force
    while(checkForBreaking(threshold) && bflActive && oemSwitchActive()){
      long timeNow = millis();
      forcedBreakeCounter++;
      if(forcedBreakeCounter >= delayBFL){
        if(timeNow - previousTimeOff <= frequenceTimeOff){
          activateBL(false);
          previousTimeOn = timeNow;
        }else if((timeNow - previousTimeOff > frequenceTimeOff) && (timeNow - previousTimeOn <= frequenceTimeOn)){
          activateBL(true);
        }else{
          previousTimeOff = timeNow;  
        }
      }else{
        activateBL(true);
      }
    }
      
    //Normal Braking  
    while((checkForBreaking(thresholdBrake) && (checkForBreaking(threshold) == false || bflActive == false)) || (oemSwitchActive() && checkForBreaking(threshold) == false)){
      Serial.println("Normal");
      Serial.println(checkForBreaking(threshold));
      forcedBreakeCounter = 0; //Reset Counter
      activateBL(true);
    }

    //No Breaking
    while((checkForBreaking(thresholdBrake) == false && checkForBreaking(threshold) == false && oemSwitchActive() == false) || oemSwitchActive() == false){
      activateBL(false);
        forcedBreakeCounter = 0; //Reset Counter
    }
  }
}
