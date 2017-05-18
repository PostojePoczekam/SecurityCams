#ifndef SETTINGS_CONTAINER_H
#define SETTINGS_CONTAINER_H

#include<QString>

class SettingsContainer
{
public:
	static SettingsContainer* get();

public:
	inline  void setSavePath(const QString& path) { m_savePath = path; }
	inline  void setSensitivity(int sensitivity) { m_sensitivity = sensitivity; }
	inline  void setResolution(int resolution) { m_resolution = resolution; }
	inline  QString getSavePath() { return m_savePath; }
	inline  int getSensitivity() { return m_sensitivity; }
	inline  int getResolution() { return m_resolution; }

private:
	QString m_savePath;
	int m_sensitivity;
	int m_resolution;

private:
	static SettingsContainer* m_instance;
	SettingsContainer();
	~SettingsContainer() {}

};

#endif //SETTINGS_CONTAINER_H