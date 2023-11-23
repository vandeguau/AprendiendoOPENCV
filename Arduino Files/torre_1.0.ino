#include <Servo.h>

Servo servoX;  // Instancia del servo para el eje X
Servo servoY;  // Instancia del servo para el eje Y

int servoXPin = 16;  // Pin al que está conectado el servo para el eje X
int servoYPin = 5; // Pin al que está conectado el servo para el eje Y

void setup() {
  Serial.begin(9600);
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int commaIndex = data.indexOf(',');
    
    if (commaIndex != -1) {
      String valX = data.substring(0, commaIndex);
      String valY = data.substring(commaIndex + 1);
      
      int posX = valX.toInt();
      int posY = valY.toInt();
      
      int angleX = map(posX, -100, 100, 0, 180);  // Mapear el rango de valores recibidos a ángulos (0-180 grados)
      int angleY = map(posY, -100, 100, 0, 180);
      
      servoX.write(angleX);  // Mover el servo X
      servoY.write(angleY);  // Mover el servo Y
    }
  }
}
