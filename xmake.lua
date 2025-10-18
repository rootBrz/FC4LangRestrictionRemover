set_project("FC4RemoveLangRetriction")
set_version("1.0.0")
set_languages("c++17")

set_arch("x64")

target("main")
    set_kind("shared")
    set_filename("version.dll")
    add_files("main.cpp", "wrapper.asm", "version.def")
    add_links("Advapi32")
