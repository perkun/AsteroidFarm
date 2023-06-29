project "Sandbox"
	location "./"
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++2a"
	buildoptions { }

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/" .. outputdir  .. "/%{prj.name}")

	--pchheader "src/svpch.h"

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
 		"%{prj.name}/src",
	}

	links { "Core", "glfw", "glad", "fmt", "pthread", "dl" }

	filter "configurations:Debug"
		symbols "On"
		defines "AF_DEBUG"
		--defines "..."

	filter "configurations:Release"
		optimize "On"
		defines "AF_RELEASE"
		--defines "..."

	filter "configurations:Dist"
		optimize "On"
		--defines "..."
