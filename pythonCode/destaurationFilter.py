import cv2
import numpy as np

#read image
image = cv2.imread("../assets/putin.jpg")

#convert to HSV color space
hsvImage = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

#create a copy of hsv image to work on
hsvImageCopy = hsvImage.copy()

#convert to float32
hsvImageCopy = np.float32(hsvImageCopy)

#initialize desaturation Scale value
saturationScale = 0.01

#split the channels
H, S, V = cv2.split(hsvImageCopy)

#Desaturation. Multiply S channel by scaling factor and make sure the values are between 0 and 255
S = np.clip(S * saturationScale, 0, 255)

#merge the channels
hsvImageCopy = cv2.merge([H, S, V])

#convert back to uint8
hsvImageCopy = np.uint8(hsvImageCopy)

#convert back to bgr color space
hsvImageCopy = cv2.cvtColor(hsvImageCopy, cv2.COLOR_HSV2BGR)

#create windows to show image
cv2.namedWindow("image", cv2.WINDOW_NORMAL)
cv2.namedWindow("hsv", cv2.WINDOW_NORMAL)
cv2.namedWindow("desaturated", cv2.WINDOW_NORMAL)

#display images
cv2.imshow("image", image)
cv2.imshow("hsv", hsvImage)
cv2.imshow("desaturated", hsvImageCopy)

#press esc to exit the program
cv2.waitKey(0)

#close all the opened windows
cv2.destroyAllWindows()