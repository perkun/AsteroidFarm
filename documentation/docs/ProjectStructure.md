# Project's structure

`premake5` is used as underlying build system.
Sage is organized into workspace and projects. The `premake5.lua` file in root
directory defines the workspace, global include directories and includes
individual projects. Projects are stored in separate directories, each
containing its own `premake5.lua` file.

## External libraries

Libraries used in projects should be stored in `vendor` folder. Rules for
building can be added to the premake file stored there.


## Documentation

Documentation is stored in `documentation/source` folder. The `index.md` is the main
page.

Documentation is generated automatically when the whole projetc is build. You
need to have `mkdocs` installed. See dependencies
section.

To generate documentation locally:

```
cd docs
make
```
then open `documentation/build/html/index.html` in a web browser.

# Dependencies

* fmt
* gtest
* mkdocs



