#How tos

## How to build Sage

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
