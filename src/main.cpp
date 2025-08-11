#include <spdLeg.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// put function declarations here:

char* readMessage();
void setStand();
void setRest();

int minPulse = 103;
int maxPulse = 512;


int rest = 307;
int servoNum = 1;

void setup() {
  Serial.begin(115200);
  Serial.println("Servo Testing!");

  pwm.begin(); // Initialize the PWM driver
  pwm.reset();

  pwm.setOscillatorFrequency(25000000); // Set the oscillator frequency
  pwm.setPWMFreq(60); // Set frequency to 60 Hz for servos



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
    }else{
      //Serial.print(message);
      Serial.println("hi");
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