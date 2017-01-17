#include "RecordingsPanel.h"
#include <ui_mainwindow.h>


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
		SLOT(openCamera(QListWidgetItem*)));
}

//*****************************************************************************
void RecordingsPanel::reloadRecordings()
{

}

//*****************************************************************************
void RecordingsPanel::openRecording(QListWidgetItem*)
{

}