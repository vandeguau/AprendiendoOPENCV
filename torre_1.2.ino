#include <Servo.h>

Servo servoX;          // Instancia del servo para el eje X
int servoXPin = 16;     // Pin al que está conectado el servo para el eje X

const int umbral = 36; // Umbral para el movimiento del servo
const int delayMAX = 500; // delay maximo de tiempo de reaccion para los map
const int delayMIN = 1; // delay maximo de tiempo de reaccion para los map

int VelRespuesta = 10;

int posServoX = 90;

void setup() {
  Serial.begin(9600);
  servoX.attach(servoXPin);
  servoX.write(90);
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

      if (posX < -umbral) {//trabaja la izquierda de 0 a 90 grados
      posServoX = posServoX - 3;
      VelRespuesta = map(posX,-320, -umbral, delayMIN, delayMAX);//a partir de que tan lejos este sera la velocidad con la que se mueva a ese punto
      servoX.write(posServoX);

      if(posServoX==0){//si el objeto sale del rango el dispositvo solo lo dejara ir ya que no puede seguir infinitamente.
        posServoX=90;
        }
      delayMicroseconds(VelRespuesta);
        
      } 
      else if (posX > umbral) {//trabaja la derecha de 90 a 180 grados
      posServoX = posServoX + 3;
      VelRespuesta = map(posX, umbral, 320, delayMAX, delayMIN); //a partir de que tan lejos este el centro del objetivo sera la velocidad con la que se mueva a ese punto
      servoX.write(posServoX);

      if(posServoX==180){//si el objeto sale del rango el dispositvo solo lo dejara ir ya que no puede seguir infinitamente.
        posServoX=90;
        }
      delayMicroseconds(VelRespuesta);
      
      } 
      else {
      //servoX.write(90); // Mantener el servo X en la posición central (90 grados)
      }
      
    }
  }
}
