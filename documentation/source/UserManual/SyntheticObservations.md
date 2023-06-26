# Synthetic observation generation

You can use certain project's within Sage to generate synthetic observations based on config files.

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

`eclipticLongitude` and `eclipticLatitude` in degrees define spin axis orientation in ecliptic
reference frame. The rotation is defined by rotation phase (`rotPhaseForEpoch`, in degrees) at an
Julian Day `epoch`, and a rotation `period` in hours.

## Lightcurves

**Work in progress**

## Adaptive Optics

**Work in progress**

## Radar delay-Doppler

**Work in progress**

