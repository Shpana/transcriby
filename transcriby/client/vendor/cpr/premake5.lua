project "cpr"
	kind "StaticLib"
    language "C++"
    cppdialect "C++17"
	staticruntime "Off"
	
	targetdir ("%{wks.location}/bin/" .. output_dir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. output_dir .. "/%{prj.name}")

	warnings "Off"

    includedirs {
		for_include["curl"],
		for_include["cpr"],
    }

    files {
    	"cpr/*.cpp"
    }

    defines	{
    	"CURL_STATICLIB",
    }

    links {
    	"curl" -- link to libcurl.so
    }

	--- Platform ---
	filter "system:windows"
		systemversion "latest"
		defines {
			"_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS"
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
