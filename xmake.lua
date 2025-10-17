set_project("FC4RemoveLangRetriction")
set_version("1.0.0")
set_languages("c++17")

set_arch("x64")

target("main")
    set_kind("shared")
    set_filename("version.dll")
    add_files("main.cpp", "wrapper.asm", "version.def")
    after_build(function (target)
        import("core.project.config")
        import("core.project.project")

        local src = path.join(os.projectdir(), "lang_fix.ini")
        local dst = path.join(target:targetdir(), "lang_fix.ini")

        os.cp(src, dst)
        print("Copied lang_fix.ini to build directory.")
    end)
