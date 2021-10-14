#include "Harmony.h"
#include "Harmony/Core/EntryPoint.h"

#include "EditorLayer.h"

#include <string>

namespace Harmony
{

	class HarmonyEditor : public Application
	{
	public:
		HarmonyEditor()
			: Application("Harmony Editor")
		{
			push_layer(new EditorLayer());
		}

		~HarmonyEditor()
		{
		}
	};

	Application* create_application()
	{
		return new HarmonyEditor();
	}

}