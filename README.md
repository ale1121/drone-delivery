# Santa's Drone Delivery

A 3D drone delivery game implemented in C++ using OpenGL, featuring procedurally generated terrain, shader visual effects and collision detection

Developed as part of a computer graphics project using the [gfx-framework](https://github.com/UPB-Graphics/gfx-framework), with all scene elements generated programmatically from vertex data

![dronedelivery](https://github.com/user-attachments/assets/8371f907-5dfc-43da-a193-bf80758ab702)

## Gameplay

The player controls a drone that collects presents from a central Christmas tree and delivers them to randomly selected houses scattered across a snowy terrain.

Each successful delivery generates a new target location, requiring the player to navigate through obstacles while managing flight direction and thrust.

### Controls

- `Mouse` / `Arrow keys` - control drone direction
- `W`/`S` - increase/decrease thrust
- `Scroll wheel` - adjust field of view

### Graphics and features

- Procedural terrain generation using randomised noise patterns
- Vertex shader tree animation where trees dynamically bend away from the drone
- Fog rendering using fragment shaders
- Randomized obstacle placement for varied gameplay
- Collision detection preventing the drone from intersecting terrain or objects
- Score tracking based on delivery count and completion time

## Technical Details

- Implemented in C++ with OpenGL
- GLSL vertex and fragment shaders
- Scene geometry generated entirely from vertez data
- Built using [gfx-framework](https://github.com/UPB-Graphics/gfx-framework)

## Building and running
Follow the build instructions in the [gfx-framework repository](https://github.com/UPB-Graphics/gfx-framework?tab=readme-ov-file#gear-building). This project uses module 1. 

## Preview

https://github.com/user-attachments/assets/1f96132d-4b1b-4319-a261-f591dd551010
