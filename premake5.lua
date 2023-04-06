workspace "Sage"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}"

--libdirs { "%{wks.location}/libs" }


--include "vendor"
include "Sage"
include "Sandbox"


-- TESTS --
include "tests/Sage"
