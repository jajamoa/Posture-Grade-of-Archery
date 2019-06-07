#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2\opencv.hpp>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

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
    void testTwoCam();
    void savePics();

public slots:
    void greeting();
    void waitReady();
    void breakLoop();
    void barUpdate();
    void report();
    void grade();

private:
    Ui::MainWindow *ui;
    int count;
    std::vector<cv::Mat> his;
    QTimer *timer = new QTimer(this);
    QTimer *timer2 = new QTimer(this);
    QSerialPort *serial;
};

#endif // MAINWINDOW_H
