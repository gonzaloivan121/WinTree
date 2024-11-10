#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "WinTreeLayer.h"

Walnut::Application* Walnut::CreateApplication(int argc, char** argv) {
	Walnut::ApplicationSpecification spec;
	spec.Name = "WinTree";
	spec.IconPath = "resources/icons/logo.png";
	spec.CustomTitlebar = true;
	spec.CenterWindow = true;

	Walnut::Application* app = new Walnut::Application(spec);
	std::shared_ptr<WinTreeLayer> winTreeLayer = std::make_shared<WinTreeLayer>();
	app->PushLayer(winTreeLayer);
	app->SetMenubarCallback([app, winTreeLayer]() {
		if (ImGui::BeginMenu("Archivo")) {
			if (ImGui::MenuItem("Abrir...", "Ctrl+O")) {
				winTreeLayer->OpenDrive();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Refrescar Todo", "Ctrl+F5", nullptr, winTreeLayer->IsDriveSelected())) {
				winTreeLayer->RefreshAll();
			}

			if (ImGui::MenuItem("Refrescar Seleccionado", "F5", nullptr, winTreeLayer->IsFolderSelected())) {
				winTreeLayer->RefreshSelected();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Salir", "Alt+F4")) {
				app->Close();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Editar")) {
			if (ImGui::MenuItem("Copiar Ruta", "Ctrl+C", nullptr, winTreeLayer->IsFolderSelected())) {
				winTreeLayer->CopyPath();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Limpiar")) {
			if (ImGui::MenuItem("Abrir", "Enter", nullptr, winTreeLayer->IsFolderSelected())) {
				winTreeLayer->Open();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Explorador Aqui", "Ctrl+E", nullptr, winTreeLayer->IsFolderSelected())) {
				winTreeLayer->ExplorerHere();
			}

			if (ImGui::MenuItem("Linea de Comandos Aqui", "Ctrl+P", nullptr, winTreeLayer->IsFolderSelected())) {
				winTreeLayer->CommandPromptHere();
			}

			if (ImGui::MenuItem("Borrar (a la Papelera de Reciclaje)", "Del", nullptr, winTreeLayer->IsFolderSelected())) {
				winTreeLayer->DeleteToTrashBin();
			}

			if (ImGui::MenuItem("Borrar (sin posibilidad de recuperacion)", "Shift+Del", nullptr, winTreeLayer->IsFolderSelected())) {
				winTreeLayer->DeletePermanently();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Propiedades", nullptr, nullptr, winTreeLayer->IsFolderSelected())) {
				winTreeLayer->Properties();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Vaciar la papelera de reciclaje ()")) {
				winTreeLayer->EmptyTrashBin();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Limpieza definida por el Usuario", nullptr, nullptr, false)) {
				winTreeLayer->UserDefinedCleanUp();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Opciones")) {
			if (ImGui::MenuItem("Mostrar Espacio Libre", "F6", winTreeLayer->ShowFreeSpace())) {
				winTreeLayer->ToggleShowFreeSpace();
			}

			if (ImGui::MenuItem("Mostrar Desconocido", "F7", winTreeLayer->ShowUnknown())) {
				winTreeLayer->ToggleShowUnknown();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Mostrar Tipos de Archivo", "F7", winTreeLayer->ShowFileExtensions())) {
				winTreeLayer->ToggleShowFileExtensions();
			}

			if (ImGui::MenuItem("Mostrar Tipos de Archivo", "F7", winTreeLayer->ShowTaskBar())) {
				winTreeLayer->ToggleShowTaskBar();
			}

			if (ImGui::MenuItem("Mostrar Tipos de Archivo", "F7", winTreeLayer->ShowStatusBar())) {
				winTreeLayer->ToggleShowStatusBar();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Configurar WinTree")) {
				
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Ayuda")) {
			if (ImGui::MenuItem("Ayuda")) {

			}

			ImGui::Separator();

			if (ImGui::MenuItem("Acerca de WinTree")) {

			}

			ImGui::EndMenu();
		}
	});
	return app;
}