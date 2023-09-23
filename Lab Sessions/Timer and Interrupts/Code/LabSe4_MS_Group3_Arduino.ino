const byte interruptPin = 2;
volatile byte state = LOW;
int i=0;
int j = 0;
int flag =0 ;
float t0 = 0;
float t1 = 0;
float t2 = 0;
float t3 = 0;
float t4 = 0;
  float starttime = 0;  //Variables to do the math
  float endtime=0;
  float resulttime=0;
  float oldresulttime=0;
  float dt = 0;


void setup() {
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin),refreshTime, FALLING);
}

void loop() {
  if (i%2 == 0){
    t0 = millis() ;
    resulttime = t2;
    endtime = t2;
  }
  if (i%2 == 1){
    t1 = millis();
    resulttime = t1 - t0 + endtime;
    t2 = resulttime;
  }
  if (flag==1){
  oldresulttime = t4;
  t0 = oldresulttime;
  t1 = 0;
  t2 = 0;
  endtime = 0;
  resulttime = 0;
  flag = 0;
  i = 0;
}

  Serial.print("Result time: ");  Serial.println(resulttime);
}

void refreshTime(){
  t3 = t4;
  t4 = millis();
  if (abs(t4-t3)>200){
    i++;
    if (abs(t4-t3)<1000)
    flag = 1;
  }
}