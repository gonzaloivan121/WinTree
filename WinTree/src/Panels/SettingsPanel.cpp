#include "SettingsPanel.h"

#include "Walnut/UI/UI.h"

#include <filesystem>

SettingsPanel::SettingsPanel(bool& showSettingsPanel)
	: m_ShowSettingsPanel(showSettingsPanel)
{
	
}

bool SettingsPanel::OnUIRender() {
	if (m_ShowSettingsPanel) {
		ImGui::Begin("Settings", &m_ShowSettingsPanel);

		ImGui::Separator();
		ImGui::AlignTextToFramePadding();
		Walnut::UI::TextCentered("Language");
		ImGui::Separator();

		ImGui::BeginChild("Language Settings", ImVec2(0, 52), true);
		if (ImGui::BeginCombo("Language", m_Language.c_str())) {
			SetupLanguageSelector();
			ImGui::EndCombo();
		}
		ImGui::EndChild();

		ImGui::End();
	}
}

void SettingsPanel::SetupLanguageSelector() {
	for (const auto& entry : std::filesystem::directory_iterator("i18n")) {
		if (entry.path().extension() == ".yaml") {
			std::string languageName = entry.path().filename().replace_extension("").string();
			bool isSelected = m_Language == languageName;

			if (ImGui::Selectable(languageName.c_str(), isSelected)) {
				m_Language = languageName;
				TranslationService::Use(m_Language);
			}

			if (isSelected) {
				ImGui::SetItemDefaultFocus();
			}
		}
	}
}
