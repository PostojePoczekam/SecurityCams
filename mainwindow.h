#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
	class MainWindow;
}
class CamerasPanel;
class SettingsPanel;
class RecordingsPanel;

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
	RecordingsPanel* m_recordingsPanel;

private:
	void setup();
};

#endif // MAINWINDOW_H
