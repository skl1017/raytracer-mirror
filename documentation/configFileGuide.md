# Raytracer Configuration Guide

This project uses libconfig-style `.cfg` files to describe the scene. The main configuration sections are:

- `materials`
- `primitives`
- `lights`
- `cameras`

Each section is parsed by a dedicated parser in `src/Parser`.

---

## 1. materials

The `materials` section defines named materials that primitives can use.

Current supported type:
- `flatColor`

Example:

```cfg
materials = {
    flatColor = (
        {
            name = "red";
            color = { r = 1.0; g = 0.0; b = 0.0; };
            transparency = 0;
            reflection = 10;
        },
        {
            name = "white";
            color = { r = 1.0; g = 1.0; b = 1.0; };
            transparency = 0;
            reflection = 0;
        }
    );
};
```

Required fields for `flatColor`:
- `name`: material identifier used by primitives
- `color`: RGB values in `[0, 1]`
- `transparency`: integer transparency amount
- `reflection`: integer reflection amount

---

## 2. primitives

The `primitives` section contains objects in the scene.
The supported primitive types are:
- `spheres`
- `planes`
- `cylinders`
- `cones`

### Sphere example

```cfg
primitives = {
    spheres = (
        { position = { x = 0.0; y = 10.0; z = 0.0; }; r = 6.0; material = "white"; }
    );
};
```

Fields:
- `position`: object center
- `r`: radius
- `material`: material name defined in `materials`

### Plane example

```cfg
primitives = {
    planes = (
        {
            material = "mirror";
            position = 35.0;
            rotation = { x = 1.5708; y = 0; z = 0; };
        }
    );
};
```

Fields:
- `material`: material name
- `position`: distance along the plane normal
- `rotation`: Euler rotation in radians

Notes for planes:
- rotation is stored as Euler angles `x`, `y`, `z`
- values are in radians
- rotation is applied as X then Y then Z

### Cylinder example

```cfg
primitives = {
    cylinders = (
        {
            position = { x = 10.0; y = 10.0; z = 10.0; };
            rotation = { x = 0; y = 0; z = 0; };
            radius = 4.5;
            height = 1;
            material = "green";
        }
    );
};
```

Fields:
- `position`: base or object position
- `rotation`: Euler angles in radians
- `radius`: cylinder radius
- `height`: cylinder height
- `material`: material name

### Cone example

```cfg
primitives = {
    cones = (
        {
            position = { x = 0.0; y = 100.0; z = 0.0; };
            rotation = { x = 0; y = 0; z = 0; };
            radius = 2;
            height = 10;
            material = "green";
        }
    );
};
```

Fields:
- `position`: cone position
- `rotation`: Euler angles in radians
- `radius`: base radius
- `height`: cone height
- `material`: material name

---

## 3. lights

Light blocks must use the exact parser type names:
- `point`
- `directional`

### Point light example

```cfg
lights = {
    point = (
        {
            x = 0;
            y = 50;
            z = 0;
            color = { r = 1; g = 1; b = 1; };
        }
    );
};
```

Fields:
- `x`, `y`, `z`: light position
- `color`: RGB values

### Directional light example

```cfg
lights = {
    directional = (
        {
            direction = { x = 1; y = -0.9; z = 0; };
            color = { r = 0.9; g = 0.35; b = 0.55; };
        }
    );
};
```

Fields:
- `direction`: light direction vector
- `color`: RGB values

---

## 4. cameras

Cameras are defined in a list and support the following fields:

```cfg
cameras = (
    {
        position = { x = 0.0; y = 30.0; z = -25.0; };
        rotation = { x = 0.3; y = 0.0; z = 0.0; w = 1.0; };
        fieldOfView = 70.0;
        resolution = { width = 1920; height = 1080; };
    }
);
```

Fields:
- `position`: camera location
- `rotation`: quaternion `x`, `y`, `z`, `w`
- `fieldOfView`: vertical FOV in degrees
- `resolution.width`: output width
- `resolution.height`: output height

---

## Important notes

- `rotation` for primitives is Euler angles in radians.
- `rotation` for cameras is a quaternion with `x`, `y`, `z`, `w`.
- `material` names must match exactly the `name` values in `materials`.
- Light section names are singular: `point` and `directional`.
- If a field is missing or misspelled, the parser may fail or ignore the object.

---

## Minimal valid config example

```cfg
materials = {
    flatColor = (
        {
            name = "white";
            color = { r = 1.0; g = 1.0; b = 1.0; };
            transparency = 0;
            reflection = 0;
        }
    );
};

primitives = {
    planes = (
        {
            material = "white";
            position = 0.0;
            rotation = { x = 0; y = 0; z = 0; };
        }
    );
};

lights = {
    directional = (
        {
            direction = { x = 0; y = -1; z = 0; };
            color = { r = 1; g = 1; b = 1; };
        }
    );
};

cameras = (
    {
        position = { x = 0.0; y = 5.0; z = -20.0; };
        rotation = { x = 0.0; y = 0.0; z = 0.0; w = 1.0; };
        fieldOfView = 70.0;
        resolution = { width = 1920; height = 1080; };
    }
);
```
