
unsigned long time;
unsigned long time_prev;

float sp;
float pv;
float e;
float e_prev;

float p;
float i;
float d;
float pid;

float i_prev;
float d_prev;


float p_control(float kp, float error) {
    float p_control_val = kp*error;
    return p_control_val;
}


float i_control(float ki, float error, float error_prev, float T, float i_control_prev,float down_limit, float up_limit) {
    float i_control_val = ki * T/2 * (error + error_prev) + i_control_prev;
    
    if (i_control_val > up_limit){
      i_control_val = up_limit;
    } 
    if (i_control_val < down_limit) {
      i_control_val = down_limit;
    }
    
    return i_control_val;
}

float d_control(float kd, float error, float error_prev, float T, float d_control_prev, float down_limit, float up_limit){
    float d_control_val = (kd *  (error - error_prev)/T);

    if (d_control_val > up_limit){
      d_control_val = up_limit;
    } 
    if (d_control_val < down_limit) {
      d_control_val = down_limit;
    }
    return d_control_val;
}


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


  //4 p = kp*e
  float kp = 2.5;
  p = p_control(kp, e);


  //5 i = ki(konstanta integral) * jumlah error keseluruhan selama sistem nyala
  float ki = 0.1;
  //memanggil function dengan urutan inputan ki, error, error sebelumnya, interval, nilai i sebelumnya, nilai min, dan nilai max
  i = i_control(ki, e, e_prev, 0.5, i_prev, 0, 255);


  //6 d = kd * perbedaan error per satuan waktu
  float kd = 0;
  d = d_control(kd, e, e_prev, 0.5, d_prev, 0, 255);


  // p tambah i tambah d
  pid = p+i+d;
  

  //batasin nilai PID sesuai dengan kemampuan pwm microcontroller
  if (pid > 255){
    pid = 255;
  }
  if (pid < 0){
    pid = 0;
  }

  
  //masuk ke plant lewat pin pwm
  analogWrite(9, pid);


  //debug apa yang terjadi
  Serial.print("sp : ");
  Serial.print(sp);


  Serial.print(" pv : ");
  Serial.print(pv);

  Serial.print(" e : ");
  Serial.print(e);

  Serial.print(" e_prev : ");
  Serial.print(e_prev);

  Serial.print(" p : ");
  Serial.print(p);

  Serial.print(" i : ");
  Serial.print(i);

  Serial.print(" d : ");
  Serial.print(d);


  Serial.print(" pid : ");
  Serial.print(pid);

  Serial.println();

  e_prev = e;
  i_prev = i;
  d_prev = d;
  time_prev = millis();

  
  }
  
  
  


}
