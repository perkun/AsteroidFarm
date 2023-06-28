# Config files

In this project configuration, input and output data is handled in JSON format. In the code writing
and parsing is done via [nlohmann json](https://github.com/nlohmann/json) library.


## Asteroid Parameters

`eclipticLongitude` and `eclipticLatitude` in degrees define spin axis orientation in ecliptic
reference frame. The rotation is defined by rotation phase (`rotPhaseForEpoch`, in degrees) at an
Julian Day `epoch`, and a rotation `period` in hours.

```json
"asteroidParams": {
    "eclipticLongitude": <deg>,
    "eclipticLatitude": <deg>,
    "period": <hours>,
    "epoch": <julian day>,
    "rotPhaseForEpoch": <deg>
}
```

## Scene

Scene config groups global scene stuff: path to 3D model and *OpenGl* shaders.

```json
"scene": {
    "fragmentShaderPath": "data/shadow.fs",
    "modelPath": "data/asteroid.obj",
    "vertexShaderPath": "data/shadow.vs"
}
```

## more to come...
