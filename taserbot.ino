


//define L298n module IO Pin
#define enB 5
#define in1 11
#define in2 9
#define in3 8
#define in4 7
#define enA 6

#define taser_relay 4
#define taser_button 10



int motorSpeedA = 0;
int motorSpeedB = 0;


void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);   //before useing io pin, pin mode must be set first 
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(taser_button, INPUT_PULLUP);
  pinMode(taser_relay, OUTPUT);

}

void loop() {
  int buttonState = digitalRead(taser_button);
  bool status = false;
  bool move = true;
  int xAxis = analogRead(A1); // Read Joysticks X-axis
  int yAxis = analogRead(A0); // Read Joysticks Y-axis


  
    // Y-axis used for forward and backward control
    if (yAxis < 470) {
      // Set Motor A backward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      // Set Motor B backward
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(yAxis, 470, 0, 0, 255);
      motorSpeedB = map(yAxis, 470, 0, 0, 255);
    }
    else if (yAxis > 550) {
      // Set Motor A forward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      // Set Motor B forward
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(yAxis, 550, 1023, 0, 255);
      motorSpeedB = map(yAxis, 550, 1023, 0, 255);
    }
    // If joystick stays in middle the motors are not moving
    else {
      motorSpeedA = 0;
      motorSpeedB = 0;
    }

    // X-axis used for left and right control
    if (xAxis < 470) {
      // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
      int xMapped = map(xAxis, 470, 0, 0, 255);
      // Move to left - decrease left motor speed, increase right motor speed
      motorSpeedA = motorSpeedA - xMapped;
      motorSpeedB = motorSpeedB + xMapped;
      // Confine the range from 0 to 255
      if (motorSpeedA < 0) {
        motorSpeedA = 0;
      }
      if (motorSpeedB > 255) {
        motorSpeedB = 255;
      }
    }
    if (xAxis > 550) {
      // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
      int xMapped = map(xAxis, 550, 1023, 0, 255);
      // Move right - decrease right motor speed, increase left motor speed
      motorSpeedA = motorSpeedA + xMapped;
      motorSpeedB = motorSpeedB - xMapped;
      // Confine the range from 0 to 255
      if (motorSpeedA > 255) {
        motorSpeedA = 255;
      }
      if (motorSpeedB < 0) {
        motorSpeedB = 0;
      }
    }
    // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
    if (motorSpeedA < 70) {
      motorSpeedA = 0;
    }
    if (motorSpeedB < 70) {
      motorSpeedB = 0;
    }
      analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enB, motorSpeedB); // Send PWM signal to motor B 

   if(buttonState == HIGH) {
    status = true;
    move = false;
    } 
    if (status == true) {
    digitalWrite(taser_relay, HIGH);
  } else {digitalWrite(taser_relay, LOW);}

    if (buttonState == LOW) {
    status = false;
  } 
  
}






