#include "Game.h"
#include "Platform/Window.h"

using namespace rogue;

namespace game
{
	namespace windowui
	{
		namespace funcs
		{
			void CreateWeaponDef()
			{
				std::string wpnDefEditorId = window::GetControlText("wpnDefEditorId");
				std::string wpnDefDisplayName = window::GetControlText("wpnDefDisplayName");
				std::string wpnDefIsUnique = window::GetControlText("wpnDefIsUnique");
				std::string wpnDefRange = window::GetControlText("wpnDefRange");
				std::string wpnDefValue = window::GetControlText("wpnDefValue");
				std::string wpnDefWeight = window::GetControlText("wpnDefWeight");
				std::string wpnDefDamage = window::GetControlText("wpnDefDamage");

				std::vector<std::string> params{};
				params.push_back(wpnDefEditorId);
				params.push_back(wpnDefDisplayName);
				params.push_back(wpnDefIsUnique);
				params.push_back(wpnDefRange);
				params.push_back(wpnDefValue);
				params.push_back(wpnDefWeight);
				params.push_back(wpnDefDamage);

				commands::CreateWeaponDef(params);
			}

			void PrintDefs()
			{
				commands::PrintDefs(std::vector<std::string>());
			}

			void LoadDefs()
			{
				//txtLoadDefsPath
				std::vector<std::string> params;
				params.push_back(window::GetControlText("txtLoadDefsPath"));
				commands::LoadDefs(params);
			}

			void SaveDefs()
			{
				//txtSaveDefsPath
				std::vector<std::string> params;
				params.push_back(window::GetControlText("txtSaveDefsPath"));
				commands::SaveDefs(params);
			}

			void ClearDefs()
			{
				commands::ClearDefs(std::vector<std::string>());
			}

		}

		void Run()
		{
			window::m_windowTitle = "REngine";
			window::m_windowClassName = "REngineClass";

			//general engine funcs column
			window::AddControl(window::ControlType::Label, "labelIntro", "Engine controls", 150, 25);
			window::AddControl(window::ControlType::Button, "btnPrintDefs", "Print Defs", 150, 25);
			window::AddControlFunction("btnPrintDefs", funcs::PrintDefs);
			window::AddControl(window::ControlType::Button, "btnClearDefs", "Clear Defs", 150, 25);
			window::AddControlFunction("btnClearDefs", funcs::ClearDefs);
			window::AddControl(window::ControlType::Edit, "txtLoadDefsPath", "load.json", 150, 25);
			window::AddControl(window::ControlType::Button, "btnLoadDefs", "Load Defs", 150, 25);
			window::AddControlFunction("btnLoadDefs", funcs::LoadDefs);
			window::AddControl(window::ControlType::Edit, "txtSaveDefsPath", "save.json", 150, 25);
			window::AddControl(window::ControlType::Button, "btnSaveDefs", "Save Defs", 150, 25);
			window::AddControlFunction("btnSaveDefs", funcs::SaveDefs);

			window::NextColumn();

			//CreateWeaponDef column
			window::AddControl(window::ControlType::Label, "wpnDefLabel", "Create WeaponDef:", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefEditorId", "EditorId", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefDisplayName", "DisplayName", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefIsUnique", "IsUnique", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefRange", "Range", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefValue", "Value", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefWeight", "Weight", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefDamage", "Damage", 150, 25);
			window::AddControl(window::ControlType::Button, "wpnDefCreateButton", "Create WeaponDef", 150, 25);
			window::AddControlFunction("wpnDefCreateButton", funcs::CreateWeaponDef);

			window::NextColumn();

			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)window::Setup, 0, 0, 0);
		}
	}
}