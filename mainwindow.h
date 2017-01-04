#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CamerasPanel.h"
#include "SettingsPanel.h"

namespace Ui
{
	class MainWindow;
}
class CamerasPanel;
class SettingsPanel;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *m_ui;
	CamerasPanel* m_camerasPanel;
	SettingsPanel* m_settingsPanel;

private:
	void setup();
};

#endif // MAINWINDOW_H
