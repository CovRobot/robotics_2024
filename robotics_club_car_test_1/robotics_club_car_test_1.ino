#define m1 5
#define m2 6
#define pot A2

void setup() {
  Serial.begin(9600);
//  pinMode(pot, INPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
//  init_esc(m1);
//  init_esc(m2);
}

void loop() {
//  analogWrite(m1, 70);
  int pot_read = analogRead(pot);
  int mot_val = map(pot_read, 0, 1023, 180, 360);
  Serial.println(mot_val);
  analogWrite(m1, mot_val);
  delay(10);
}

// initialize each esc by increasing and quickly bring the pwm back to 0
void init_esc(int motor){
}