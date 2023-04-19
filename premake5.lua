workspace "Sage"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}"
includedirs { "%{wks.location}/vendor/glm", "%{wks.locaion}/vendor/nlohmann" }

--include "vendor"
include "Sage"
include "Sandbox"

-- TESTS --
include "tests/Sage"

-- DOCS --
include "docs"
