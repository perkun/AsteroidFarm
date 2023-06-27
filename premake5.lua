workspace "Sage"
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
			  "%{wks.location}/Sage/src",
			  "%{wks.location}/Sage/src/**",
            }

include "vendor/glad"
include "vendor/glfw"
include "Sage"
include "Sandbox"
include "Generators/Lightcurve"
include "Generators/AdaptiveOptics"

-- TESTS --
include "tests/Sage"
include "tests/Generators/Lightcurve"

-- DOCS --
-- include "documentation"
