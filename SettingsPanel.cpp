#include <ui_mainwindow.h>
#include <qfiledialog.h>

#include "SettingsPanel.h"
#include "SettingsContainer.h"
#include <QDir>

SettingsPanel::SettingsPanel(Ui::MainWindow* ui)
	: QObject(nullptr)
	, m_ui(ui)
{}

SettingsPanel::~SettingsPanel()
{}

void SettingsPanel::setup()
{
	m_ui->savePath->setText(QDir::currentPath());
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

	connect(
		m_ui->resolutionComboBox,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(setResolution(int)));
}

void SettingsPanel::setSensitivity(int value)
{
	SettingsContainer::get()->setSensitivity(value);
}

void SettingsPanel::browseSavePath()
{
	QString dir = QFileDialog::getExistingDirectory(
		nullptr, tr("Open Directory"), "/home",
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (dir.isEmpty() || dir.isNull())
		m_ui->savePath->setText(QDir::currentPath());
	else
		m_ui->savePath->setText(dir);

}

void SettingsPanel::setSavePath(QString dir)
{
	QFileInfo fi(dir);
	bool isDirValid = (fi.isDir() && fi.isWritable());
	if (isDirValid)
		SettingsContainer::get()->setSavePath(dir);
	else
		SettingsContainer::get()->setSavePath(QDir::currentPath());

}

void SettingsPanel::setResolution(int resolutionIndex)
{
	int resolution = 240 + 120 * resolutionIndex;
	SettingsContainer::get()->setResolution(resolution);
}