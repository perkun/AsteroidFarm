project "vendor"
kind "Makefile"

buildcommands {
    "sphinx-build -M html source build",
    "rm -r ../docs",
    "cp -r build/html ../docs",
    "touch ../docs/.nojekyll"
}

cleancommands {
    "{RMDIR} %{prj.location}/build;"
}
