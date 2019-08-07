import cv2

vc = cv2.VideoCapture('C://Users//jsjtx//Desktop//1.avi')  # 读入视频文件
c = 1

if vc.isOpened():  # 判断是否正常打开
    rval, frame = vc.read()
    print("AA")
else:
    rval = False

timeF = 1  # 视频帧计数间隔频率

while rval:  # 循环读取视频帧
    rval, frame = vc.read()
    if (c % timeF == 0):  # 每隔timeF帧进行存储操作
        cv2.imwrite('C://Users//jsjtx//Desktop//imgaaa//' + str((int)(c/timeF)) + '.jpg', frame)  # 存储为图像
    c = c + 1
    cv2.waitKey(1)
vc.release()
