workspace "Aurora"
	architecture "x64"
	startproject "Sandbox"

	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Aurora/vendor/GLFW/include"
IncludeDir["Glad"] = "Aurora/vendor/Glad/include"
IncludeDir["Imgui"] = "Aurora/vendor/imgui"
IncludeDir["glm"] = "Aurora/vendor/glm"

include "Aurora/vendor/GLFW"
include "Aurora/vendor/Glad"
include "Aurora/vendor/imgui"

project "Aurora"
	location "Aurora"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "arpch.h"
	pchsource "Aurora/src/arpch.cpp"

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs 
	{
		"%{prj.name}/src",	
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}", 
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.glm}"
	}

	links 
	{
		"GLFW",
		"Glad",
		"Imgui",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions "/utf-8"

		defines 
		{
			"AR_PLATFORM_WINDOWS",
			"AR_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug"
		defines {"AR_DEBUG", "AR_ENABLE_ASSERTS"}
		runtime "Debug"
		--buildoptions "/MDd"
		symbols "on"
		
	filter "configurations:Release"
		defines "AR_RELEASE"
		runtime "Release"
		--buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "AR_DIST"
		runtime "Release"
		--buildoptions "/MD"
		optimize "on"
		

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Aurora/src",
		"Aurora/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Aurora"
	}

	filter "system:windows"
		--staticruntime "On"
		systemversion "latest"
		buildoptions "/utf-8"

		defines 
		{
			"AR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AR_DEBUG"
		runtime "Debug"
		--buildoptions "/MDd"
		symbols "on"
		
	filter "configurations:Release"
		defines "AR_RELEASE"
		runtime "Release"
		--buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "AR_DIST"
		runtime "Release"
		--buildoptions "/MD"
		optimize "on"
