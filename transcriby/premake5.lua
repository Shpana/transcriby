project "transcriby"
    kind "ConsoleApp"
    language "C++"
    staticruntime "Off"

    targetdir ("%{wks.location}/bin/" .. output_dir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. output_dir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs {
        "src/",

        for_include["curl"],
        for_include["cpr"],
        for_include["imgui"],
        for_include["imgui-filebrowser"],
        for_include["imgui-sfml"],
        for_include["sfml"],
        for_include["irrklang"],
    }

    links {
        "cpr",
        "imgui",
        "imgui-sfml",
    }

    libdirs {
        libs["sfml"],
        libs["irrklang"],
    }

    defines {
        "SFML_STATIC",
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        
        links {
            "opengl32",
            "winmm",
            "freetype",           
            "Winx64-visualStudio/irrklang.lib",
        }

        postbuildcommands {
            "{COPYFILE} %[%{bins['irrklang']}/Winx64-visualStudio/*.dll] %[%{!cfg.targetdir}]",
        }

    filter {"system:windows", "configurations:Debug"}
		runtime "Debug"
		symbols "on"

        links {
            "sfml-graphics-s-d.lib",
            "sfml-window-s-d.lib",
            "sfml-system-s-d.lib",
        }

        postbuildcommands {
            "{COPYFILE} %[%{pdbs['sfml']}/*.pdb] %[%{!cfg.objdir}]",
        }

	filter {"system:windows", "configurations:Release"}
		runtime "Release"
		optimize "on"

        links {
            "sfml-graphics-s.lib",
            "sfml-window-s.lib",
            "sfml-system-s.lib",
        }
