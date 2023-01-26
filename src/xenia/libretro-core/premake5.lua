project_root = "../../../.."
include(project_root.."/tools/build")

group("src")
project("xenia-libretro-core")
  uuid("4d872bf7-2a02-4816-b51f-52628ba5335d")
  kind("SharedLib")
  language("C++")
  links({
  })
  defines({
  })
  includedirs({
  })
  files({
    "libretro.cc",
    "libretro.h"
  })
