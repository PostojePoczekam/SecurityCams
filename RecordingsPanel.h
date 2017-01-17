#ifndef RECORDINGS_PANEL_H
#define RECORDINGS_PANEL_H

#include <QListWidget>
#include "qobject.h"
#include "mainwindow.h"

namespace Ui
{
	class MainWindow;
}

class RecordingsPanel : public QObject
{
	Q_OBJECT
public:
	RecordingsPanel(Ui::MainWindow*);
	~RecordingsPanel();
	void setup();
	void reloadRecordings();

private:
	Ui::MainWindow* m_ui;

	private slots:
	void openRecording(QListWidgetItem*);
};

#endif // RECORDINGS_PANEL_H
