#pragma once
#include "imgui.h"
#ifndef IMGUI_DISABLE
namespace sf {
class Window;
class Event;
} // namespace sf

IMGUI_IMPL_API bool ImGui_ImplSFML2_6_InitForOpenGL(sf::Window *window,
                                                    void *sfml_gl_context);
IMGUI_IMPL_API void ImGui_ImplSFML2_6_Shutdown();
IMGUI_IMPL_API void ImGui_ImplSFML2_6_NewFrame();
IMGUI_IMPL_API bool ImGui_ImplSFML2_6_ProcessEvent(const sf::Event *event);

#endif
