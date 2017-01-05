#include <QDir>
#include "SettingsContainer.h"

SettingsContainer* SettingsContainer::m_instance;

//*****************************************************************************
SettingsContainer* SettingsContainer::get()
{
	if (nullptr == m_instance)
		m_instance = new SettingsContainer();
	return m_instance;
}

//*****************************************************************************
SettingsContainer::SettingsContainer()
	: m_savePath(QDir::currentPath())
	, m_sensitivity(3)
	, m_resolution(240)
{

}