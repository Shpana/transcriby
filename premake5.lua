workspace "transcriby"
    architecture "x64"
    startproject "transcriby/client"

    configurations {
        "Debug", 
        "Release",
    }

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

for_include = {}
-- Audio
for_include["irrklang"] = "%{wks.location}/transcriby/client/vendor/irrklang/include"
-- UI and Graphics
for_include["imgui"] = "%{wks.location}/transcriby/client/vendor/imgui"
for_include["imgui-filebrowser"] = "%{wks.location}/transcriby/client/vendor/imgui-filebrowser"
for_include["imgui-sfml"] = "%{wks.location}/transcriby/client/vendor/imgui-sfml"
for_include["sfml"] = "%{wks.location}/transcriby/client/vendor/sfml/include"
-- Networking
for_include["curl"] = "%{wks.location}/transcriby/client/vendor/curl/include"
for_include["cpr"] = "%{wks.location}/transcriby/client/vendor/cpr/include"

libs = {}
-- Audio
libs["irrklang"] = "%{wks.location}/transcriby/client/vendor/irrklang/lib"
-- UI and Graphics
libs["sfml"] = "%{wks.location}/transcriby/client/vendor/sfml/lib"

bins = {} 
--Audio
bins["irrklang"] = "%{wks.location}/transcriby/client/vendor/irrklang/bin"

-- Visual Studio PDB files
pdbs = {}
pdbs["sfml"] = "%{wks.location}/transcriby/client/vendor/sfml/lib/Debug"

group "dependencies"
    include "transcriby/client/vendor/curl"
    include "transcriby/client/vendor/cpr"
    include "transcriby/client/vendor/imgui"
    include "transcriby/client/vendor/imgui-sfml"
group ""

group "app"
    include "transcriby/client"
group ""
