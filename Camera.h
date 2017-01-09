#ifndef CAMERA_H
#define CAMERA_H

#include <QString>
#include <thread>
#include <QDateTime> 
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>

class Camera
{
public:
	Camera(int index, QString name);
	~Camera();

private:
	void proceedFrame();
	void createOutputFile();

private:
	int m_index;
	QString m_name;
	std::thread* m_thread;
	cv::VideoCapture m_videoCapture;
	cv::VideoWriter m_videoWriter;
	cv::Mat m_outputFrame;
	cv::Mat m_proceedFrameAlpha;
	cv::Mat m_proceedFrameBeta;
};

#endif //CAMERA_H
