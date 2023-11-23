#include <Servo.h>

Servo servoX;          // Instancia del servo para el eje X
int servoXPin = 16;     // Pin D0 GPI16 al que está conectado el servo para el eje X

Servo servoY;          // Instancia del servo para el eje Y
int servoYPin = 5;     // Pin D1 GPIO5 al que está conectado el servo para el eje Y

const int umbral = 36; // Umbral para el movimiento del servo
const int sumadorMAX = 10; // delay maximo de tiempo de reaccion para los map
const int sumadorMIN = 1; // delay maximo de tiempo de reaccion para los map

int sumadorX= 1;
int sumadorY= 1;

int posServoX = 90;
int posServoY = 90;

void setup() {
  Serial.begin(9600);
  servoX.attach(servoXPin);
  servoX.write(90);
  servoY.attach(servoYPin);
  servoY.write(90);
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
        sumadorX = map(posX,-320, -umbral, sumadorMAX, sumadorMIN);//a partir de que tan lejos este sera la cantidad de grados que gira a ese punto
        posServoX = posServoX - sumadorX;

        if(posServoX<=0){//si el objeto sale del rango el dispositvo solo lo dejara ir ya que no puede seguir infinitamente.
          posServoX=0;
        }

         
      } 
      else if (posX > umbral) {//trabaja la derecha de 90 a 180 grados
        sumadorX = map(posX, umbral, 320, sumadorMIN, sumadorMAX); //a partir de que tan lejos este sera la cantidad de grados que gira a ese punto
        posServoX = posServoX + sumadorX;

        if (posServoX >= 180) {
          posServoX = 180; // Ajustar el límite superior
        }

        
      }

      if (posY < -umbral) {//trabaja hacia arriba de 0 a 90 grados para el eje Y
        sumadorY = map(posY, -240, -umbral, sumadorMAX, sumadorMIN);//a partir de que tan lejos este sera la cantidad de grados que gira a ese punto
        posServoY = posServoY - sumadorY;

        if(posServoY<=0){//si el objeto sale del rango el dispositvo solo lo dejara ir ya que no puede seguir infinitamente.
          posServoY=0;
        }

         
      }
      else if (posY > umbral) {//trabaja hacia abajo de 90 a 180 grados para el eje Y
        sumadorY = map(posY, umbral, 240, sumadorMIN, sumadorMAX); //a partir de que tan lejos este sera la cantidad de grados que gira a ese punto
        posServoY = posServoY + sumadorY;

        if (posServoY >= 180) {
          posServoY = 180; // Ajustar el límite superior
        }

        
      }  

      servoX.write(posServoX); 
      servoY.write(posServoY); 
    }
  }
}
