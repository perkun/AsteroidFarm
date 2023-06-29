workspace "AsteroidFarm"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}"
includedirs { "%{wks.location}/vendor/glm",
              "%{wks.location}/vendor/nlohmann",
              "%{wks.location}/vendor/glad/include",
              "%{wks.location}/vendor/glfw/include",
			  "%{wks.location}/vendor/entt/",
              "%{wks.location}/vendor/stb_image",
			  "%{wks.location}/Core/src",
			  "%{wks.location}/Core/src/**",
            }

include "vendor/glad"
include "vendor/glfw"
include "Core"
include "Sandbox"
include "Generators/Lightcurve"
include "Generators/AdaptiveOptics"
include "Generators/Radar"

-- TESTS --
include "tests/Core"
include "tests/Generators/Lightcurve"

-- DOCS --
-- include "documentation"
