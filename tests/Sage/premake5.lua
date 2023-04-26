project "SageTests"
	location "./"
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++2a"
	buildoptions { }

	targetdir ("%{wks.location}/tests/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/tests/build/" .. outputdir  .. "/%{prj.name}")

	--pchheader "src/svpch.h"

	files
	{
		"src/**.h",
		"src/**.cpp",
		--"vendor/stb_image/**.h",
	}

	includedirs
	{
 		"%{prj.name}/src",
        "%{wks.location}/Sage/src/",
		"%{wks.location}/vendor/fmt/",
 		--"vendor/cppargs/src",
	}

	links { "Sage", "fmt", "gtest", "glfw", "glad", "pthread"}

	filter "configurations:Debug"
		symbols "On"
		defines "SAGE_DEBUG"
		--defines "..."

	filter "configurations:Release"
		optimize "On"
		defines "SAGE_RELEASE"
		--defines "..."

	filter "configurations:Dist"
		optimize "On"
		--defines "..."
