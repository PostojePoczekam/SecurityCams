#ifndef SETTINGS_PANEL_H
#define SETTINGS_PANEL_H

#include "qobject.h"
#include "mainwindow.h"

namespace Ui
{
	class MainWindow;
}


class SettingsPanel : public QObject
{
	Q_OBJECT
public:
	SettingsPanel(Ui::MainWindow* ui);
	~SettingsPanel();
	void setup();

private:
	Ui::MainWindow* m_ui;

private slots:
	void setSensitivity(int);
	void browseSavePath();
	void setSavePath(QString);
	void setResolution(int);

};

#endif //SETTINGS_PANEL_H