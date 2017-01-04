#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent)
	, m_ui(new Ui::MainWindow)
	, m_camerasPanel(nullptr)
	, m_settingsPanel(nullptr)
{
	m_ui->setupUi(this);
	setup();
}

MainWindow::~MainWindow()
{
	delete m_ui;
}

void MainWindow::setup()
{
	m_camerasPanel = new CamerasPanel(m_ui);
	m_settingsPanel = new SettingsPanel(m_ui);
	m_camerasPanel->setup();
	m_settingsPanel->setup();
}