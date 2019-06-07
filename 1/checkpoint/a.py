from scipy.io import loadmat
from PIL import Image
import matplotlib.pyplot as plt
import cv2
m=loadmat('preds_valid.mat')
print(m['preds'])
point_color = (0, 0, 255)
img=cv2.imread('kun.jpg')
#cv2.rectangle(image,(xmin,ymin),(xmax,ymax),(0,255,0),2)
print(type(m['preds']))
for i in range(7,16):
	print(i,m['preds'][0][i][0],m['preds'][0][i][1])
	cv2.circle(img, ((int)(m['preds'][0][i][0]),(int)(m['preds'][0][i][1])), 10, point_color, 1)
	cv2.putText(img,str(i),((int)(m['preds'][0][i][0]),(int)(m['preds'][0][i][1])),cv2.FONT_HERSHEY_COMPLEX, 0.4,(100,200,20),1)

cv2.line(img,((int)(m['preds'][0][7][0]),(int)(m['preds'][0][7][1])),((int)(m['preds'][0][8][0]),(int)(m['preds'][0][8][1])),(0,255,0),2)
cv2.line(img,((int)(m['preds'][0][13][0]),(int)(m['preds'][0][13][1])),((int)(m['preds'][0][14][0]),(int)(m['preds'][0][14][1])),(0,255,0),2)
cv2.line(img,((int)(m['preds'][0][14][0]),(int)(m['preds'][0][14][1])),((int)(m['preds'][0][15][0]),(int)(m['preds'][0][15][1])),(0,255,0),2)
cv2.line(img,((int)(m['preds'][0][10][0]),(int)(m['preds'][0][10][1])),((int)(m['preds'][0][11][0]),(int)(m['preds'][0][11][1])),(0,255,0),2)
cv2.line(img,((int)(m['preds'][0][11][0]),(int)(m['preds'][0][11][1])),((int)(m['preds'][0][12][0]),(int)(m['preds'][0][12][1])),(0,255,0),2)
cv2.line(img,((int)(m['preds'][0][7][0]),(int)(m['preds'][0][7][1])),((int)(m['preds'][0][12][0]),(int)(m['preds'][0][12][1])),(0,255,0),2)
cv2.line(img,((int)(m['preds'][0][7][0]),(int)(m['preds'][0][7][1])),((int)(m['preds'][0][13][0]),(int)(m['preds'][0][13][1])),(0,255,0),2)
cv2.line(img,((int)(m['preds'][0][10][0]),(int)(m['preds'][0][10][1])),((int)(m['preds'][0][11][0]),(int)(m['preds'][0][11][1])),(0,255,0),2)
cv2.line(img,((int)(m['preds'][0][8][0]),(int)(m['preds'][0][8][1])),((int)(m['preds'][0][9][0]),(int)(m['preds'][0][9][1])),(0,255,0),2)

score = 100.0
d=[]
d.append(0.1*max(0,-m['preds'][0][13][1]-m['preds'][0][15][1]+2*m['preds'][0][14][1]))#L elbow deg
d.append(0.1*abs(m['preds'][0][13][1]-m['preds'][0][15][1]))#L arm incl
d.append(0.3*max(0,m['preds'][0][11][1]-m['preds'][0][12][1]))#R el down
d.append(0.3*max(0,m['preds'][0][10][1]-m['preds'][0][12][1]))#R wri down
d.append(0.1*max(0,abs(m['preds'][0][13][0]-m['preds'][0][14][0])-abs(m['preds'][0][11][0]-m['preds'][0][12][0])))#R el enou

print(d)
for item in d:
	score -= item
cv2.putText(img,str(score),(50,50), cv2.FONT_HERSHEY_COMPLEX, 1.0,(100,200,20),1)
cv2.imshow('image', img)
cv2.waitKey(5000)
cv2.imwrite('kun.png',img)
