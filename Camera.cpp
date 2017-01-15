#include <SettingsContainer.h>
#include <windows.h>
#include "Camera.h"
#include <opencv2/video.hpp>
#include <QDebug>

#define ASPECT_RATIO 4.f/3.f
#define FRAMES2RECORD 50
#define FRAMERATE 10

//*****************************************************************************
Camera::Camera(int index, QString name)
	: m_index(index)
	, m_framesLeft(FRAMES2RECORD)
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
	m_videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, SettingsContainer::get()->getResolution());
	m_videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, SettingsContainer::get()->getResolution()*ASPECT_RATIO);
	bool recording = false;
	cv::namedWindow(m_name.toStdString(), cv::WINDOW_AUTOSIZE);

	while (true)
	{
		if (!IsWindowVisible((HWND)cvGetWindowHandle(m_name.toStdString().c_str())))
		{
			if (recording)
				m_videoWriter.release();
			cv::destroyWindow(m_name.toStdString());
			delete this;
			break;
		}
		if (recording)
		{
			if (m_framesLeft != 0)
			{
				m_videoCapture >> m_outputFrame;
				m_videoWriter.write(m_outputFrame);
				imshow(m_name.toStdString(), m_outputFrame);
				m_framesLeft--;
			}
			else
			{
				qDebug() << "recorded!";
				m_videoWriter.release();
				recording = false;
				m_framesLeft = FRAMES2RECORD;
			}
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
		cv::waitKey(1000 / FRAMERATE);
	}
}

//*****************************************************************************
void Camera::createOutputFile()
{
	int fourcc = CV_FOURCC('M', 'P', 'E', 'G');
	QString filename = SettingsContainer::get()->getSavePath() + QString("/") + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + QString(".mp4");
	cv::Size frameSize = cv::Size(m_outputFrame.cols, m_outputFrame.rows);
	m_videoWriter.open(filename.toStdString(), fourcc, FRAMERATE, frameSize, true);
	if (m_videoWriter.isOpened())
		qDebug() << "detected!";
}