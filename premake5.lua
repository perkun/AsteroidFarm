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
            }

include "vendor/glad"
include "vendor/glfw"
include "Sage"
include "Sandbox"

-- TESTS --
include "tests/Sage"

-- DOCS --
--include "docs"
