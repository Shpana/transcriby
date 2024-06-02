workspace "transcriby"
    architecture "x64"
    startproject "transcriby"

    configurations {
        "Debug", 
        "Release",
    }

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

for_include = {}
-- Audio
for_include["irrklang"] = "%{wks.location}/transcriby/vendor/irrklang/include"
-- UI and Graphics
for_include["imgui"] = "%{wks.location}/transcriby/vendor/imgui"
for_include["imgui-filebrowser"] = "%{wks.location}/transcriby/vendor/imgui-filebrowser"
for_include["imgui-sfml"] = "%{wks.location}/transcriby/vendor/imgui-sfml"
for_include["sfml"] = "%{wks.location}/transcriby/vendor/sfml/include"
-- Networking
for_include["curl"] = "%{wks.location}/transcriby/vendor/curl/include"
for_include["cpr"] = "%{wks.location}/transcriby/vendor/cpr/include"

libs = {}
-- Audio
libs["irrklang"] = "%{wks.location}/transcriby/vendor/irrklang/lib"
-- UI and Graphics
libs["sfml"] = "%{wks.location}/transcriby/vendor/sfml/lib"

bins = {} 
--Audio
bins["irrklang"] = "%{wks.location}/transcriby/vendor/irrklang/bin"

-- Visual Studio PDB files
pdbs = {}
pdbs["sfml"] = "%{wks.location}/transcriby/vendor/sfml/lib/Debug"

group "dependencies"
    include "transcriby/vendor/curl"
    include "transcriby/vendor/cpr"
    include "transcriby/vendor/imgui"
    include "transcriby/vendor/imgui-sfml"
group ""

group "app"
    include "transcriby"
group ""
