#include <Servo.h>

Servo servoX;          // Instancia del servo para el eje X
int servoXPin = 16;     // Pin al que está conectado el servo para el eje X

const int umbral = 36; // Umbral para el movimiento del servo
const int sumadorMAX = 10; // delay maximo de tiempo de reaccion para los map
const int sumadorMIN = 1; // delay maximo de tiempo de reaccion para los map

int sumador= 1;

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
      sumador = map(posX,-320, -umbral, sumadorMAX, sumadorMIN);//a partir de que tan lejos este sera la cantidad de grados que gira a ese punto
      posServoX = posServoX - sumador;

      if(posServoX<=0){//si el objeto sale del rango el dispositvo solo lo dejara ir ya que no puede seguir infinitamente.
        posServoX=0;
        }

      servoX.write(posServoX);  

      } 
      else if (posX > umbral) {//trabaja la derecha de 90 a 180 grados
      sumador = map(posX, umbral, 320, sumadorMIN, sumadorMAX); //a partir de que tan lejos este sera la cantidad de grados que gira a ese punto
      posServoX = posServoX + sumador;

      if (posServoX >= 180) {
          posServoX = 180; // Ajustar el límite superior
        }

      servoX.write(posServoX); 
      } 
      else {
      //servoX.write(90); // Mantener el servo X en la posición central (90 grados)
      }

    }
  }
}
