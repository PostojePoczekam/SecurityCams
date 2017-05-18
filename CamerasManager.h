#ifndef CAMERAS_MANAGER_H
#define CAMERAS_MANAGER_H

#include <QStringList>

class CamerasManager
{
public:
	static CamerasManager* get();
public:
	QStringList getCamerasList();
	void showCamera(int, QString);
private:
	static CamerasManager* m_instance;
	CamerasManager() {}
	~CamerasManager() {}
private:
	QStringList m_runningCameras;
};

#endif //CAMERAS_MANAGER_H