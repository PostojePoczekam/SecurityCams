#include <SettingsContainer.h>
#include <windows.h>
#include "Camera.h"
#include <opencv2/video.hpp>
#include <QDebug>

#define ASPECT_RATIO 4.f/3.f

//*****************************************************************************
Camera::Camera(int index, QString name)
	: m_index(index)
	, m_name(name)
{
	m_thread = new std::thread(&Camera::proceedFrame, this);
}

//*****************************************************************************
Camera::~Camera()
{
	/*m_thread->join();
	delete m_thread;*/
}

//*****************************************************************************
void Camera::proceedFrame()
{
	m_videoCapture.open(m_index);
	if (!m_videoCapture.isOpened())
		return;
	bool heightSet = m_videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, SettingsContainer::get()->getResolution());
	bool widthSet = m_videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, SettingsContainer::get()->getResolution()*ASPECT_RATIO);
	bool recording = false;
	cv::namedWindow(m_name.toStdString(), cv::WINDOW_AUTOSIZE);

	while (true)
	{
		if (!IsWindowVisible((HWND)cvGetWindowHandle(m_name.toStdString().c_str())))
		{
			cv::destroyWindow(m_name.toStdString());
			delete this;
			break;
		}
		if (recording)
		{
			m_videoCapture >> m_outputFrame;
			imshow(m_name.toStdString(), m_outputFrame);
		}
		else
		{
			m_videoCapture >> m_outputFrame;
			m_videoCapture >> m_proceedFrameAlpha;
			m_videoCapture >> m_proceedFrameBeta;
			cv::cvtColor(m_proceedFrameAlpha, m_proceedFrameAlpha, cv::COLOR_RGB2GRAY);
			cv::cvtColor(m_proceedFrameBeta, m_proceedFrameBeta, cv::COLOR_RGB2GRAY);
			cv::GaussianBlur(m_proceedFrameAlpha, m_proceedFrameAlpha, cv::Size(5, 5), 1);
			cv::GaussianBlur(m_proceedFrameBeta, m_proceedFrameBeta, cv::Size(5, 5), 1);
			cv::absdiff(m_proceedFrameAlpha, m_proceedFrameBeta, m_proceedFrameAlpha);
			cv::threshold(m_proceedFrameAlpha, m_proceedFrameAlpha, 50, 255, cv::THRESH_BINARY);
			std::vector<std::vector<cv::Point> > contours;
			std::vector<cv::Vec4i> hierarchy;
			findContours(m_proceedFrameAlpha, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
			if (contours.size() > 3 * (6 - SettingsContainer::get()->getSensitivity()))
			{
				createOutputFile();
				recording = true;
			}
			imshow(m_name.toStdString(), m_outputFrame);
		}
		cv::waitKey(100);
	}
}

//*****************************************************************************
void Camera::createOutputFile()
{
	int fourcc = CV_FOURCC('M', 'J', 'P', 'G');
	QString filename = SettingsContainer::get()->getSavePath() + QString("/") + QDateTime::currentDateTime().toString() + QString(".avi");
	cv::Size frameSize = cv::Size(m_outputFrame.cols, m_outputFrame.rows);
	m_videoWriter.open(filename.toStdString(), fourcc, 24, frameSize, true);
	if (m_videoWriter.isOpened())
		qDebug() << "ready!";
	else
		qDebug() << "nope";
}