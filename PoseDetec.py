import cv2
import mediapipe as mp
import time

mpDraw = mp.solutions.drawing_utils
mpPose =mp.solutions.pose
pose = mpPose.Pose()


cap = cv2.VideoCapture(1)
pTime=0
while True:
    succes,img =cap.read()
    
    img = cv2.flip(img,1)
    imgRGB=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
    results =pose.process(imgRGB)
    #print(results.pose_landmarks)
    if results.pose_landmarks:
        mpDraw.draw_landmarks(img,results.pose_landmarks,mpPose.POSE_CONNECTIONS)



    cTime=time.time()
    fps = 1/(cTime-pTime)
    pTime =cTime

    cv2.putText(img,"FPS "+str(int(fps)),(20,50),cv2.FONT_HERSHEY_PLAIN,3,(0,255,0),3)

    cv2.imshow("Imagen",img)
    
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


cv2.waitKey(0)
cv2.destroyAllWindows()

