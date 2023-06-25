project "vendor"
kind "Makefile"

buildcommands {
    "sphinx-build -M html source build"
}

cleancommands {
    "{RMDIR} %{prj.location}/build;"
}
