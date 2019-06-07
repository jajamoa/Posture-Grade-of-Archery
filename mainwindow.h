#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2\opencv.hpp>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "string.h"
#include "Windows.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QImage MatToQImage(cv::Mat mtx);
    LPCWSTR stringToLPCWSTR(std::string orig);
    void testTwoCam();
    void savePics();

public slots:
    void greeting();
    void waitReady();
    void breakLoop();
    void barUpdate();
    void report();
    void grade();
    void gradeBarUpdate();
    void display();
    void waitJudge();
    void report1();
    void report2();
    void report3();
    void adjustSpeed();

private:
    Ui::MainWindow *ui;
    int count;
    std::vector<cv::Mat> his;
    QTimer *timer = new QTimer(this);
    QTimer *timer2 = new QTimer(this);
    QTimer *timer3 = new QTimer(this);
    QTimer *timer4 = new QTimer(this);
    QTimer *timer5 = new QTimer(this);
    QTimer *timer6 = new QTimer(this);
    QSerialPort *serial;
    int curPicIndex;
    QMovie *movie3;
};

#endif // MAINWINDOW_H
