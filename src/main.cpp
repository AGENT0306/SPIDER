#include <../include/spdLeg.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

SPDLegs* leg1 = nullptr;
SPDLegs* leg2 = nullptr;
SPDLegs* leg3 = nullptr;
SPDLegs* leg4 = nullptr;

// put function declarations here:

char* readMessage();
void setStand();
void setRest();

void setup() {
  Serial.begin(115200);
  Serial.println("SPIDER Robot Started!");

  Adafruit_PWMServoDriver* pwm = new Adafruit_PWMServoDriver();

  static std::vector<int> leg1Idx = {1,6,10};
  static std::vector<int> leg2Idx = {14,7,11};
  static std::vector<int> leg3Idx = {4,8,12};
  static std::vector<int> leg4Idx = {5,9,13};

  leg1 = new SPDLegs(3, &leg1Idx, "Leg 1", pwm);
  leg2 = new SPDLegs(4, &leg2Idx, "Leg 2", pwm);
  leg3 = new SPDLegs(5, &leg3Idx, "Leg 3", pwm);
  leg4 = new SPDLegs(6, &leg4Idx, "Leg 4", pwm);


  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available() > 0){
    auto message = readMessage();
    if(strcmp(message, "rest") == 0){
      Serial.println("resting\n");
      setRest();
    }else if(strcmp(message, "stand") == 0){
      Serial.println("standing\n");
      setStand();
    }else if (strcmp(message, "move") == 0){
      std::vector<double>* pos = new std::vector<double>{0.0, 0.0, 0.0};
      leg1->moveLeg(pos);
    }else {
      Serial.println("No such command!");
    }
  }
  delay(10);
}

// put function definitions here:

char* readMessage(){
  static char message[20] = {};
  for(int i = 0; i < 20; i++){
    char incomingByte = Serial.read();

    if(incomingByte == '\n' || incomingByte == '\0' || i == 19){
      message[i] = '\0';
      break;
    }

    message[i] = incomingByte;
  }
  return message;
}

void setRest(){
  for(int i = 0; i < 16; i++){
    pwm.setPWM(i,0, 307);
  }
}

void setStand(){
  pwm.setPWM(1, 0, 200);
  pwm.setPWM(4, 0, 460);
  pwm.setPWM(5, 0, 200);
  pwm.setPWM(14, 0, 500);

  pwm.setPWM(6, 0, 370);
  delay(100);
  pwm.setPWM(7, 0, 370);
   delay(100);
  pwm.setPWM(8, 0, 280);
   delay(100);
  pwm.setPWM(9, 0, 250);

  pwm.setPWM(10, 0, 130);
  pwm.setPWM(11, 0, 130);
  pwm.setPWM(12, 0, 500);
  pwm.setPWM(13, 0, 500);
}