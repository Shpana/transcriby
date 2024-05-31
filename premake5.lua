workspace "transcriby"
    architecture "x64"
    startproject "transcriby/client"

    configurations {
        "Debug", 
        "Release",
    }

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

for_include = {}
for_include["imgui"] = "%{wks.location}/transcriby/client/vendor/imgui"
for_include["imgui-sfml"] = "%{wks.location}/transcriby/client/vendor/imgui-sfml"
for_include["sfml"] = "%{wks.location}/transcriby/client/vendor/sfml/include"

libs = {}
libs["sfml"] = "%{wks.location}/transcriby/client/vendor/sfml/lib"

group "dependencies"
    include "transcriby/client/vendor/imgui"
    include "transcriby/client/vendor/imgui-sfml"
group ""

group "app"
    include "transcriby/client"
group ""
