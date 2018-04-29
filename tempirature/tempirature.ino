int temp = 0;

void setup() {
  pinMode(A5, INPUT);
  Serial.begin(115200);
}

void loop() {
  temp = analogRead(A5);
  Serial.println(temp);
  delay(1000*5);
}
