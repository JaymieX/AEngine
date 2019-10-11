workspace "AEngine"
	architecture "x64"

	configurations {
		"Debug",
		"Release"
	}

outputdir = "%{cfg.system}_%{cfg.buildcfg:lower()}_%{cfg.architecture}"

local GLFW_DIR = "AEngine/external/glfw"
local GLAD_DIR = "AEngine/external/glad"

project "AEngine"
	location "AEngine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	pchheader "AEpch.h"
	pchsource "%{prj.name}/src/AEpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/external/glm/glm",
		path.join(GLAD_DIR, "include"),
		path.join(GLFW_DIR, "include"),
	}

	links 
	{
		"glad",
		"glfw",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		optimize "Debug"

	filter "configurations:Release"
		symbols "Off"
		optimize "Full"


project "glfw"
	kind "StaticLib"
	language "C"
	location (GLFW_DIR)

	targetdir (GLFW_DIR .. "/bin/" .. outputdir .. "/%{prj.name}")
	objdir (GLFW_DIR .. "/build/" .. outputdir .. "/%{prj.name}")

	files
	{
		path.join(GLFW_DIR, "include/GLFW/*.h"),
		path.join(GLFW_DIR, "src/context.c"),
		path.join(GLFW_DIR, "src/egl_context.*"),
		path.join(GLFW_DIR, "src/init.c"),
		path.join(GLFW_DIR, "src/input.c"),
		path.join(GLFW_DIR, "src/internal.h"),
		path.join(GLFW_DIR, "src/monitor.c"),
		path.join(GLFW_DIR, "src/osmesa_context.*"),
		path.join(GLFW_DIR, "src/vulkan.c"),
		path.join(GLFW_DIR, "src/window.c"),
	}
	includedirs { path.join(GLFW_DIR, "include") }
	filter "system:windows"
		defines "_GLFW_WIN32"
		files
		{
			path.join(GLFW_DIR, "src/win32_*.*"),
			path.join(GLFW_DIR, "src/wgl_context.*")
		}
	filter "system:linux"
		defines "_GLFW_X11"
		files
		{
			path.join(GLFW_DIR, "src/glx_context.*"),
			path.join(GLFW_DIR, "src/linux*.*"),
			path.join(GLFW_DIR, "src/posix*.*"),
			path.join(GLFW_DIR, "src/x11*.*"),
			path.join(GLFW_DIR, "src/xkb*.*")
		}
	filter "action:vs*"
		defines "_CRT_SECURE_NO_WARNINGS"

project "glad"
	kind "StaticLib"
	language "C"
	location (GLAD_DIR)

	targetdir (GLAD_DIR .. "/bin/" .. outputdir .. "/%{prj.name}")
	objdir (GLAD_DIR .. "/build/" .. outputdir .. "/%{prj.name}")

	files
	{
		path.join(GLAD_DIR, "include/glad/glad.h"),
		path.join(GLAD_DIR, "include/KHR/khrplatform.h"),
		path.join(GLAD_DIR, "src/glad.c"),
	}

	includedirs { path.join(GLAD_DIR, "include") }

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "action:vs*"
		defines "_CRT_SECURE_NO_WARNINGS"


