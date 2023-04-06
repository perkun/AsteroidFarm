project "vendor"
kind "Makefile"

buildcommands {
    "{MKDIR} %{prj.location}/fmt/build; {CHDIR} %{prj.location}/fmt/build; cmake -DBUILD_SHARED_LIBS=TRUE ..;  make; {COPY} libfmt.so* ../../../libs/"
}

cleancommands {
    "{RMDIR} %{wks.location}/vendor/fmt/build;"
}
