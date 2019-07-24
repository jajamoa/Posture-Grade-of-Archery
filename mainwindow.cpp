#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <opencv2\opencv.hpp>
#include <QImage>
#include <Qmovie>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <Winbase.h>
#include <MMsystem.h>
#include <QThread>
#include <QDebug>
#include <QTime>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <string>
#include <shellapi.h>
#include <fstream>>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "WINMM.LIB")



//thread test
class MyThread : public QThread {
     public:
         virtual void run();
     };

     void MyThread::run()
     {
         for( int count = 0; count < 20; count++ ) {
             sleep( 1 );
             qDebug( "Ping!" );
         }
     }

void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::bow()
{
    cur_sport=1;
    greeting();
}
void MainWindow::gymn()
{
    cur_sport=2;
    greeting();
}
void MainWindow::shot()
{
    cur_sport=3;
    greeting();
}
void MainWindow::badm()
{
    cur_sport=4;
    greeting();
}

void MainWindow::changeBg(int index)
{
    char temp[] = "";
    sprintf(temp,"%d",index);
    std::string si(temp);
    ui->stackedWidget->setCurrentIndex(0);
    cv::Mat frame=cv::imread("C:\\Users\\jsjtx\\Desktop\\bowbow\\Resources\\bg\\"+si+".jpg");
    QPixmap pixmap = QPixmap::fromImage(MatToQImage(frame));
    int with = ui->bg->width();
    int height = ui->bg->height();
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->bg->setPixmap(fitpixmap);
}

void MainWindow::changeBg2(int index)
{
    char temp[] = "";
    sprintf(temp,"%d",index);
    std::string si(temp);
    ui->stackedWidget->setCurrentIndex(0);
    cv::Mat frame=cv::imread("C:\\Users\\jsjtx\\Desktop\\bowbow\\Resources\\bg\\"+si+".jpg");
    QPixmap pixmap = QPixmap::fromImage(MatToQImage(frame));
    int with = ui->bg->width();
    int height = ui->bg->height();
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->bg_2->setPixmap(fitpixmap);
}


void MainWindow::loadFvideos()
{
    cv::Mat frame=cv::imread("C://Users//jsjtx//Desktop//bowbow//Resources//video//1.png");
    QPixmap pixmap = QPixmap::fromImage(MatToQImage(frame));
    int with = ui->video1->width();
    int height = ui->video1->height();
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->video1->setPixmap(fitpixmap);

    frame=cv::imread("C://Users//jsjtx//Desktop//bowbow//Resources//video//2.png");
    pixmap = QPixmap::fromImage(MatToQImage(frame));
    with = ui->video2->width();
    height = ui->video2->height();
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->video2->setPixmap(fitpixmap);

    frame=cv::imread("C://Users//jsjtx//Desktop//bowbow//Resources//video//3.png");
    pixmap = QPixmap::fromImage(MatToQImage(frame));
    with = ui->video3->width();
    height = ui->video3->height();
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->video3->setPixmap(fitpixmap);

    frame=cv::imread("C://Users//jsjtx//Desktop//bowbow//Resources//video//4.png");
    pixmap = QPixmap::fromImage(MatToQImage(frame));
    with = ui->video4->width();
    height = ui->video4->height();
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->video4->setPixmap(fitpixmap);

    ui->video1->hide();
    ui->video2->hide();
    ui->video3->hide();
    ui->video4->hide();
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    //available ports
    QStringList m_serialPortName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        m_serialPortName << info.portName();
        qDebug()<<"serialPortName:"<<info.portName();
    }

    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    palette.setColor(QPalette::Text, Qt::black);
    palette.setColor(QPalette::WindowText, Qt::black);
    this->setPalette(palette);

    serial = new QSerialPort;
    serial->setPortName("COM7");
    serial->open(QIODevice::ReadWrite);
    serial->setBaudRate(QSerialPort::Baud9600);

    count = 0;
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(waitSelection()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(breakLoop()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(report()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(grade()));
    //connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(testTwoCam()));

    changeBg(1);
    ui->bg_2->hide();
    changeBg2(2);

    QMovie *movie1 = new QMovie("C:\\Users\\jsjtx\\Desktop\\bowbow\\Resources\\greeting1.gif");
    ui->label1->setMovie(movie1);
    movie1->start();
    QMovie *movie2 = new QMovie("C:\\Users\\jsjtx\\Desktop\\bowbow\\Resources\\greeting2.gif");
    ui->label2->setMovie(movie2);
    movie2->start();
    ui->progressBar->setMaximum(589);
    ui->progressBar->setValue(0);
    ui->progressBar->hide();
    ui->label1->hide();
    ui->label2->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->label_report->hide();
    ui->estlabel->hide();
    ui->est->hide();

    ui->label_report_2->hide();
    ui->estlabel_2->hide();
    ui->label_report_3->hide();
    ui->label_report_4->hide();
    ui->label_report_5->hide();
    ui->label_report_6->hide();
    ui->label_report_7->hide();

    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->standard->hide();
    ui->pose1->hide();
    ui->pose2->hide();
    ui->pose3->hide();
    ui->pose4->hide();
    ui->label->hide();
    ui->score->hide();
    ui->score_2->hide();
    //gymn
    ui->poseA->hide();
    ui->poseB->hide();
    ui->poseC->hide();
    ui->poseD->hide();
    ui->G1->hide();
    ui->G2->hide();
    ui->G3->hide();
    ui->G4->hide();
    ui->Gt->hide();

    loadFvideos();

    WinExec("C:\\Users\\jsjtx\\Desktop\\bowbow\\Message\\init.bat",0);
    sleep(100);
    connect(timer7, SIGNAL(timeout()), this, SLOT(checkM()));
    timer7->start(500);

    //train();
    //changeBg2(7);
    //success();
}

void MainWindow::checkM()
{
    std::string temp;
    std::ifstream OpenFile("C://Users//jsjtx//Desktop//bowbow//Message//1.txt");
    OpenFile >> temp;
    if (temp=="0" && !started) {
        started = true;
        timer7->stop();
        waitSelection();
    }
    if (temp=="3" && !choosed && started) {
        choosed = true;
        timer8->stop();
        bow();
    }
    if (temp=="1" && !choosed && started) {
        choosed = true;
        timer8->stop();
        badm();
    }
    if (temp=="2" && !choosed && started) {
        choosed = true;
        timer8->stop();
        gymn();
    }
    if (temp=="4" && !choosed && started) {
        choosed = true;
        timer8->stop();
        shot();
    }
    if (temp=="5" && !selftested && started && choosed) {
        selftested = true;
        if (cur_sport == 1) ui->video1->hide();
        if (cur_sport == 2) ui->video2->hide();
        if (cur_sport == 3) ui->video3->hide();
        if (cur_sport == 4) ui->video4->hide();
        timer9->stop();
        breakLoop();
    }
    if (temp=="6" && selftested && started && choosed) {
        timer10->stop();
        train();
    }
    OpenFile.close();
}

void MainWindow::waitSelection()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->bg_2->show();
    sleep(100);
    changeBg(3);
    int mode;
    WinExec("C:\\Users\\jsjtx\\Desktop\\bowbow\\Message\\init.bat",0);
    sleep(100);
    connect(timer8, SIGNAL(timeout()), this, SLOT(checkM()));
    timer8->start(500);
}

void MainWindow::greeting()
{
    ui->bg_2->hide();
    if (cur_sport == 1) ui->video1->show();
    if (cur_sport == 2) ui->video2->show();
    if (cur_sport == 3) ui->video3->show();
    if (cur_sport == 4) ui->video4->show();
    sleep(100);
    changeBg2(8);
    WinExec("C:\\Users\\jsjtx\\Desktop\\bowbow\\Message\\init.bat",0);
    sleep(100);
    connect(timer9, SIGNAL(timeout()), this, SLOT(checkM()));
    timer9->start(500);
    //ui->label_2->setText("射箭");
    PlaySound(TEXT("C:\\Users\\jsjtx\\Desktop\\bowbow\\Resources\\1greeting.wav"),NULL,SND_FILENAME | SND_ASYNC);
    //sleep(5*1000);
    /*
    connect(timer, SIGNAL(timeout()), this, SLOT(waitReady()));
    timer->start(7000);


    int X=0;
    QByteArray buf;
    buf = serial->readAll();
    buf.clear();
    while (1){
        ++X;
        if (X>1000) break;
        QString str;
        buf = serial->readAll();
        if(!buf.isEmpty()) qDebug()<<buf;
        str=buf;
        if (str.indexOf('.')>=3 && str[0]!='-') {
            qDebug()<<"!!!";
            break;
        }
        buf.clear();
        sleep(1000);
    }
    serial->clear();
    serial->close();
    serial->deleteLater();
    */
    //breakLoop();
}

void MainWindow::waitReady()
{
    PlaySound(TEXT("C:\\Users\\jsjtx\\Desktop\\bowbow\\Resources\\2ready.wav"),NULL,SND_FILENAME | SND_ASYNC);
}

void MainWindow::waitJudge()
{
    PlaySound(TEXT("C:\\Users\\jsjtx\\Desktop\\bowbow\\Resources\\4judge.wav"),NULL,SND_FILENAME | SND_ASYNC);
}

void MainWindow::breakLoop()
{
    timer->stop();
    ui->bg_2->show();
    ui->progressBar->show();
    sleep(100);
    changeBg(9);
    //ui->label1->show();
    //ui->label2->show();
    PlaySound(TEXT("C:\\Users\\jsjtx\\Desktop\\bowbow\\Resources\\3start.wav"),NULL,SND_FILENAME | SND_ASYNC);
    sleep(7000);
    connect(timer2, SIGNAL(timeout()), this, SLOT(barUpdate()));
    timer2->start(200);
    //ui->stackedWidget->setCurrentIndex(3);
    savePics();
}

void MainWindow::barUpdate()
{
    if (ui->progressBar->value()<589) {
        ui->progressBar->setValue(ui->progressBar->value()+589/50);
    }
    else timer2->stop();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gradeBarUpdate()
{
    std::string str;
    std::ifstream OpenFile("C:\\Users\\jsjtx\\Desktop\\bowbow\\judge\\judgeProgress.txt");
    OpenFile >> str;
    OpenFile.close();
    ui->progressBar->setValue(atoi(str.c_str()));
    if ((atoi(str.c_str()))==589) {
        ui->progressBar->hide();
        report();
    }
}

void MainWindow::grade()
{
    //Change GUI
    //ui->label->hide();
    //ui->label2->hide();
    //ui->label1->hide();
    //ui->est->show();
    //ui->estlabel->show();
    //ui->progressBar->show();
    //ui->progressBar->setValue(0);
    //ui->estlabel->hide();
    //ui->progressBar->move(280,330);
    //ui->stackedWidget->setCurrentIndex(3);

    changeBg2(10);

    //play sound
    waitJudge();
    connect(timer5, SIGNAL(timeout()), this, SLOT(waitJudge()));
    timer5->start(7000);

    //save imgs
    if (!his.empty())for (int i=1;i<50;++i){
        if (i==1) ui->bg_2->hide();
        std::string res;
        std::stringstream ss;
        ss << i;
        res = ss.str();
        ui->progressBar->setValue(i);
        cv::imwrite("C:\\Users\\jsjtx\\Desktop\\1\\data\\mpii\\images\\"+res+".jpg",his[i]);
        cv::imwrite("C:\\Users\\jsjtx\\Desktop\\1\\checkpoint\\mpii\\new\\input\\"+res+".jpg",his[i]);
    }

    //Start bar

    std::ofstream OpenFile("C:\\Users\\jsjtx\\Desktop\\bowbow\\judge\\judgeProgress.txt");
    OpenFile << "50";
    OpenFile.close();
    connect(timer3, SIGNAL(timeout()), this, SLOT(gradeBarUpdate()));
    timer3->start(50);

    //start judge
    //system("C:\\Users\\jsjtx\\Desktop\\bowbow\\judge.bat");
    if (cur_sport==1) WinExec("C:\\Users\\jsjtx\\Desktop\\bowbow\\judge\\judge1.bat",0);
    if (cur_sport==2) WinExec("C:\\Users\\jsjtx\\Desktop\\bowbow\\judge\\judge2.bat",0);
    if (cur_sport==3) WinExec("C:\\Users\\jsjtx\\Desktop\\bowbow\\judge\\judge3.bat",0);
    if (cur_sport==4) WinExec("C:\\Users\\jsjtx\\Desktop\\bowbow\\judge\\judge4.bat",0);
}

void MainWindow::display()
{
    curPicIndex++;
    if (curPicIndex>=50) curPicIndex=1;
    std::string res;
    std::stringstream ss;
    ss << curPicIndex;
    res = ss.str();
    cv::Mat frame=cv::imread("C:\\Users\\jsjtx\\Desktop\\1\\checkpoint\\mpii\\new\\output\\"+res+".png");
    QPixmap pixmap = QPixmap::fromImage(MatToQImage(frame));
    int with = ui->estlabel_2->width();
    int height = ui->estlabel_2->height();
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->estlabel_2->setPixmap(fitpixmap);
}

QString str2qstr(const std::string str)
{
    return QString::fromLocal8Bit(str.data());
}

void MainWindow::success()
{
    QPalette pe;

    srand((unsigned)time(NULL));
    int score=(78+rand()%20);
    std::ofstream OpenFile("C:\\Users\\jsjtx\\Desktop\\bowbow\\Message\\2.txt");
    OpenFile << score;
    OpenFile.close();

    pe.setColor(QPalette::WindowText,Qt::white);
    ui->score_2->setPalette(pe);
    ui->score_2->setText(str2qstr(std::to_string(score)));
    ui->score_2->show();
    ui->score->hide();
    ui->video1->hide();
    ui->bg_2->show();
}

void MainWindow::traindisplay()
{
    int count[5]={0,41,0,0,0};
    curPicIndex++;
    if (curPicIndex>=count[cur_sport]) {
        curPicIndex=1;
        if (cirNum) {
            cirNum--;
            ui->score->setText(str2qstr(scores[assCirNum - cirNum -1]));
            qDebug() << str2qstr(scores[assCirNum - cirNum -1]);
        }
        else {
            timer6->stop();
            success();
        }
    }

    std::string res,ress;
    std::stringstream ss,sss;
    ss << curPicIndex;
    res = ss.str();
    sss << cur_sport;
    ress = sss.str();
    cv::Mat frame=cv::imread("C:\\Users\\jsjtx\\Desktop\\bowbow\\Resources\\"+ress+"\\"+res+".jpg");
    QPixmap pixmap = QPixmap::fromImage(MatToQImage(frame));
    int with = ui->video1->width();
    int height = ui->video1->height();
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->video1->setPixmap(fitpixmap);
}


void MainWindow::report()
{
    //changeBg2(10);
    changeBg(5);
    //cur_sport=2;
    ui->bg_2->show();
    //stop timer
    timer3->stop();
    timer5->stop();
    //change GUI
    ui->stackedWidget->setCurrentIndex(4);
    ui->progressBar->hide();
    ui->label_report->show();
    ui->label->hide();
    ui->label1->hide();
    ui->label2->hide();
    ui->estlabel->hide();
    ui->est->hide();
    ui->estlabel_2->show();
    if (cur_sport==1) {
        ui->label_report_2->show();
        ui->label_report_3->show();
        ui->label_report_4->show();
        ui->label_report_5->show();
        ui->label_report_6->show();
        ui->label_report_7->show();
    }
    if (cur_sport==2) {
        loadGymCap();
        ui->poseA->show();
        ui->poseB->show();
        ui->poseC->show();
        ui->poseD->show();
        ui->G1->show();
        ui->G2->show();
        ui->G3->show();
        ui->G4->show();
        ui->Gt->show();
    }

    //ui->pushButton_5->show();
    //ui->pushButton_6->show();
    //ui->pushButton_7->show();



    //report 2 content (Review active)
    curPicIndex=1;
    connect(timer4, SIGNAL(timeout()), this, SLOT(display()));
    timer4->start(200);

    //report 1 content
    std::string res,index,score;
    std::stringstream ss;
    std::ifstream OpenFile("C:\\Users\\jsjtx\\Desktop\\bowbow\\judge\\bestpose.txt");
    OpenFile >> score >> index;
    cv::Mat frame=cv::imread("C:\\Users\\jsjtx\\Desktop\\1\\checkpoint\\mpii\\new\\output\\"+index+".png");
    QPixmap pixmap = QPixmap::fromImage(MatToQImage(frame));
    int with = ui->estlabel_2->width();
        int height = ui->estlabel_2->height();
        //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
        QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->estlabel_2->setPixmap(fitpixmap);
    std::string content;
    ui->label_report_2->setText(ui->label_report_2->text()+str2qstr(score+"/100"));
    OpenFile >> score;
    ui->label_report_3->setText(ui->label_report_3->text()+str2qstr(score));
    OpenFile >> score;
    ui->label_report_4->setText(ui->label_report_4->text()+str2qstr(score));
    OpenFile >> score;
    ui->label_report_5->setText(ui->label_report_5->text()+str2qstr(score));
    OpenFile >> score;
    ui->label_report_6->setText(ui->label_report_6->text()+str2qstr(score));
    OpenFile >> score;
    ui->label_report_7->setText(ui->label_report_7->text()+str2qstr(score));

    //report 3 content
    //QMovie *movie3 = new QMovie("C:\\Users\\jsjtx\\Desktop\\bowbow\\Resources\\greeting3.gif");
    //movie3->setScaledSize(ui->standard->size());
    //ui->standard->setMovie(movie3);
    //movie3->start();
    //connect(timer6, SIGNAL(timeout()), this, SLOT(adjustSpeed()));
    //timer6->start(200);


    //label_report_2
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(report1()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(report2()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(report3()));

    WinExec("C:\\Users\\jsjtx\\Desktop\\bowbow\\Message\\init.bat",0);
    sleep(100);
    connect(timer10, SIGNAL(timeout()), this, SLOT(checkM()));
    timer10->start(500);
}

void MainWindow::train()
{
    //QMovie *movie = new QMovie("C:\\Users\\jsjtx\\Desktop\\bowbow\\Resources\\greeting3.gif");
    //movie->setScaledSize(ui->video1->size());
    //ui->video1->setMovie(movie);
    //movie->start();
    std::string str;
    std::ifstream CirFile("C:\\Users\\jsjtx\\Desktop\\bowbow\\judge\\trainscore.txt");
    CirFile >> str;
    cirNum=atoi(str.c_str());
    assCirNum=cirNum;
    qDebug() << atoi(str.c_str());
    for (int i=0;i<cirNum;++i) {
        CirFile >> str;
        scores[i]=str;
    }
    CirFile.close();

    ui->score->show();
    curPicIndex=1;
    connect(timer6, SIGNAL(timeout()), this, SLOT(traindisplay()));
    timer6->start(200);

    sleep(300);
    timer4->stop();
    ui->estlabel_2->hide();
    ui->bg_2->hide();
    ui->video1->move(127,220);
    ui->video1->show();
    changeBg2(7);
}

void MainWindow::adjustSpeed()
{
    if (ui->video1->isVisible())
        movie->setSpeed(100);
}

void MainWindow::report1()
{
    ui->stackedWidget->setCurrentIndex(4);

    ui->estlabel->hide();
    ui->estlabel_2->show();
    ui->label_report_2->show();
    ui->label_report_3->show();
    ui->label_report_4->show();
    ui->label_report_5->show();
    ui->label_report_6->show();
    ui->label_report_7->show();
    ui->standard->hide();
    ui->label_report->show();
}

void MainWindow::report2()
{
    ui->stackedWidget->setCurrentIndex(5);

    ui->estlabel->show();
    ui->estlabel_2->hide();
    ui->label_report_2->hide();
    ui->label_report_3->hide();
    ui->label_report_4->hide();
    ui->label_report_5->hide();
    ui->label_report_6->hide();
    ui->label_report_7->hide();
    ui->standard->hide();
    ui->label_report->show();
}

void MainWindow::report3()
{
    ui->stackedWidget->setCurrentIndex(6);

    ui->estlabel->hide();
    ui->estlabel_2->hide();
    ui->label_report_2->hide();
    ui->label_report_3->hide();
    ui->label_report_4->hide();
    ui->label_report_5->hide();
    ui->label_report_6->hide();
    ui->label_report_7->hide();
    ui->label_report->hide();
    ui->standard->show();
}

void MainWindow::savePics()
{
    //cv::VideoCapture capture(0);
    cv::VideoCapture capture(1);
    while (1) {
        count++;
        cv::Mat frame;
        capture >> frame;
        his.push_back(frame);
        cv::imshow("1",frame);
        cv::waitKey(200);
        if (count==50) {
            timer2->stop();
            break;
        }
    }
    cv::destroyAllWindows();
    grade();
}

void MainWindow::testTwoCam()
{
    cv::VideoCapture capture1(0);
    cv::VideoCapture capture2(1);

    while (1) {
        cv::Mat frame1,frame2;
        capture1 >> frame1;
        capture2 >> frame2;
        cv::imshow("1",frame1);
        cv::imshow("2",frame2);
        cv::waitKey(100);
    }
}

LPCWSTR stringToLPCWSTR(std::string orig)
{
    size_t origsize = orig.length() + 1;
        const size_t newsize = 100;
        size_t convertedChars = 0;
    wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length()-1));
    mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

    return wcstring;
}

QImage MainWindow::MatToQImage(cv::Mat mtx)
{
    switch (mtx.type())
    {
    case CV_8UC1:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols, QImage::Format_Grayscale8);
            return img;
        }
    case CV_8UC3:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 3, QImage::Format_RGB888);
            return img.rgbSwapped();
        }
    case CV_8UC4:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 4, QImage::Format_ARGB32);
            return img;
        }
    default:
        {
            QImage img;
            return img;
        }
    }
}


void MainWindow::loadGymCap()
{
    std::string res,index,score;
    std::stringstream ss;
    std::ifstream OpenFile("C:\\Users\\jsjtx\\Desktop\\bowbow\\judge\\bestpose.txt");
    OpenFile >> score;
    ui->Gt->setText(ui->Gt->text()+str2qstr(score+"/100"));

    OpenFile >> score;
    ui->G1->setText(ui->G1->text()+str2qstr(score));
    OpenFile >> index;
    cv::Mat frame=cv::imread("C:\\Users\\jsjtx\\Desktop\\1\\checkpoint\\mpii\\new\\output\\"+index+".png");
    QPixmap pixmap = QPixmap::fromImage(MatToQImage(frame));
    int with = ui->poseA->width();
    int height = ui->poseA->height();
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->poseA->setPixmap(fitpixmap);

    OpenFile >> score;
    ui->G2->setText(ui->G2->text()+str2qstr(score));
    OpenFile >> index;
    frame=cv::imread("C:\\Users\\jsjtx\\Desktop\\1\\checkpoint\\mpii\\new\\output\\"+index+".png");
    pixmap = QPixmap::fromImage(MatToQImage(frame));
    with = ui->poseB->width();
    height = ui->poseB->height();
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->poseB->setPixmap(fitpixmap);

    OpenFile >> score;
    ui->G3->setText(ui->G3->text()+str2qstr(score));
    OpenFile >> index;
    frame=cv::imread("C:\\Users\\jsjtx\\Desktop\\1\\checkpoint\\mpii\\new\\output\\"+index+".png");
    pixmap = QPixmap::fromImage(MatToQImage(frame));
    with = ui->poseC->width();
    height = ui->poseC->height();
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->poseC->setPixmap(fitpixmap);

    OpenFile >> score;
    ui->G4->setText(ui->G4->text()+str2qstr(score));
    OpenFile >> index;
    frame=cv::imread("C:\\Users\\jsjtx\\Desktop\\1\\checkpoint\\mpii\\new\\output\\"+index+".png");
    pixmap = QPixmap::fromImage(MatToQImage(frame));
    with = ui->poseD->width();
    height = ui->poseD->height();
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->poseD->setPixmap(fitpixmap);
    OpenFile.close();
}
