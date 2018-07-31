"""
    File   : FaceDetect.py
    Autor  : Francisco Guilherme
    Módulo : Identificar rostos
"""

# Importando bibliotecas
import cv2
import sys

# Capturar dados enviados pelo usuário
imagePath = sys.argv[1]
xmlFlPath = sys.argv[2]

# Base para arquivo .xml
faceCascade = cv2.CascadeClassifier(xmlFlPath)

# Lendo a imagem
image = cv2.imread(imagePath)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Dectando faces na imagem
faces = faceCascade.detectMultiScale(
    gray,
    scaleFactor = 1.1,
    minNeighbors = 5,
    minSize = (30, 30),
    flags = cv2.cv.CV_HAAR_SCALE_IMAGE
)

# Construindo retangulos em torno das faces
for (x, y, w, h) in faces
    cv2.rectang(image, (x, y), (x + w, y + h), (0, 255, 0), 2)
    
cv2.imshow("Rostos encontrados", image)
cv2.waitKey(0)
