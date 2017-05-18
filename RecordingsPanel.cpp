#include "RecordingsPanel.h"
#include <ui_mainwindow.h>
#include <QDir>
#include "SettingsContainer.h"
#include <QDesktopServices>
#include <QUrl>

//*****************************************************************************
RecordingsPanel::RecordingsPanel(Ui::MainWindow* ui)
	: QObject(nullptr)
	, m_ui(ui)
{}

//*****************************************************************************
RecordingsPanel::~RecordingsPanel()
{}

//*****************************************************************************
void RecordingsPanel::setup()
{
	reloadRecordings();
	connect(
		m_ui->recordingsList,
		SIGNAL(itemDoubleClicked(QListWidgetItem*)),
		this,
		SLOT(openRecording(QListWidgetItem*)));
}

//*****************************************************************************
void RecordingsPanel::reloadRecordings()
{
	m_ui->recordingsList->clear();
	QDir directory = QDir(SettingsContainer::get()->getSavePath());
	QStringList filters;
	filters << "*.avi" << "*.mp4" << "*.webm";
	auto filenames = directory.entryList(filters);
	for (QString filename : filenames)
	{
		m_ui->recordingsList->addItem(filename);
	}
}

//*****************************************************************************
void RecordingsPanel::openRecording(QListWidgetItem* item)
{
	QDesktopServices::openUrl(QUrl("file:///" + SettingsContainer::get()->getSavePath() + "/" + item->text()));
}