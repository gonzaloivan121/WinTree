#pragma once

#include "Panel.h"

#include "../Translation/TranslationService.h"

class SettingsPanel : public Panel {
public:
	SettingsPanel(bool& showSettingsPanel);

	virtual bool OnUIRender() override;
private:
	void SetupLanguageSelector();
private:
	bool& m_ShowSettingsPanel;

	std::string m_Language = TranslationService::GetCurrentLanguage();
};
