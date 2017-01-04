#include "CamerasPanel.h"
#include "CamerasManager.h"
#include <ui_mainwindow.h>

//*****************************************************************************
CamerasPanel::CamerasPanel(Ui::MainWindow* ui)
	: QObject(nullptr)
	, m_ui(ui)
{}

//*****************************************************************************
CamerasPanel::~CamerasPanel()
{}

//*****************************************************************************
void CamerasPanel::setup()
{
	reloadCameras(CamerasManager::get()->getCamerasList());
	connect(
		m_ui->camerasList,
		SIGNAL(itemDoubleClicked(QListWidgetItem*)),
		this,
		SLOT(openCamera(QListWidgetItem*)));
}

//*****************************************************************************
void CamerasPanel::reloadCameras(const QStringList& camerasList)
{
	for (QString camera : camerasList)
	{
		m_ui->camerasList->addItem(camera);
	}
}

//*****************************************************************************
void CamerasPanel::openCamera(QListWidgetItem* item)
{
	CamerasManager::get()->showCamera(m_ui->camerasList->row(item), item->text());
}