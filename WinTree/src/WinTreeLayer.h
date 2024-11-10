#pragma once

#include "Walnut/Layer.h"
#include "Walnut/Image.h"
#include "Walnut/UI/UI.h"

#include "Core/Node.h"

#include <filesystem>
#include <unordered_map>
#include <string>

class WinTreeLayer : public Walnut::Layer {
public:
	WinTreeLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(float ts) override;
	virtual void OnUIRender() override;
public:
	// File Menu
	void OpenDrive();
	void RefreshAll();
	void RefreshSelected();

	// Edit Menu
	void CopyPath();

	// Clean Up Menu
	void Open();
	void ExplorerHere();
	void CommandPromptHere();
	void DeleteToTrashBin();
	void DeletePermanently();
	void Properties();
	void EmptyTrashBin();
	void UserDefinedCleanUp();
public:
	void ToggleShowFreeSpace() { m_ShowFreeSpace = !m_ShowFreeSpace; }
	void ToggleShowUnknown() { m_ShowUnknown = !m_ShowUnknown; }
	void ToggleShowFileExtensions() { m_ShowFileExtensions = !m_ShowFileExtensions; }
	void ToggleShowTaskBar() { m_ShowTaskBar = !m_ShowTaskBar; }
	void ToggleShowStatusBar() { m_ShowStatusBar = !m_ShowStatusBar; }
public:
	const bool& IsDriveSelected() const { return m_IsDriveSelected; }
	const bool& IsFolderSelected() const { return m_IsFolderSelected; }

	const bool& ShowFreeSpace() const { return m_ShowFreeSpace; }
	const bool& ShowUnknown() const { return m_ShowUnknown; }
	const bool& ShowFileExtensions() const { return m_ShowFileExtensions; }
	const bool& ShowTaskBar() const { return m_ShowTaskBar; }
	const bool& ShowStatusBar() const { return m_ShowStatusBar; }
private:
	void Initialize();
	void HandleControls();
	void GenerateExtensionIcons();
	void SetupRootPath();
	void GenerateTree();
	void IterateOverDirectory(const std::filesystem::path& path, Node* parent = nullptr);
	ImGuiTableFlags& GetTableFlags();
	ImGuiTreeNodeFlags& GetFolderTreeNodeFlags();
	ImGuiTreeNodeFlags& GetFileTreeNodeFlags();
	std::string& GetFileExtension(const std::filesystem::directory_entry& entry);
	std::shared_ptr<Walnut::Image> GetFileIcon(const std::string& extension);
	void DisplayNode(const Node& node);
private:
	bool m_IsDriveSelected = false;
	bool m_IsFolderSelected = false;

	bool m_ShowFreeSpace = true;
	bool m_ShowUnknown = false;
	bool m_ShowFileExtensions = true;
	bool m_ShowTaskBar = true;
	bool m_ShowStatusBar = true;

	bool m_ShowImGuiDemoWindow = true;

	float m_IconSize = 0.33f;

	std::filesystem::path m_RootPath;
	std::filesystem::path m_IconsPath = "resources/icons/files/";
	std::unordered_map<std::string, std::shared_ptr<Walnut::Image>> m_ExtensionIcons;

	std::vector<Node> m_Nodes;
};