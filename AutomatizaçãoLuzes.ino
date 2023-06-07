const byte LED = 9;
const byte LDR = A5;
unsigned int valorLDR;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
  Serial.begin(9600);
}

void loop() {
  valorLDR = analogRead(LDR);
  
  if (valorLDR > 740) {
    digitalWrite(LED, LOW); // Desliga o LED
  } else {
    analogWrite(LED, byte(200 - (valorLDR/4)));
  }
  
  Serial.println(valorLDR);
  delay(600);
}
