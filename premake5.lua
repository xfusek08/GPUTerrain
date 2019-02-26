workspace "GPUTerrain"
	architecture "x64"
	startproject "GPUTerrain"

	configurations
	{
		"Debug",
		"Release"
	}

project "GPUTerrain"
	location "GPUTerrain"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

  objdir ("bin-objs")

  configuration "Debug"
    targetdir "bin/debug"

  configuration "Release"
    targetdir "bin/release"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
    "src/"
	}

	links
	{
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"
