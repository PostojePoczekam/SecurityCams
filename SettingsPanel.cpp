#include <ui_mainwindow.h>
#include <qfiledialog.h>

#include "SettingsPanel.h"

SettingsPanel::SettingsPanel(Ui::MainWindow* ui)
	: QObject(nullptr)
	, m_ui(ui)
{}

SettingsPanel::~SettingsPanel()
{}

void SettingsPanel::setup()
{
	connect(
		m_ui->sensitivitySlider,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(setSensitivity(int)));

	connect(
		m_ui->browsePathButton,
		SIGNAL(clicked()),
		this,
		SLOT(browseSavePath()));

	connect(
		m_ui->savePath,
		SIGNAL(textChanged(QString)),
		this,
		SLOT(setSavePath(QString)));
}

void SettingsPanel::setSensitivity(int value)
{

}

void SettingsPanel::browseSavePath()
{
	QString dir = QFileDialog::getExistingDirectory(
		nullptr, tr("Open Directory"),
		"/home",
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	m_ui->savePath->setText(dir);
}

void SettingsPanel::setSavePath(QString dir)
{

}