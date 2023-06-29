# Project's structure

## Build system

`premake5` is used as underlying build system. Asteroid Farm is organized into workspace and
projects. The `premake5.lua` file in root directory defines the workspace, global include
directories and includes individual projects. Projects are stored in separate directories, each
containing its own `premake5.lua` file. `premage5` generates a *master* `Makefile` that includes
`Makefile`s of each project.

## External libraries

Libraries used in projects should be stored in `vendor` folder. Rules for
building can be added to the premake file stored there.


## Documentation

Documentation is stored in `documentation/` folder.  The `index.md` is the main
page.

Documentation is generated automatically when the whole projetc is build. You need to have
`mkdocs-material` installed:

```sh
pip install mkdocs-material
```

To generate documentation locally:

```
cd docs
make
```

The output files will be generated in `docs` folder, which is also under version control. After
updating documentation and building it, commit the changes in `docs` folder as well.

# Dependencies

* fmt
* gtest
* mkdocs-material



