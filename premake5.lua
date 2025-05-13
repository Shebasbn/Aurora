workspace "Aurora"
	architecture "x64"
	startproject "Sandbox"

	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Aurora/vendor/GLFW/include"
IncludeDir["Glad"] = "Aurora/vendor/Glad/include"

include "Aurora/vendor/GLFW"
include "Aurora/vendor/Glad"

project "Aurora"
	location "Aurora"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "arpch.h"
	pchsource "Aurora/src/arpch.cpp"

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}", 
		"%{IncludeDir.Glad}"
	}

	links 
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions {"/utf-8", "/MD"}

		defines 
		{
			"AR_PLATFORM_WINDOWS",
			"AR_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines {"AR_DEBUG", "AR_ENABLE_ASSERTS"}
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "AR_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "AR_DIST"
		buildoptions "/MD"
		optimize "On"

	filter { "system:windows", "configurations:Release"}
		

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Aurora/vendor/spdlog/include",
		"Aurora/src"
	}

	links
	{
		"Aurora"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions "/utf-8"

		defines 
		{
			"AR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AR_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "AR_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "AR_DIST"
		buildoptions "/MD"
		optimize "On"
