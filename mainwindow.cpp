#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2\opencv.hpp>
#include <QImage>
#include <Qmovie>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <MMsystem.h>
#include <QThread>
#include <QDebug>
#include <QTime>
#pragma comment(lib, "WINMM.LIB")

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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    count = 0;
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(greeting()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(breakLoop()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(report()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(grade()));
    QMovie *movie1 = new QMovie("C:\\Users\\cityscience\\Documents\\bowbow\\Resources\\greeting1.gif");
    ui->label1->setMovie(movie1);
    movie1->start();
    QMovie *movie2 = new QMovie("C:\\Users\\cityscience\\Documents\\bowbow\\Resources\\greeting2.gif");
    ui->label2->setMovie(movie2);
    movie2->start();
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
}

void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::greeting()
{
    PlaySound(TEXT("C:\\Users\\cityscience\\Documents\\bowbow\\Resources\\1greeting.wav"),NULL,SND_FILENAME | SND_ASYNC);
    sleep(5*1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(waitReady()));
    timer->start(7000);
}

void MainWindow::waitReady()
{
    PlaySound(TEXT("C:\\Users\\cityscience\\Documents\\bowbow\\Resources\\2ready.wav"),NULL,SND_FILENAME | SND_ASYNC);
}

void MainWindow::breakLoop()
{
    timer->stop();
    ui->label1->show();
    ui->label2->show();
    ui->progressBar->show();
    PlaySound(TEXT("C:\\Users\\cityscience\\Documents\\bowbow\\Resources\\3start.wav"),NULL,SND_FILENAME | SND_ASYNC);
    sleep(7000);
    connect(timer, SIGNAL(timeout()), this, SLOT(barUpdate()));
    timer->start(20);
    savePics();
}

void MainWindow::barUpdate()
{
    if (ui->progressBar->value()<500) {
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    else timer->stop();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::grade()
{
    ui->label->hide();
    ui->label2->hide();
    ui->label1->hide();
    ui->est->show();
    ui->estlabel->show();
    ui->progressBar->show();
    ui->progressBar->setValue(0);
    for (int i=1;i<500;++i){
        sleep(10);
        std::string res;
        std::stringstream ss;
        ss << i;
        res = ss.str();
        cv::Mat frame=cv::imread("C:\\Users\\cityscience\\Documents\\bowbow\\img\\img"+res+".jpg");
        ui->estlabel->setPixmap(QPixmap::fromImage(MatToQImage(frame)));
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    report();
}

void MainWindow::report()
{
    ui->progressBar->hide();
    ui->label_report->show();
    ui->estlabel->hide();
    ui->est->hide();
}

void MainWindow::savePics()
{
    cv::VideoCapture capture(0);
    while (1) {
        count++;
        cv::Mat frame;
        capture >> frame;
        his.push_back(frame);
        cv::imshow("1",frame);
        cv::waitKey(20);
        if (count==500) {
            timer->stop();
            break;
        }
    }
    for (int i=1;i<500;++i){
        std::string res;
        std::stringstream ss;
        ss << i;
        res = ss.str();
        cv::imwrite("C:\\Users\\cityscience\\Documents\\bowbow\\img\\img"+res+".jpg",his[i]);
    }
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
        cv::waitKey(30);
    }
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
