-- # This file is inspired from premake5 https://github.com/premake/premake-core/blob/master/contrib/curl/premake5.lua AND https://github.com/multitheftauto/mtasa-blue/tree/master/vendor/curl
project "curl"
	kind "StaticLib"
    language "C"
    --cdialect "C11" [C11 result in error: lib/hostip.h:205:8: error: unknown type name ‘sigjmp_buf’  205 | extern sigjmp_buf curl_jmpenv; | see https://github.com/baderouaich/Enigma/runs/2035170343]
	staticruntime "Off"

    targetdir ("%{wks.location}/bin/" .. output_dir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. output_dir .. "/%{prj.name}")

	warnings "Off"

    includedirs {
     	"include/", 
     	"lib/",
    }

    files {
		"**.h",
		"**.c"
	}

	excludes {
		"lib/amigaos.c",
		"lib/amigaos.h",
		"lib/config-amigaos.h",
		"lib/config-dos.h",
		"lib/config-mac.h",
		"lib/config-os400.h",
		"lib/config-riscos.h",
		"lib/config-symbian.h",
		"lib/config-tpf.h",
		"lib/config-win32ce.h",
		"lib/config-vxworks.h",
		"lib/setup-os400.h",
		"lib/setup-vms.h"
	}

	defines {
        "BUILDING_LIBCURL",
        "CURL_STATICLIB", 
        "HTTP_ONLY", 
        "HAVE_CONFIG_H"

    }

	--- Platform ---
	filter "system:windows"
		systemversion "latest"
		defines {
			"_WINSOCK_DEPRECATED_NO_WARNINGS",
			"USE_SCHANNEL", 
			"USE_WINDOWS_SSPI",
			"USE_WIN32_IDN", 
			"WANT_IDN_PROTOTYPES"
		}

		linkoptions {
			"/ignore:4006" -- "/ignore:4006,4006,..." -- Normaliz.lib has already linked to all bellow, this will give warning LNK4006: __NULL_IMPORT_DESCRIPTOR, ignore it
		}

		links {
			-- WARNING! Order Matters. --
	 		"Normaliz", 
	 		"Ws2_32", 
	 		"Crypt32",
	 		"Wldap32",
	    }
	  
	--- Configurations ---
	filter "configurations:Debug"
		runtime "Debug"
		symbols "Full" --vs17 and newer | symbols "On"
		optimize "Off" -- No optimization will be performed.

	filter "configurations:Release"
		runtime "Release"
		optimize "On" -- Perform a balanced set of optimizations.
		inlining "Explicit" -- Only inline functions explicitly marked with the inline keyword.
