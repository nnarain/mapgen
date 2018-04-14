#include "imgui_extension/imgui_extension.h"
#include <imgui.h>

namespace ImGui
{
	//https://github.com/ocornut/imgui/issues/673
	bool Combo(const char* label, int* current_item, const std::vector<std::string>& items, int items_count, int height_in_items)
	{
		return Combo(label, current_item, [](void* data, int idx, const char** out_text) { *out_text = (*(const std::vector<std::string>*)data)[idx].c_str(); return true; }, (void*)&items, items_count, height_in_items);
	}
}