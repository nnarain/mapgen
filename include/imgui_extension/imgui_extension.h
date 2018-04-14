#ifndef IMGUI_EXTENSION_H
#define IMGUI_EXTENSION_H

#include <vector>
#include <string>

namespace ImGui
{
	//https://github.com/ocornut/imgui/issues/673
	bool Combo(const char* label, int* current_item, const std::vector<std::string>& items, int items_count, int height_in_items = -1);
}

#endif // IMGUI_EXTENSION_H