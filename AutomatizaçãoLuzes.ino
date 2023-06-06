const byte LED = 9;
const byte LDR = A5;
unsigned int valorLDR;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
  Serial.begin(1);
}

void loop(){
  valorLDR = analogRead(LDR);
  analogWrite(LED, byte(200 - (valorLDR/4)));
  Serial.println(valorLDR);
}
