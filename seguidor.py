import cv2
import mediapipe as mp
import time
import serial

arduino = serial.Serial('COM8', 9600)
time.sleep(2)

mpDraw = mp.solutions.drawing_utils
mpPose =mp.solutions.pose
pose = mpPose.Pose()

objetivo_x = 0  # Inicialización fuera del bloque condicional
objetivo_y = 0  # Inicialización fuera del bloque condicional

cap = cv2.VideoCapture(1)
pTime=0
while True:
    succes,img =cap.read()
    
    img = cv2.flip(img,1)
    imgRGB=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
    results =pose.process(imgRGB)
    #print(results.pose_landmarks)
    #if results.pose_landmarks:
    #    mpDraw.draw_landmarks(img,results.pose_landmarks,mpPose.POSE_CONNECTIONS)

    #Punto Central
    center_height, center_width, _ = img.shape
    center_x, center_y =  center_width // 2,  center_height // 2
    cv2.circle(img, (center_x, center_y), 5, (255, 0, 0), cv2.FILLED)


    # Verificar si los landmarks de la pose están presentes
    if results.pose_landmarks:
        # Obtener las coordenadas de los puntos de los hombros (11 y 12)
        left_shoulder = results.pose_landmarks.landmark[mpPose.PoseLandmark.LEFT_SHOULDER]
        right_shoulder = results.pose_landmarks.landmark[mpPose.PoseLandmark.RIGHT_SHOULDER]

        # Convertir las coordenadas normalizadas a píxeles
        h, w, _ = img.shape
        left_shoulder_x, left_shoulder_y = int(left_shoulder.x * w), int(left_shoulder.y * h)
        right_shoulder_x, right_shoulder_y = int(right_shoulder.x * w), int(right_shoulder.y * h)

        # Calcular el centro entre los dos puntos
        objetivo_x = (left_shoulder_x + right_shoulder_x) // 2
        objetivo_y = (left_shoulder_y + right_shoulder_y) // 2

        # Dibujar un punto en el centro de los hombros
        cv2.circle(img, (objetivo_x, objetivo_y), 5, (0, 0, 255), cv2.FILLED)

    # Calcular las diferencias en las coordenadas
    diff_x = objetivo_x - center_x
    diff_y = objetivo_y - center_y
    print(f"Diff X: {diff_x}, Diff Y: {diff_y} Objetivo X: {objetivo_x}, Objetivo Y: {objetivo_y} Center X: {center_x}, Center Y: {center_y}")
    

    # Enviar las diferencias al Arduino
    arduino.write(f"{diff_x},{diff_y}\n".encode())


    cTime=time.time()
    fps = 1/(cTime-pTime)
    pTime =cTime

    cv2.putText(img,"FPS "+str(int(fps)),(20,50),cv2.FONT_HERSHEY_PLAIN,3,(0,255,0),3)

    cv2.imshow("Imagen",img)
    
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


cv2.waitKey(0)
cv2.destroyAllWindows()

