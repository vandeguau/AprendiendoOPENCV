#include <Servo.h>

Servo servoX;          // Instancia del servo para el eje X
int servoXPin = 16;     // Pin al que está conectado el servo para el eje X

const int umbral = 36; // Umbral para el movimiento del servo

const int VelRespuesta = 10;

const int posServoX = 90;

void setup() {
  Serial.begin(9600);
  servoX.attach(servoXPin);
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

      if (posX < -umbral) {
      if(VelRespuesta==180){
        VelRespuesta=90;
        }
      } 
      else if (posX > umbral) {
      int newPos = map(posX, umbral, 320, 90, 180); // Mapear el rango a partir de 10 a 320 a un rango de 90 a 180 grados
      servoX.write(newPos); // Mover el servo X hacia la derecha
      } 
      else {
      //servoX.write(90); // Mantener el servo X en la posición central (90 grados)
      }
      
    }
  }
}
