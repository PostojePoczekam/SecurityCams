#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CamerasPanel.h"
#include "SettingsPanel.h"
#include "RecordingsPanel.h"
#include <qdebug.h>

//*****************************************************************************
MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent)
	, m_ui(new Ui::MainWindow)
	, m_camerasPanel(nullptr)
	, m_settingsPanel(nullptr)
	, m_recordingsPanel(nullptr)
{
	m_ui->setupUi(this);
	setup();
}

//*****************************************************************************
MainWindow::~MainWindow()
{
	delete m_ui;
}

//*****************************************************************************
void MainWindow::setup()
{
	connect(
		m_ui->tabWidget,
		SIGNAL(currentChanged(int)),
		this,
		SLOT(tabChanged(int))
	);
	m_camerasPanel = new CamerasPanel(m_ui);
	m_settingsPanel = new SettingsPanel(m_ui);
	m_recordingsPanel = new RecordingsPanel(m_ui);
	m_camerasPanel->setup();
	m_settingsPanel->setup();
	m_recordingsPanel->setup();
}

//*****************************************************************************
void MainWindow::tabChanged(int index)
{
	switch (index)
	{
	case(0):
		m_camerasPanel->reloadCameras();
		break;
	case(2):
		m_recordingsPanel->reloadRecordings();
		break;
	default:
		break;
	}
}