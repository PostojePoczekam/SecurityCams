#include "CamerasManager.h"
#include <QtMultimedia\qcamera.h>
#include <QtMultimedia\qcameraInfo.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <qmessagebox.h>
#include <QDebug>

CamerasManager* CamerasManager::m_instance;

//*****************************************************************************
CamerasManager* CamerasManager::get()
{
	if (nullptr == m_instance)
		m_instance = new CamerasManager();
	return m_instance;
}

//*****************************************************************************
QStringList CamerasManager::getCamerasList()
{
	QStringList devices;
	for (QCameraInfo cameraInfo : QCameraInfo::availableCameras())
	{
		devices.push_back(cameraInfo.description());
	}
	return devices;
}

//*****************************************************************************
void CamerasManager::showCamera(int index, QString name)
{
	cv::VideoCapture cap(index);
	cv::Mat edges;
	cv::namedWindow(name.toStdString(), cv::WINDOW_AUTOSIZE);

	while (true)
	{
		if (!IsWindowVisible((HWND)cvGetWindowHandle(name.toStdString().c_str())))
		{
			cv::destroyWindow(name.toStdString());
			break;
		}
		cv::Mat frame;
		cv::Mat frame1;
		cv::Mat frame2;
		cap >> frame1;
		cap >> frame2;
		cv::cvtColor(frame1, frame1, cv::COLOR_RGB2GRAY);
		cv::cvtColor(frame2, frame2, cv::COLOR_RGB2GRAY);
		cv::GaussianBlur(frame1, frame1, cv::Size(5, 5), 1);
		cv::GaussianBlur(frame2, frame2, cv::Size(5, 5), 1);
		cv::absdiff(frame1, frame2, frame);
		cv::threshold(frame, frame, 50, 255, cv::THRESH_BINARY);
		std::vector<std::vector<cv::Point> > contours;
		std::vector<cv::Vec4i> hierarchy;
		findContours(frame, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
		qDebug()<<contours.size();
		imshow(name.toStdString(), frame);
		cv::waitKey(100);
	}
}