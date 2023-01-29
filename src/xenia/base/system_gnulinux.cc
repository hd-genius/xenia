/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <alloca.h>
#include <dlfcn.h>
#include <stdlib.h>

#include <cstring>

#include "xenia/base/assert.h"
#include "xenia/base/logging.h"
#include "xenia/base/string.h"
#include "xenia/base/system.h"

// Use headers in third party to not depend on system sdl headers for building
#include "third_party/SDL2/include/SDL.h"

namespace xe {

void LaunchWebBrowser(const std::string_view url) {
  auto cmd = std::string("xdg-open ");
  cmd.append(url);
  system(cmd.c_str());
}

void LaunchFileExplorer(const std::filesystem::path& path) { assert_always(); }

const char* TitleForMessageBoxType(SimpleMessageBoxType type) {
  switch (type) {
    case SimpleMessageBoxType::Help:
      return "Xenia Help";
    case SimpleMessageBoxType::Warning:
      return "Xenia Warning";
    case SimpleMessageBoxType::Error:
      return "Xenia Error";
  }
}

Uint32 FlagsForMessageBoxType(SimpleMessageBoxType type) {
  switch (type) {
    case SimpleMessageBoxType::Help:
      return SDL_MESSAGEBOX_INFORMATION;
    case SimpleMessageBoxType::Warning:
      return SDL_MESSAGEBOX_WARNING;
    case SimpleMessageBoxType::Error:
      return SDL_MESSAGEBOX_ERROR;
  }
}

char* StringViewToCharPointer(std::string_view original) {
  char* converted = reinterpret_cast<char*>(alloca(original.size() + 1));
  std::memcpy(converted, original.data(), original.size());
  converted[original.size()] = '\0';
  return converted;
}

void ShowSimpleMessageBox(SimpleMessageBoxType type, std::string_view message) {
  void* libsdl2 = dlopen("libSDL2.so", RTLD_LAZY | RTLD_LOCAL);
  assert_not_null(libsdl2);
  if (libsdl2) {
    auto* pSDL_ShowSimpleMessageBox =
        reinterpret_cast<decltype(SDL_ShowSimpleMessageBox)*>(
            dlsym(libsdl2, "SDL_ShowSimpleMessageBox"));
    assert_not_null(pSDL_ShowSimpleMessageBox);
    if (pSDL_ShowSimpleMessageBox) {
      const Uint32 flags = FlagsForMessageBoxType(type);
      const char* title = TitleForMessageBoxType(type);
      char* message_copy = StringViewToCharPointer(message);
      pSDL_ShowSimpleMessageBox(flags, title, message_copy, NULL);
    }
    dlclose(libsdl2);
  }
}

}  // namespace xe
