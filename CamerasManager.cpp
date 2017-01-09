#include "CamerasManager.h"
#include <QtMultimedia\qcamera.h>
#include <QtMultimedia\qcameraInfo.h>
#include <qmessagebox.h>
#include <QDebug>
#include "SettingsContainer.h"
#include <Camera.h>

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
	Camera* camera = new Camera(index, name);
}