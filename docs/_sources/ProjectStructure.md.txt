# Project's structure

`premake5` is used as underlying build system.
Sage is organized into workspace and projects. The `premake5.lua` file in root
directory defines the workspace, global include directories and includes
individual projects. Projects are stored in separate directories, each
containing its own `premake5.lua` file.

## External libraries

Libraries used in projects should be stored in `vendor` folder. Rules for
building can be added to the premake file stored there.

# How to build Sage

First, you need to generate `Makefile`s. To do so, run this command in project's root directory:

```
tools/linux/premake5 gmake
```

and then just run

```
make
```

to build the whole project. The default cofiguration is `Debug`. To build
`Release` configuration run

```
make config=release
```

Binaries are located in `build/<Target>/<Project>` directory, where `<Target>`
is either `Build` or `Release`.

# Documentation

Documentation is stored in `docs/source` folder. The `index.rst` is the main
page. You can link other files in `toc` section in either rst or markdown
formats.

Documentation is generated automatically when the whole projetc is build. You
need to have `Sphinx` installed (with some extra packages). See dependencies
section.


# Dependencies

* fmt
* gtest
* [sphinx](https://www.sphinx-doc.org/)
* [myst-parser](https://www.sphinx-doc.org/en/master/usage/markdown.htm)
* [sphinx-rtd-theme](https://sphinx-themes.org/sample-sites/sphinx-rtd-theme/)



