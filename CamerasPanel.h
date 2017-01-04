#ifndef CAMERAS_PANEL_H
#define CAMERAS_PANEL_H

#include <QListWidget>
#include "qobject.h"
#include "mainwindow.h"

namespace Ui
{
	class MainWindow;
}

class CamerasPanel : public QObject
{
	Q_OBJECT
public:
	CamerasPanel(Ui::MainWindow*);
	~CamerasPanel();
	void setup();
	void reloadCameras(const QStringList&);

private:
	Ui::MainWindow* m_ui;

private slots:
	void openCamera(QListWidgetItem*);
};

#endif // CAMERAS_PANEL_H
