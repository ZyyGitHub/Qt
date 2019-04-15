#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <io.h>
using namespace std;

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;


string FileLocation(string Location, int num, string EndLocationType);    //获取摄像头图片的函数


int main(int argc, const char * argv[]) {

    VideoCapture cap;
    cap.open(0);
    if (!cap.isOpened())
    {
        return -1;
    }
    namedWindow("video");
    for (; ;)
    {
        Mat frame;
        cap >> frame;
        imshow("Video", frame);
        if (waitKey(30) >= 0)
        {
            break;
        }
    }
    cap.release();
    return 0;
}
#if  0
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
#endif
