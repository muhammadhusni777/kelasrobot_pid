
unsigned long time;
unsigned long time_prev;

float sp;
float pv;
float e;
float e_prev;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  time = millis() - time_prev;
  
  
  if (time > 500){

  //1 nentuin nilai setpoint
  sp = 350;

  //2 baca sensor
  pv = analogRead(A0);
  
  //3 error = setpoint - sensor
  e = sp-pv;

  if (e > 0){
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }



  Serial.print("sp : ");
  Serial.print(sp);


  Serial.print(" pv : ");
  Serial.print(pv);

  Serial.print(" e : ");
  Serial.print(e);


  Serial.println();


  time_prev = millis();

  
  }
  
  
  


}
