from scipy.io import loadmat
from PIL import Image
import matplotlib.pyplot as plt
import cv2
import math
m=loadmat('preds_valid.mat')
print(m['preds'])
best_list=[]
best_index=0
best=0

for i in range(1,50):
	# log write
	global count
	object = open("C:\\Users\\cityscience\\Documents\\bowbow\\judge\\judgeProgress.txt", "w")
	object.write(str(i+540))
	object.close()

	point_color = (0, 0, 255)
	img=cv2.imread('C:\\Users\\cityscience\\Desktop\\1\\checkpoint\\mpii\\new\\input\\'+str(i)+'.jpg')
	#cv2.rectangle(image,(xmin,ymin),(xmax,ymax),(0,255,0),2)
	print(type(m['preds']))
	for j in range(7,16):
		print(j,m['preds'][i-1][j][0],m['preds'][i-1][j][1])
		cv2.circle(img, ((int)(m['preds'][i-1][j][0]),(int)(m['preds'][i-1][j][1])), 10, point_color, 1)
		cv2.putText(img,str(j),((int)(m['preds'][i-1][j][0]),(int)(m['preds'][i-1][j][1])),cv2.FONT_HERSHEY_COMPLEX, 0.4,(100,200,20),1)

	cv2.line(img,((int)(m['preds'][i-1][7][0]),(int)(m['preds'][i-1][7][1])),((int)(m['preds'][i-1][8][0]),(int)(m['preds'][i-1][8][1])),(0,255,0),2)
	cv2.line(img,((int)(m['preds'][i-1][13][0]),(int)(m['preds'][i-1][13][1])),((int)(m['preds'][i-1][14][0]),(int)(m['preds'][i-1][14][1])),(0,255,0),2)
	cv2.line(img,((int)(m['preds'][i-1][14][0]),(int)(m['preds'][i-1][14][1])),((int)(m['preds'][i-1][15][0]),(int)(m['preds'][i-1][15][1])),(0,255,0),2)
	cv2.line(img,((int)(m['preds'][i-1][10][0]),(int)(m['preds'][i-1][10][1])),((int)(m['preds'][i-1][11][0]),(int)(m['preds'][i-1][11][1])),(0,255,0),2)
	cv2.line(img,((int)(m['preds'][i-1][11][0]),(int)(m['preds'][i-1][11][1])),((int)(m['preds'][i-1][12][0]),(int)(m['preds'][i-1][12][1])),(0,255,0),2)
	cv2.line(img,((int)(m['preds'][i-1][7][0]),(int)(m['preds'][i-1][7][1])),((int)(m['preds'][i-1][12][0]),(int)(m['preds'][i-1][12][1])),(0,255,0),2)
	cv2.line(img,((int)(m['preds'][i-1][7][0]),(int)(m['preds'][i-1][7][1])),((int)(m['preds'][i-1][13][0]),(int)(m['preds'][i-1][13][1])),(0,255,0),2)
	cv2.line(img,((int)(m['preds'][i-1][10][0]),(int)(m['preds'][i-1][10][1])),((int)(m['preds'][i-1][11][0]),(int)(m['preds'][i-1][11][1])),(0,255,0),2)
	cv2.line(img,((int)(m['preds'][i-1][8][0]),(int)(m['preds'][i-1][8][1])),((int)(m['preds'][i-1][9][0]),(int)(m['preds'][i-1][9][1])),(0,255,0),2)

	score = 100.0
	d=[]
	d.append(0.2*max(0,-m['preds'][i-1][13][1]-m['preds'][i-1][15][1]+2*m['preds'][i-1][14][1]))#L elbow deg
	d.append(0.2*abs(m['preds'][i-1][13][1]-m['preds'][i-1][15][1]))#L arm incl
	d.append(0.5*max(0,m['preds'][i-1][11][1]-m['preds'][i-1][12][1]))#R el down
	d.append(0.5*max(0,m['preds'][i-1][10][1]-m['preds'][i-1][12][1]))#R wri down
	length1=(m['preds'][i-1][13][0]-m['preds'][i-1][14][0])*(m['preds'][i-1][13][0]-m['preds'][i-1][14][0])+(m['preds'][i-1][13][1]-m['preds'][i-1][14][1])*(m['preds'][i-1][13][1]-m['preds'][i-1][14][1])
	length2=(m['preds'][i-1][11][0]-m['preds'][i-1][12][0])*(m['preds'][i-1][11][0]-m['preds'][i-1][12][0])+(m['preds'][i-1][11][1]-m['preds'][i-1][12][1])*(m['preds'][i-1][11][1]-m['preds'][i-1][12][1])
	length1=math.sqrt(length1);
	length2=math.sqrt(length2);
	d.append(0.2*max(0,length1-length2))#R el enou

	print(d)
	for item in d:
		score -= item
	if score<0:
		score=0
	cv2.putText(img,'%.2f' % score,(50,50), cv2.FONT_HERSHEY_COMPLEX, 1.0,(100,200,20),2)
	#save best
	if (score>best):
		best=score
		best_index=i
		best_list=d
	#cv2.imshow('image', img)
	#cv2.waitKey(5000)
	cv2.imwrite('C:\\Users\\cityscience\\Desktop\\1\\checkpoint\\mpii\\new\\output\\'+str(i)+'.png',img)

object = open("C:\\Users\\cityscience\\Documents\\bowbow\\judge\\bestpose.txt", "w")
object.write("");
object.close();
object = open("C:\\Users\\cityscience\\Documents\\bowbow\\judge\\bestpose.txt", "a")
object.write('%.2f\n' % best)
object.write(str(best_index)+'\n')
for item in best_list:
	object.write('%.2f\n' % item)
object.close()