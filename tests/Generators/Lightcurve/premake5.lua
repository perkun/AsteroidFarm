project "LightcurveTests"
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
		"%{wks.location}/Generators/Lightcurve/src/LightcurveScene.cpp"
	}

	includedirs
	{
 		"%{prj.name}/src",
		"%{wks.location}/vendor/fmt/",
		"%{wks.location}/Generators/Lightcurve/src"
	}

	links { "Core", "fmt", "gtest", "glfw", "glad", "pthread"}

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
