{
    files = {
        [[build\.objs\main\windows\x64\release\wrapper.asm.obj]],
        [[build\.objs\main\windows\x64\release\main.cpp.obj]],
        "version.def"
    },
    values = {
        [[C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\HostX64\x64\link.exe]],
        {
            "-nologo",
            "-machine:x64",
            "/def:version.def"
        }
    }
}