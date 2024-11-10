#include "WinTreeLayer.h"

#include "Walnut/Application.h"
#include "Walnut/Input/Input.h"
#include "Walnut/Core/Log.h"

#include "Translation/TranslationService.h"

WinTreeLayer::WinTreeLayer() {

}

void WinTreeLayer::OnAttach() {
	Initialize();
#if 0
	std::filesystem::path path = std::filesystem::current_path();
	IterateOverDirectory(path);
#endif
}

void WinTreeLayer::OnDetach() {
	spdlog::info("WinTreeLayer - Destroying");
}

void WinTreeLayer::OnUpdate(float ts) {
	WinTreeLayer::HandleControls();
}

void WinTreeLayer::OnUIRender() {
	// ImGui::ShowDemoWindow();
	ImGui::Begin("Archivos");

	auto& flags = GetTableFlags();

	ImGui::BeginTable("Archivos##table", 3, flags);
	ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
	ImGui::TableSetupColumn("Size");
	ImGui::TableSetupColumn("Type");
	ImGui::TableHeadersRow();

	for (auto node : m_Nodes) {
		DisplayNode(node);
	}

	ImGui::EndTable();

	ImGui::End();
}

void WinTreeLayer::OpenDrive() {}

void WinTreeLayer::RefreshAll() {}

void WinTreeLayer::RefreshSelected() {}

void WinTreeLayer::CopyPath() {}

void WinTreeLayer::Open() {}

void WinTreeLayer::ExplorerHere() {}

void WinTreeLayer::CommandPromptHere() {}

void WinTreeLayer::DeleteToTrashBin() {}

void WinTreeLayer::DeletePermanently() {}

void WinTreeLayer::Properties() {}

void WinTreeLayer::EmptyTrashBin() {}

void WinTreeLayer::UserDefinedCleanUp() {}

void WinTreeLayer::Initialize() {
	spdlog::info("WinTreeLayer - Initializing");
	TranslationService::Use("English");
	GenerateExtensionIcons();
	SetupRootPath();
	GenerateTree();
	spdlog::info("WinTreeLayer - Initialization complete");
}

void WinTreeLayer::HandleControls() {
	// Left Controls Keys
	if (Walnut::Input::IsKeyDown(Walnut::KeyCode::LeftControl)) {
		// Open Drive
		if (Walnut::Input::IsKeyDown(Walnut::KeyCode::O)) {
			
		}

		// Reload All
		if (Walnut::Input::IsKeyDown(Walnut::KeyCode::F5)) {
			
		}

		// Copy Path
		if (Walnut::Input::IsKeyDown(Walnut::KeyCode::C)) {

		}
	}
}

void WinTreeLayer::GenerateExtensionIcons() {
	spdlog::info("WinTreeLayer - Generating Extension Icons");
	for (auto& entry : std::filesystem::directory_iterator(m_IconsPath)) {
		std::string extension = entry.path().filename().replace_extension("").string();
		m_ExtensionIcons[extension] = std::make_shared<Walnut::Image>(entry.path().string());
	}
	spdlog::info("WinTreeLayer - Extension Icons Generated");
}

void WinTreeLayer::SetupRootPath() {
	spdlog::info("WinTreeLayer - Setting up Root Path");
	m_RootPath = std::filesystem::current_path().root_path();
	spdlog::info("WinTreeLayer - Root Path setup complete");
}

void WinTreeLayer::GenerateTree() {
	spdlog::info("WinTreeLayer - Generating Tree");
	std::filesystem::path path = std::filesystem::current_path();
	IterateOverDirectory(path);
	spdlog::info("WinTreeLayer - Tree Generated");
}

void WinTreeLayer::IterateOverDirectory(const std::filesystem::path& path, Node* parent) {
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		const auto fileExtension = GetFileExtension(entry);
		const auto fileIcon = GetFileIcon(fileExtension);
		const auto fileName = entry.path().filename().string();
		const auto fileSize = entry.file_size();

		Node node;
		node.Icon = fileIcon;
		node.Name = fileName;
		node.Size = fileSize;

		if (entry.is_directory()) {
			node.Type = "Directory";
		} else if (entry.is_regular_file()) {
			node.Type = "File";
		} else {
			node.Type = "Unknown";
		}

		if (parent) {
			parent->Children.emplace_back(node);
		} else {
			m_Nodes.emplace_back(node);
		}

		if (node.Type == "Directory") {
			IterateOverDirectory(entry, &node);
		}
	}
}

ImGuiTableFlags& WinTreeLayer::GetTableFlags() {
	ImGuiTableFlags flags =
		ImGuiTableFlags_Borders |
		ImGuiTableFlags_RowBg |
		ImGuiTableFlags_Resizable |
		ImGuiTableFlags_Reorderable |
		ImGuiTableFlags_Hideable |
		ImGuiTableFlags_Sortable |
		ImGuiTableFlags_SortMulti;
	return flags;
}

ImGuiTreeNodeFlags& WinTreeLayer::GetFolderTreeNodeFlags() {
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanFullWidth;
	return flags;
}

ImGuiTreeNodeFlags& WinTreeLayer::GetFileTreeNodeFlags() {
	ImGuiTreeNodeFlags flags =
		ImGuiTreeNodeFlags_Leaf |
		ImGuiTreeNodeFlags_NoTreePushOnOpen |
		ImGuiTreeNodeFlags_SpanFullWidth;
	return flags;
}

std::string& WinTreeLayer::GetFileExtension(const std::filesystem::directory_entry& entry) {
	std::string extension = "";

	if (entry.is_directory()) {
		extension = "folder";
	} else {
		extension = entry.path().extension().string();
		extension.erase(0, 1);

		for (auto& c : extension) {
			c = tolower(c);
		}
	}

	if (extension.empty()) {
		extension = "blank";
	}

	return extension;
}

std::shared_ptr<Walnut::Image> WinTreeLayer::GetFileIcon(const std::string& extension) {
	if (m_ExtensionIcons[extension]) {
		return m_ExtensionIcons[extension];
	} else {
		return m_ExtensionIcons["blank"];
	}
}

void WinTreeLayer::DisplayNode(const Node& node) {
	ImGui::TableNextRow();
	ImGui::TableNextColumn();

	if (node.Type == "Directory") {
		bool isOpen = ImGui::TreeNodeEx(node.Name.c_str(), GetFolderTreeNodeFlags());
	
		ImGui::TableNextColumn();
		ImGui::TextDisabled("--");
		ImGui::TableNextColumn();
		ImGui::TextUnformatted(node.Type.c_str());

		if (isOpen) {
			for (auto& children : node.Children) {
				DisplayNode(children);
			}

			ImGui::TreePop();
		}
	} else {
		ImGui::TreeNodeEx(node.Name.c_str(), GetFileTreeNodeFlags());
		ImGui::TableNextColumn();
		ImGui::Text("%d", node.Size);
		ImGui::TableNextColumn();
		ImGui::TextUnformatted(node.Type.c_str());
	}
}
