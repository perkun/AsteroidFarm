# User Manual

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

## Asteroid Parameters

As part of each config (see sections below) you have to specify asteroid parameters as a JSON object, e.g.:

```json
"asteroidParams": {
    "eclipticLongitude": 170,
    "eclipticLatitude": -32,
    "period": 12.123,
    "epoch": 2457999.0334,
    "rotPhaseForEpoch": 34.123
}
```

## Synthetic observation generation

You can use certain project's within Sage to generate synthetic observations based on config files.


`eclipticLongitude` and `eclipticLatitude` in degrees define spin axis orientation in ecliptic
reference frame. The rotation is defined by rotation phase (`rotPhaseForEpoch`, in degrees) at an
Julian Day `epoch`, and a rotation `period` in hours.

### Lightcurves

**Work in progress**

### Adaptive Optics

**Work in progress**

### Radar delay-Doppler

**Work in progress**


