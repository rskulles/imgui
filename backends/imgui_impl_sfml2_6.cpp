#include "imgui.h"
#include <cstddef>
#ifndef IMGUI_DISABLE
#include "imgui_impl_sfml2_6.h"

// Clang warnings with -Weverything
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored                                               \
    "-Wimplicit-int-float-conversion" // warning: implicit conversion from 'xxx'
                                      // to 'float' may lose precision
#endif

#include "SFML/Window/Clipboard.hpp"
#include "SFML/Window/Cursor.hpp"
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cstring>
#include <string>

static sf::Clock imgui_clock;

// SFML Data
struct ImGui_ImplSFML2_6_Data {
  sf::Window *Window;
  uint64_t Time;
  uint32_t MouseWindowID;
  int MouseButtonsDown;
  sf::Cursor *MouseCrusors[ImGuiMouseCursor_COUNT];
  sf::Cursor *LastMouseCursor;
  int PendingMouseLeaveFrame;
  char *ClipboardTextData;
  bool MouseCanUseGlobalState;

  ImGui_ImplSFML2_6_Data() { memset((void *)this, 0, sizeof(*this)); }
};

static ImGui_ImplSFML2_6_Data *ImGui_ImplSFML2_6_GetBackendData() {
  return ImGui::GetCurrentContext()
             ? (ImGui_ImplSFML2_6_Data *)ImGui::GetIO().BackendPlatformUserData
             : nullptr;
}

// Functions
static const char *ImGui_ImplSFML2_6_GetClipboardText(void *) {
  ImGui_ImplSFML2_6_Data *bd = ImGui_ImplSFML2_6_GetBackendData();
  if (bd->ClipboardTextData) {
    delete bd->ClipboardTextData;
  }
  bd->ClipboardTextData =
      strdup(sf::Clipboard::getString().toAnsiString().c_str());
  return bd->ClipboardTextData;
}

static void ImGui_ImplSFML2_6_SetClipboardText(void *, const char *text) {
  sf::Clipboard::setString(text);
}

static ImGuiKey ImGui_ImplSFML2_6_KeycodeToImGuiKey(sf::Keyboard::Key code) {
  switch (code) {

  case sf::Keyboard::Unknown:
    return ImGuiKey_None;
  case sf::Keyboard::A:
    return ImGuiKey_A;
  case sf::Keyboard::B:
    return ImGuiKey_B;
  case sf::Keyboard::C:
    return ImGuiKey_C;
  case sf::Keyboard::D:
    return ImGuiKey_D;
  case sf::Keyboard::E:
    return ImGuiKey_E;
  case sf::Keyboard::F:
    return ImGuiKey_F;
  case sf::Keyboard::G:
    return ImGuiKey_G;
  case sf::Keyboard::H:
    return ImGuiKey_H;
  case sf::Keyboard::I:
    return ImGuiKey_I;
  case sf::Keyboard::J:
    return ImGuiKey_J;
  case sf::Keyboard::K:
    return ImGuiKey_K;
  case sf::Keyboard::L:
    return ImGuiKey_L;
  case sf::Keyboard::M:
    return ImGuiKey_M;
  case sf::Keyboard::N:
    return ImGuiKey_N;
  case sf::Keyboard::O:
    return ImGuiKey_O;
  case sf::Keyboard::P:
    return ImGuiKey_P;
  case sf::Keyboard::Q:
    return ImGuiKey_Q;
  case sf::Keyboard::R:
    return ImGuiKey_R;
  case sf::Keyboard::S:
    return ImGuiKey_S;
  case sf::Keyboard::T:
    return ImGuiKey_T;
  case sf::Keyboard::U:
    return ImGuiKey_U;
  case sf::Keyboard::V:
    return ImGuiKey_V;
  case sf::Keyboard::W:
    return ImGuiKey_W;
  case sf::Keyboard::X:
    return ImGuiKey_X;
  case sf::Keyboard::Y:
    return ImGuiKey_Y;
  case sf::Keyboard::Z:
    return ImGuiKey_Z;
  case sf::Keyboard::Num0:
    return ImGuiKey_0;
  case sf::Keyboard::Num1:
    return ImGuiKey_1;
  case sf::Keyboard::Num2:
    return ImGuiKey_2;
  case sf::Keyboard::Num3:
    return ImGuiKey_3;
  case sf::Keyboard::Num4:
    return ImGuiKey_4;
  case sf::Keyboard::Num5:
    return ImGuiKey_5;
  case sf::Keyboard::Num6:
    return ImGuiKey_6;
  case sf::Keyboard::Num7:
    return ImGuiKey_7;
  case sf::Keyboard::Num8:
    return ImGuiKey_8;
  case sf::Keyboard::Num9:
    return ImGuiKey_9;
  case sf::Keyboard::Escape:
    return ImGuiKey_Escape;
  case sf::Keyboard::LControl:
    return ImGuiKey_LeftCtrl;
  case sf::Keyboard::LShift:
    return ImGuiKey_LeftShift;
  case sf::Keyboard::LAlt:
    return ImGuiKey_LeftAlt;
  case sf::Keyboard::LSystem:
    return ImGuiKey_LeftSuper;
  case sf::Keyboard::RControl:
    return ImGuiKey_RightCtrl;
  case sf::Keyboard::RShift:
    return ImGuiKey_RightShift;
  case sf::Keyboard::RAlt:
    return ImGuiKey_RightAlt;
  case sf::Keyboard::RSystem:
    return ImGuiKey_RightSuper;
  case sf::Keyboard::Menu:
    return ImGuiKey_Menu;
  case sf::Keyboard::LBracket:
    return ImGuiKey_LeftBracket;
  case sf::Keyboard::RBracket:
    return ImGuiKey_RightBracket;
  case sf::Keyboard::Semicolon:
    return ImGuiKey_Semicolon;
  case sf::Keyboard::Comma:
    return ImGuiKey_Comma;
  case sf::Keyboard::Period:
    return ImGuiKey_Period;
  case sf::Keyboard::Apostrophe:
    return ImGuiKey_Apostrophe;
  case sf::Keyboard::Slash:
    return ImGuiKey_Slash;
  case sf::Keyboard::Backslash:
    return ImGuiKey_Backslash;
  case sf::Keyboard::Grave:
    return ImGuiKey_GraveAccent;
  case sf::Keyboard::Equal:
    return ImGuiKey_Equal;
  case sf::Keyboard::Hyphen:
    return ImGuiKey_Minus;
  case sf::Keyboard::Space:
    return ImGuiKey_Space;
  case sf::Keyboard::Enter:
    return ImGuiKey_Enter;
  case sf::Keyboard::Backspace:
    return ImGuiKey_Backspace;
  case sf::Keyboard::Tab:
    return ImGuiKey_Tab;
  case sf::Keyboard::PageUp:
    return ImGuiKey_PageUp;
  case sf::Keyboard::PageDown:
    return ImGuiKey_PageDown;
  case sf::Keyboard::End:
    return ImGuiKey_End;
  case sf::Keyboard::Home:
    return ImGuiKey_Home;
  case sf::Keyboard::Insert:
    return ImGuiKey_Insert;
  case sf::Keyboard::Delete:
    return ImGuiKey_Delete;
  case sf::Keyboard::Add:
    return ImGuiKey_KeypadAdd;
  case sf::Keyboard::Subtract:
    return ImGuiKey_KeypadSubtract;
  case sf::Keyboard::Multiply:
    return ImGuiKey_KeypadMultiply;
  case sf::Keyboard::Divide:
    return ImGuiKey_KeypadDivide;
  case sf::Keyboard::Left:
    return ImGuiKey_LeftArrow;
  case sf::Keyboard::Right:
    return ImGuiKey_RightArrow;
  case sf::Keyboard::Up:
    return ImGuiKey_UpArrow;
  case sf::Keyboard::Down:
    return ImGuiKey_DownArrow;
  case sf::Keyboard::Numpad0:
    return ImGuiKey_Keypad0;
  case sf::Keyboard::Numpad1:
    return ImGuiKey_Keypad1;
  case sf::Keyboard::Numpad2:
    return ImGuiKey_Keypad2;
  case sf::Keyboard::Numpad3:
    return ImGuiKey_Keypad3;
  case sf::Keyboard::Numpad4:
    return ImGuiKey_Keypad4;
  case sf::Keyboard::Numpad5:
    return ImGuiKey_Keypad5;
  case sf::Keyboard::Numpad6:
    return ImGuiKey_Keypad6;
  case sf::Keyboard::Numpad7:
    return ImGuiKey_Keypad7;
  case sf::Keyboard::Numpad8:
    return ImGuiKey_Keypad8;
  case sf::Keyboard::Numpad9:
    return ImGuiKey_Keypad9;
  case sf::Keyboard::F1:
    return ImGuiKey_F1;
  case sf::Keyboard::F2:
    return ImGuiKey_F2;
  case sf::Keyboard::F3:
    return ImGuiKey_F3;
  case sf::Keyboard::F4:
    return ImGuiKey_F4;
  case sf::Keyboard::F5:
    return ImGuiKey_F5;
  case sf::Keyboard::F6:
    return ImGuiKey_F6;
  case sf::Keyboard::F7:
    return ImGuiKey_F7;
  case sf::Keyboard::F8:
    return ImGuiKey_F8;
  case sf::Keyboard::F9:
    return ImGuiKey_F9;
  case sf::Keyboard::F10:
    return ImGuiKey_F10;
  case sf::Keyboard::F11:
    return ImGuiKey_F11;
  case sf::Keyboard::F12:
    return ImGuiKey_F12;
  case sf::Keyboard::F13:
    return ImGuiKey_F13;
  case sf::Keyboard::F14:
    return ImGuiKey_F14;
  case sf::Keyboard::F15:
    return ImGuiKey_F15;
  case sf::Keyboard::Pause:
    return ImGuiKey_Pause;
  case sf::Keyboard::KeyCount:
    return ImGuiKey_COUNT;
    break;
  }
  return ImGuiKey_None;
}

static void ImGui_ImplSFML2_6_UpdateKeyModifiers() {
  ImGuiIO &io = ImGui::GetIO();
  io.AddKeyEvent(ImGuiMod_Ctrl,
                 (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                  sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)));
  io.AddKeyEvent(ImGuiMod_Shift,
                 (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
                  sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)));
  io.AddKeyEvent(ImGuiMod_Alt,
                 (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) ||
                  sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)));
  io.AddKeyEvent(ImGuiMod_Super,
                 (sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem) ||
                  sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem)));
}

bool ImGui_ImplSFML2_6_ProcessEvent(const sf::Event *event) {

  ImGuiIO &io = ImGui::GetIO();
  ImGui_ImplSFML2_6_Data *bd = ImGui_ImplSFML2_6_GetBackendData();

  switch (event->type) {

  case sf::Event::LostFocus:
  case sf::Event::GainedFocus: {
    io.AddFocusEvent(event->type == sf::Event::GainedFocus);
    return true;
  }
  case sf::Event::TextEntered: {
    std::string str;
    str.append(sizeof(char32_t), (char32_t)event->text.unicode);
    io.AddInputCharactersUTF8(str.c_str());
    return true;
  }
  case sf::Event::KeyPressed:
  case sf::Event::KeyReleased: {
    ImGui_ImplSFML2_6_UpdateKeyModifiers();
    ImGuiKey key = ImGui_ImplSFML2_6_KeycodeToImGuiKey(event->key.code);
    io.AddKeyEvent(key, event->type == sf::Event::KeyPressed);
  }
  case sf::Event::MouseWheelScrolled: {
    io.AddMouseSourceEvent(ImGuiMouseSource_Mouse);
    io.AddMouseWheelEvent(-event->mouseWheelScroll.x,
                          event->mouseWheelScroll.y);
    return true;
  }
  case sf::Event::MouseButtonPressed:
  case sf::Event::MouseButtonReleased: {
    int mouse_button = -1;
    switch (event->mouseButton.button) {

    case sf::Mouse::Left: {
      mouse_button = 0;
      break;
    }
    case sf::Mouse::Right: {
      mouse_button = 1;
      break;
    }
    case sf::Mouse::Middle: {
      mouse_button = 2;
      break;
    }
    case sf::Mouse::XButton1: {
      mouse_button = 3;
      break;
    }
    case sf::Mouse::XButton2: {
      mouse_button = 4;
      break;
    }
    case sf::Mouse::ButtonCount:
      break;
    }
    if (mouse_button < 0)
      break;
    io.AddMouseSourceEvent(ImGuiMouseSource_Mouse);
    io.AddMouseButtonEvent(mouse_button,
                           event->type == sf::Event::MouseButtonPressed);

    bd->MouseButtonsDown = (event->type == sf::Event::MouseButtonPressed)
                               ? (bd->MouseButtonsDown | (1 << mouse_button))
                               : (bd->MouseButtonsDown & ~(1 << mouse_button));
    return true;
  }
  case sf::Event::MouseMoved: {
    ImVec2 mouse_pos(event->mouseMove.x, event->mouseMove.y);
    io.AddMouseSourceEvent(ImGuiMouseSource_Mouse);
    io.AddMousePosEvent(mouse_pos.x, mouse_pos.y);
    return true;
  }
  case sf::Event::MouseEntered: {
    bd->PendingMouseLeaveFrame = 0;
    return true;
  }
  case sf::Event::MouseLeft: {
    bd->PendingMouseLeaveFrame = ImGui::GetFrameCount() + 1;
    return true;
  }
  default:
    break;
  }
  return false;
}

static void ImGui_ImplSFML2_6_SetupPlatformHandles(ImGuiViewport *viewport,
                                                   sf::Window *window) {
  viewport->PlatformHandleRaw = (void *)window->getNativeHandle();
}

typedef sf::Cursor *cursor_type;
static bool ImGui_ImplInitMouseCursors(
    cursor_type arrow_cursor, cursor_type text_input_cursor,
    cursor_type resize_all_cursor, cursor_type resize_ns_cursor,
    cursor_type resize_ew_cursor, cursor_type resize_nesw_cursor,
    cursor_type resize_nwse_cursor, cursor_type hand_cursor,
    cursor_type not_allowed_cursor) {
  return arrow_cursor->loadFromSystem(sf::Cursor::Arrow) &&
         text_input_cursor->loadFromSystem(sf::Cursor::Text) &&
         resize_all_cursor->loadFromSystem(sf::Cursor::SizeAll) &&
         resize_ns_cursor->loadFromSystem(sf::Cursor::SizeVertical) &&
         resize_ew_cursor->loadFromSystem(sf::Cursor::SizeHorizontal) &&
         resize_nesw_cursor->loadFromSystem(
             sf::Cursor::SizeBottomLeftTopRight) &&
         resize_nwse_cursor->loadFromSystem(
             sf::Cursor::SizeTopLeftBottomRight) &&
         hand_cursor->loadFromSystem(sf::Cursor::Hand) &&
         not_allowed_cursor->loadFromSystem(sf::Cursor::NotAllowed);
}

static bool ImGui_ImplSFML2_6_Init(sf::Window *window, void *sfml_gl_context) {
  ImGuiIO &io = ImGui::GetIO();

  IM_ASSERT(io.BackendPlatformUserData == nullptr &&
            "Already initialzed a platform backend");

  IM_UNUSED(sfml_gl_context);
  imgui_clock.start();
  ImGui_ImplSFML2_6_Data *bd = IM_NEW(ImGui_ImplSFML2_6_Data)();
  io.BackendPlatformUserData = (void *)bd;
  io.BackendPlatformName = "imgui_impl_sfml2_6";
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  bd->Window = window;

  io.SetClipboardTextFn = ImGui_ImplSFML2_6_SetClipboardText;
  io.GetClipboardTextFn = ImGui_ImplSFML2_6_GetClipboardText;
  io.ClipboardUserData = nullptr;
  io.SetPlatformImeDataFn = nullptr;

  bd->MouseCrusors[ImGuiMouseCursor_Arrow] = new sf::Cursor();
  bd->MouseCrusors[ImGuiMouseCursor_TextInput] = new sf::Cursor();
  bd->MouseCrusors[ImGuiMouseCursor_ResizeAll] = new sf::Cursor();
  bd->MouseCrusors[ImGuiMouseCursor_ResizeNS] = new sf::Cursor();
  bd->MouseCrusors[ImGuiMouseCursor_ResizeEW] = new sf::Cursor();
  bd->MouseCrusors[ImGuiMouseCursor_ResizeNESW] = new sf::Cursor();
  bd->MouseCrusors[ImGuiMouseCursor_ResizeNWSE] = new sf::Cursor();
  bd->MouseCrusors[ImGuiMouseCursor_Hand] = new sf::Cursor();
  bd->MouseCrusors[ImGuiMouseCursor_NotAllowed] = new sf::Cursor();
  auto cursor_result =
      ImGui_ImplInitMouseCursors(bd->MouseCrusors[ImGuiMouseCursor_Arrow],
                                 bd->MouseCrusors[ImGuiMouseCursor_TextInput],
                                 bd->MouseCrusors[ImGuiMouseCursor_ResizeAll],
                                 bd->MouseCrusors[ImGuiMouseCursor_ResizeNS],
                                 bd->MouseCrusors[ImGuiMouseCursor_ResizeEW],
                                 bd->MouseCrusors[ImGuiMouseCursor_ResizeNESW],
                                 bd->MouseCrusors[ImGuiMouseCursor_ResizeNWSE],
                                 bd->MouseCrusors[ImGuiMouseCursor_Hand],
                                 bd->MouseCrusors[ImGuiMouseCursor_NotAllowed]);
  if (!cursor_result) {
    io.BackendFlags &= ~ImGuiBackendFlags_HasMouseCursors;
  }
  ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui_ImplSFML2_6_SetupPlatformHandles(main_viewport, window);

  return true;
}

bool ImGui_ImplSFML2_6_InitForOpenGL(sf::Window *window,
                                     void *sfml_gl_context) {
  IM_UNUSED(sfml_gl_context);
  return ImGui_ImplSFML2_6_Init(window, sfml_gl_context);
}

void ImGui_ImplSFML2_6_Shutdown() {
  ImGui_ImplSFML2_6_Data *bd = ImGui_ImplSFML2_6_GetBackendData();
  IM_ASSERT(bd != nullptr &&
            "No platrom backend to shutdown, or already shutdown?");
  ImGuiIO &io = ImGui::GetIO();

  if (bd->ClipboardTextData)
    delete bd->ClipboardTextData;
  for (ImGuiMouseCursor cursor_n = 0; cursor_n < ImGuiMouseCursor_COUNT;
       cursor_n++) {
    delete bd->MouseCrusors[cursor_n];
  }
  bd->LastMouseCursor = nullptr;
  io.BackendPlatformName = nullptr;
  io.BackendPlatformUserData = nullptr;
  io.BackendFlags &=
      ~(ImGuiBackendFlags_HasMouseCursors | ImGuiBackendFlags_HasSetMousePos |
        ImGuiBackendFlags_HasGamepad);
  IM_DELETE(bd);
}

static void ImGui_ImplSFML2_6_UpdateMouseData() {}

static void ImGui_ImplSFML2_6_UpdateMouseCursor() {}

static void ImGui_ImplSFML2_6_UpdateGamepads() {}

void ImGui_ImplSFML2_6_NewFrame() {
  ImGui_ImplSFML2_6_Data *bd = ImGui_ImplSFML2_6_GetBackendData();
  IM_ASSERT(bd != nullptr && "Did you call ImGui_ImplSFML2_6_Init()?");
  ImGuiIO &io = ImGui::GetIO();

  auto window_size = bd->Window->getSize();
  auto desktop_size = sf::VideoMode::getDesktopMode().size;

  io.DisplaySize = ImVec2(window_size.x, window_size.y);
  io.DisplayFramebufferScale = ImVec2(1.0, 1.0);
  uint64_t current_time = imgui_clock.getElapsedTime().asMicroseconds();
  if (current_time <= bd->Time) {
    current_time = bd->Time + 1;
  }

  io.DeltaTime = bd->Time > 0
                     ? (float)((double)(current_time - bd->Time) / 1000000.0f)
                     : (float)(1.0f / 60.f);
  bd->Time = current_time;

  if (bd->PendingMouseLeaveFrame &&
      bd->PendingMouseLeaveFrame >= ImGui::GetFrameCount() &&
      bd->MouseButtonsDown == 0) {
    bd->MouseWindowID = 0;
    bd->PendingMouseLeaveFrame = 0;
    io.AddMousePosEvent(-FLT_MAX, -FLT_MAX);
  }

  ImGui_ImplSFML2_6_UpdateMouseData();
  ImGui_ImplSFML2_6_UpdateMouseCursor();

  // Update game controllers (if enabled and available)
  ImGui_ImplSFML2_6_UpdateGamepads();
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif
