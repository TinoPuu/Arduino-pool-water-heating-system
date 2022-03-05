
const int buttonPin = 2;
int WaterSensor = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(12, OUTPUT); //red led
  pinMode(11, OUTPUT); //white led
  pinMode(10, OUTPUT); //green led
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  WaterSensor = digitalRead(buttonPin);
  int WaterTemperature = analogRead(A6); // reading the WaterTemperature value from A1
  Serial.println(WaterTemperature); // display it on a monitor
  if (WaterTemperature < 3)
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    delay(2000);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    delay(1000);
  }
  else
  {
    digitalWrite(11, LOW);
    if (WaterSensor == HIGH)
    {
      // turn LED on:
      digitalWrite(12, LOW);
      digitalWrite(10, HIGH);
      Serial.println("Pumpataan säiliöstä vettä altaaseen");
    }
    else
    {
      // turn LED off:
      digitalWrite(10, LOW);
      digitalWrite(12, HIGH);
      Serial.println("Pumpataan altaasta vettä säiliöön");
    }
  }
}
