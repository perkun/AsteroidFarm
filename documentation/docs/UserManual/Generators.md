# Synthetic observation generation

There are standalone programs for the purpuse of generating synthetic observations. Programs accept
a path to input config file as a parameter and generate observations accordingly.

### Lightcurves

Project location: `Generators/Lightcurve`

Config file Example:

```json
{
    "scene": {
        "modelPath": "data/asteroid.obj",
        "vertexShaderPath": "data/shadow.vs",
        "fragmentShaderPath": "data/shadow.fs"
    },
    "asteroidParams": {
        "name": "Test target name",
        "eclipticLongitude": 170,
        "eclipticLatitude": 70,
        "period": 12.123,
        "epoch": 2457999.0334,
        "rotPhaseForEpoch": 44.123
    },
    "lightcurves": [
        {
            "targetPosition": [0,4,0],
            "observerPosition": [2, 0, 0],
            "lightPosition": [0, 0, 0],
            "startJd": 2458009.0334,
            "numPoints": 90
        }
    ],
    "outputPath": "data/myLightcurves.json"
}
```

The output will be saved in a file defined by `outputPath` parameter. It looks like that:

```json
{
    "asteroidParams": {
        "eclipticLatitude": 0.0,
        "eclipticLongitude": 0.0,
        "epoch": 0.0,
        "name": "",
        "period": 0.0,
        "rotPhaseForEpoch": 0.0
    },
    "scene": {
        "fragmentShaderPath": "",
        "modelPath": "",
        "vertexShaderPath": ""
    },
    "lightcurves": [
        [
            {
                "julianDay": 2458009.0334,
                "magnitude": -10.336428851339793,
                "observerPosition": [
                    2.0,
                    0.0,
                    0.0
                ],
                "rotPhase": 5.0082009092861455,
                "step": 0,
                "targetPosition": [
                    0.0,
                    4.0,
                    0.0
                ]
            },
    ...
```

It contains `AsteroidConfig`, information about the scene and array of lightcurves, which are the
arrays of observation points.

### Adaptive Optics

Project location: `Generators/AdaptiveOptics`

Adaptive Optics images are just images of a target as visible from the observer's position.


Config file example:

```json
{
    "scene": {
        "modelPath": "data/model_shifted.obj",
        "vertexShaderPath": "data/shadow.vs",
        "fragmentShaderPath": "data/shadow.fs"
    },
    "asteroidParams": {
        "name": "Test target name",
        "eclipticLongitude": 170,
        "eclipticLatitude": 70,
        "period": 12.123,
        "epoch": 2457999.0334,
        "rotPhaseForEpoch": 74.123
    },
    "aoImages": [
        {
            "targetPosition": [0,4,0],
            "observerPosition": [2, 0, 0],
            "lightPosition": [0, 0, 0],
            "jd": 2458009.0334,
            "imageSize": 512
        },
        {
            "targetPosition": [0,4,0],
            "observerPosition": [2, 2, 1],
            "lightPosition": [0, 0, 0],
            "jd": 2458011.0334,
            "imageSize": 100
        }

    ],
    "outputFolderPath": "data/AoImages/",
    "imagePrefix": "test"
}
```

The AO images will be saved as `.png` files named `<outputFolderPath>/<imagePrefix>_<i>.png`, where
`i` is a consecutive index of an image.

### Radar delay-Doppler

**Work in progress**


