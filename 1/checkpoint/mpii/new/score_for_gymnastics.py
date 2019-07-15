from scipy.io import loadmat
from PIL import Image
import matplotlib.pyplot as plt
import cv2
import math

m=loadmat('preds_valid.mat')
print(m['preds'])
best_list={1:[],2:[],3:[],4:[]}
best_index={1:0,2:0,3:0,4:0}
best={1:0,2:0,3:0,4:0}
pose_name={1:'Pose A',2:'Pose B',3:'Pose C',4:'Pose D'}

def relu(v):
    if (v<0):
        return 0
    return v

def bend_score(y1, y2, x1, x2, weight):
    punish_angle = 0.25
    angle = abs(math.atan(abs(y1 - y2) / abs(x1 - x2)))
    if (x1==x2):
        angle = abs(math.atan(abs(y1 - y2) / 0.0001))
    if angle <= punish_angle:
        return 2*weight*abs(punish_angle-angle)
    return math.pi/4 - angle

def topangle_socre(weight):
        v1x = m['preds'][i-1][11][0] - m['preds'][i-1][9][0]
        v2x = m['preds'][i-1][14][0] - m['preds'][i-1][9][0]
        v1y = m['preds'][i-1][11][1] - m['preds'][i-1][9][1]
        v2y = m['preds'][i-1][14][1] - m['preds'][i-1][9][1]
        if (v1x==v2x and v1y==v2y) is False:
            tmp_angle = abs(math.acos((v1x*v2x+v1y*v2y)/(math.sqrt(pow(v1x, 2)+pow(v1y, 2))*math.sqrt(pow(v2x, 2)+pow(v2y, 2)))))
        else:
            tmp_angle = 0
        angle = (math.pi - tmp_angle)/2
        return weight*angle

# point_1 should over p2 means y1 should < y2
# distance in range of 0 to 100
def over_head_score(y1, y2, weight):
    max_distance = math.sqrt(pow(m['preds'][i-1][6][1]-m['preds'][i-1][9][1], 2)+pow(m['preds'][i-1][6][0]-m['preds'][i-1][9][0], 2))
    distance = (y2 - y1)/max_distance*100
    if distance < 0:
        return -0.1*weight*distance
    return 0

def vertical_score(y1, y2, x1, x2, weight):
        angle = abs(math.atan(abs(y1 - y2)/abs(x1 - x2)))
        if (x1 == x2):
            angle = abs(math.atan(abs(y1 - y2) / 0.0001))
        if(abs(angle)<=0.125):
            return 0
        return weight*(abs(angle)-0.125)


def distance_score(y1, y2, x1, x2, weight):
    p1x = m['preds'][i-1][6][0]
    p1y = m['preds'][i-1][6][1]
    p2x = m['preds'][i-1][7][0]
    p2y = m['preds'][i-1][7][1]
    max_distance = math.sqrt(pow(m['preds'][i-1][7][1]-m['preds'][i-1][9][1], 2)+pow(m['preds'][i-1][7][0]-m['preds'][i-1][9][0], 2))
    safe_distance = 0.2*math.sqrt(pow(p2x - p1x, 2) + pow(p2y - p1y, 2)) / max_distance * 100
    distance = math.sqrt(pow(y1-y2, 2)+pow(x1-x2, 2))/max_distance * 100
    if(distance <= safe_distance):
        return 0
    ans = weight*(distance-safe_distance)
    return ans

def level_score(y1, y2, x1, x2, weight):
        angle = abs(math.atan(abs(x1-x2)/abs(y1-y2)))
        if (y1 == y2):
            angle = abs(math.atan(abs(x1-x2)/0.0001))
        if(angle <= 0.125):
           return 0
        return weight*(abs(angle)-0.125)

def arm_line_score(weight):
    v1x = m['preds'][i-1][11][0] - m['preds'][i-1][12][0]
    v2x = m['preds'][i-1][10][0] - m['preds'][i-1][12][0]
    v1y = m['preds'][i-1][11][1] - m['preds'][i-1][12][1]
    v2y = m['preds'][i-1][10][1] - m['preds'][i-1][12][1]
    tmp_angle = abs(math.acos((v1x*v2x+v1y*v2y)/(math.sqrt(pow(v1x, 2)+pow(v1y, 2))*math.sqrt(pow(v2x, 2)+pow(v2y, 2)))))
    safe_angle = 0.125
    if tmp_angle > safe_angle:
        return abs(tmp_angle-safe_angle)*weight
    return 0


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
    '''
    for j in range(1,i):
        cv2.line(img, ((int)(m['preds'][j - 1][10][0]), (int)(m['preds'][j - 1][10][1])), ((int)(m['preds'][j][10][0]), (int)(m['preds'][j][10][1])), (0, 255, 0), 2)
    '''

    #Line
    cv2.line(img,((int)(m['preds'][i-1][7][0]),(int)(m['preds'][i-1][7][1])),((int)(m['preds'][i-1][8][0]),(int)(m['preds'][i-1][8][1])),(0,255,0),2)
    cv2.line(img,((int)(m['preds'][i-1][13][0]),(int)(m['preds'][i-1][13][1])),((int)(m['preds'][i-1][14][0]),(int)(m['preds'][i-1][14][1])),(0,255,0),2)
    cv2.line(img,((int)(m['preds'][i-1][14][0]),(int)(m['preds'][i-1][14][1])),((int)(m['preds'][i-1][15][0]),(int)(m['preds'][i-1][15][1])),(0,255,0),2)
    cv2.line(img,((int)(m['preds'][i-1][10][0]),(int)(m['preds'][i-1][10][1])),((int)(m['preds'][i-1][11][0]),(int)(m['preds'][i-1][11][1])),(0,255,0),2)
    cv2.line(img,((int)(m['preds'][i-1][11][0]),(int)(m['preds'][i-1][11][1])),((int)(m['preds'][i-1][12][0]),(int)(m['preds'][i-1][12][1])),(0,255,0),2)
    cv2.line(img,((int)(m['preds'][i-1][7][0]),(int)(m['preds'][i-1][7][1])),((int)(m['preds'][i-1][12][0]),(int)(m['preds'][i-1][12][1])),(0,255,0),2)
    cv2.line(img,((int)(m['preds'][i-1][7][0]),(int)(m['preds'][i-1][7][1])),((int)(m['preds'][i-1][13][0]),(int)(m['preds'][i-1][13][1])),(0,255,0),2)
    cv2.line(img,((int)(m['preds'][i-1][10][0]),(int)(m['preds'][i-1][10][1])),((int)(m['preds'][i-1][11][0]),(int)(m['preds'][i-1][11][1])),(0,255,0),2)
    cv2.line(img,((int)(m['preds'][i-1][8][0]),(int)(m['preds'][i-1][8][1])),((int)(m['preds'][i-1][9][0]),(int)(m['preds'][i-1][9][1])),(0,255,0),2)
    cv2.line(img,((int)(m['preds'][i-1][7][0]),(int)(m['preds'][i-1][7][1])),((int)(m['preds'][i-1][6][0]),(int)(m['preds'][i-1][6][1])),(0,255,0),2)
    cv2.line(img,((int)(m['preds'][i-1][2][0]),(int)(m['preds'][i-1][2][1])),((int)(m['preds'][i-1][6][0]),(int)(m['preds'][i-1][6][1])),(0,255,0),2)
    cv2.line(img,((int)(m['preds'][i-1][3][0]),(int)(m['preds'][i-1][3][1])),((int)(m['preds'][i-1][6][0]),(int)(m['preds'][i-1][6][1])),(0,255,0),2)
        #kuan dao xi
    if ((m['preds'][i - 1][3][1]) < (m['preds'][i - 1][4][1])):
        cv2.line(img,((int)(m['preds'][i-1][3][0]),(int)(m['preds'][i-1][3][1])),((int)(m['preds'][i-1][4][0]),(int)(m['preds'][i-1][4][1])),(0,255,0),2)
    if ((m['preds'][i - 1][2][1]) < (m['preds'][i - 1][1][1])):
        cv2.line(img,((int)(m['preds'][i-1][2][0]),(int)(m['preds'][i-1][2][1])),((int)(m['preds'][i-1][1][0]),(int)(m['preds'][i-1][1][1])),(0,255,0),2)
        #xi dao jio
    if ((m['preds'][i - 1][4][1]) < (m['preds'][i - 1][5][1])):
        cv2.line(img,((int)(m['preds'][i-1][5][0]),(int)(m['preds'][i-1][5][1])),((int)(m['preds'][i-1][4][0]),(int)(m['preds'][i-1][4][1])),(0,255,0),2)
    if ((m['preds'][i - 1][1][1]) < (m['preds'][i - 1][0][1])):
        cv2.line(img,((int)(m['preds'][i-1][0][0]),(int)(m['preds'][i-1][0][1])),((int)(m['preds'][i-1][1][0]),(int)(m['preds'][i-1][1][1])),(0,255,0),2)
    #Point
    for j in range(16):
        print(j,m['preds'][i-1][j][0],m['preds'][i-1][j][1])
        cv2.circle(img, ((int)(m['preds'][i-1][j][0]),(int)(m['preds'][i-1][j][1])), 10, point_color, 1)
        cv2.putText(img,str(j),((int)(m['preds'][i-1][j][0]),(int)(m['preds'][i-1][j][1])),cv2.FONT_HERSHEY_COMPLEX, 0.4,(255,255,255),1)
    '''
    #Score for Archery
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
    '''

    #Score for gymnastics
    gymnastics_score={1:100,2:100,3:100,4:100}
    gymnastics_d={1:[],2:[],3:[],4:[]}

    #pose_1
    gymnastics_score = {1: 100.0, 2: 100.0, 3: 100.0, 4: 100.0}
    gymnastics_d = {1: [], 2: [], 3: [], 4: []}
    wei = {1:30,2:0.55,3:15,4:10.0}
    gymnastics_d[1].append(vertical_score(m['preds'][i-1][1][0],  m['preds'][i-1][2][0], m['preds'][i-1][1][1], m['preds'][i-1][2][1], wei[1]))
    gymnastics_d[1].append(vertical_score(m['preds'][i-1][4][0],  m['preds'][i-1][3][0], m['preds'][i-1][4][1], m['preds'][i-1][3][1], wei[1]))
    gymnastics_d[1].append(vertical_score(m['preds'][i-1][11][0],  m['preds'][i-1][10][0], m['preds'][i-1][11][1], m['preds'][i-1][10][1], wei[1]))
    gymnastics_d[1].append(vertical_score(m['preds'][i-1][15][0],  m['preds'][i-1][14][0], m['preds'][i-1][15][1], m['preds'][i-1][14][1], wei[1]))
    gymnastics_d[1].append(vertical_score(m['preds'][i-1][9][0],  m['preds'][i-1][7][0], m['preds'][i-1][9][1], m['preds'][i-1][7][1], wei[1]))
    for value in gymnastics_d[1]:
        if (math.isnan(value) is False):
            gymnastics_score[1] -= value
    gymnastics_score[1]=relu(gymnastics_score[1])
    
    #pose_2
    gymnastics_d[2].append(distance_score(m['preds'][i-1][11][0],  m['preds'][i-1][12][0], m['preds'][i-1][11][1], m['preds'][i-1][12][1], wei[2]))
    gymnastics_d[2].append(distance_score(m['preds'][i-1][13][0],  m['preds'][i-1][14][0], m['preds'][i-1][13][1], m['preds'][i-1][14][1], wei[2]))
    gymnastics_d[2].append(distance_score(m['preds'][i-1][11][0],  m['preds'][i-1][10][0], m['preds'][i-1][11][1], m['preds'][i-1][10][1], wei[2]))
    gymnastics_d[2].append(distance_score(m['preds'][i-1][15][0],  m['preds'][i-1][14][0], m['preds'][i-1][15][1], m['preds'][i-1][14][1], wei[2]))
    gymnastics_d[2].append(distance_score(m['preds'][i-1][12][0],  m['preds'][i-1][10][0], m['preds'][i-1][12][1], m['preds'][i-1][10][1], wei[2]))
    gymnastics_d[2].append(distance_score(m['preds'][i-1][15][0],  m['preds'][i-1][13][0], m['preds'][i-1][15][1], m['preds'][i-1][13][1], wei[2]))
    gymnastics_d[2].append(vertical_score(m['preds'][i-1][1][0],  m['preds'][i-1][2][0], m['preds'][i-1][1][1], m['preds'][i-1][2][1], wei[1]))
    gymnastics_d[2].append(vertical_score(m['preds'][i-1][4][0],  m['preds'][i-1][3][0], m['preds'][i-1][4][1], m['preds'][i-1][3][1], wei[1]))
    for value in gymnastics_d[2]:
        if (math.isnan(value) is False):
            gymnastics_score[2] -= value
    gymnastics_score[2]=relu(gymnastics_score[2])

    #pose_3
    gymnastics_d[3].append(level_score(m['preds'][i-1][11][0],  m['preds'][i-1][12][0], m['preds'][i-1][11][1], m['preds'][i-1][12][1], wei[3]))
    gymnastics_d[3].append(level_score(m['preds'][i-1][13][0],  m['preds'][i-1][14][0], m['preds'][i-1][13][1], m['preds'][i-1][14][1], wei[3]))
    gymnastics_d[3].append(level_score(m['preds'][i-1][13][0],  m['preds'][i-1][12][0], m['preds'][i-1][13][1], m['preds'][i-1][12][1], wei[3]*5))
    gymnastics_d[3].append(level_score(m['preds'][i-1][10][0],  m['preds'][i-1][11][0], m['preds'][i-1][10][1], m['preds'][i-1][11][1], wei[3]))
    gymnastics_d[3].append(level_score(m['preds'][i-1][14][0],  m['preds'][i-1][15][0], m['preds'][i-1][14][1], m['preds'][i-1][15][1], wei[3]))
    gymnastics_d[3].append(vertical_score(m['preds'][i-1][1][0],  m['preds'][i-1][2][0], m['preds'][i-1][1][1], m['preds'][i-1][2][1], wei[1]))
    gymnastics_d[3].append(vertical_score(m['preds'][i-1][4][0],  m['preds'][i-1][3][0], m['preds'][i-1][4][1], m['preds'][i-1][3][1], wei[1]))
    gymnastics_d[3].append(relu(topangle_socre(wei[3]*1.5)-15)*2)
    for value in gymnastics_d[3]:
        if (math.isnan(value) is False):
            gymnastics_score[3] -= value
    gymnastics_score[3]=relu(gymnastics_score[3])

    #pose_4
    gymnastics_d[4].append(arm_line_score(wei[4]*7))
    gymnastics_d[4].append(over_head_score(m['preds'][i-1][11][1],m['preds'][i-1][12][1],wei[4]*2))
    gymnastics_d[4].append(over_head_score(m['preds'][i-1][11][1],m['preds'][i-1][9][1],wei[4]*0.5))
    gymnastics_d[4].append(relu(bend_score(m['preds'][i-1][9][0],  m['preds'][i-1][7][0],m['preds'][i-1][9][1],  m['preds'][i-1][7][1],wei[4]*3)))
    gymnastics_d[4].append(relu(bend_score(m['preds'][i-1][6][0],  m['preds'][i-1][7][0],m['preds'][i-1][6][1],  m['preds'][i-1][7][1],wei[4]*3)))
    for value in gymnastics_d[4]:
            if (math.isnan(value) is False):
                gymnastics_score[4] -= value
    gymnastics_score[4]=relu(gymnastics_score[4])

    print(i,gymnastics_d[4])
    cv2.putText(img,'Pose1: %.2f' % gymnastics_score[1],(450,50), cv2.FONT_HERSHEY_COMPLEX, 0.7,(255,255,20),2)
    cv2.putText(img,'Pose2: %.2f' % gymnastics_score[2],(450,80), cv2.FONT_HERSHEY_COMPLEX, 0.7,(255,255,20),2)
    cv2.putText(img,'Pose3: %.2f' % gymnastics_score[3],(450,110), cv2.FONT_HERSHEY_COMPLEX, 0.7,(255,255,20),2)
    cv2.putText(img,'Pose4: %.2f' % gymnastics_score[4],(450,140), cv2.FONT_HERSHEY_COMPLEX, 0.7,(255,255,20),2)
    cate = pose_name[max(zip(gymnastics_score.values(),gymnastics_score.keys()))[1]]
    cv2.putText(img,cate,(20,40), cv2.FONT_HERSHEY_COMPLEX, 1.2,(255,255,20),3)

    #save best
    for pose in range(1,5):
        if (gymnastics_score[pose]>best[pose]):
            best[pose]=gymnastics_score[pose]
            best_index[pose]=i
            best_list[pose]=gymnastics_d[pose]
    cv2.imwrite('C:\\Users\\cityscience\\Desktop\\1\\checkpoint\\mpii\\new\\output\\'+str(i)+'.png',img)

object = open("C:\\Users\\cityscience\\Documents\\bowbow\\judge\\bestpose.txt", "w")
object.write("");
object.close();
object = open("C:\\Users\\cityscience\\Documents\\bowbow\\judge\\bestpose.txt", "a")
for i in range(1,5):
    object.write('%.2f\n' % best[i])
    object.write(str(best_index[i])+'\n')
    for item in best_list[i]:
        object.write('%.2f\n' % item)
object.close()
