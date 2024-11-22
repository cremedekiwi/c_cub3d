# cub3d
## Introduction
**Cub3D** is a project inspired by the classic game **Wolfenstein 3D**, designed as a raycasting engine built for a 2D map rendering in a pseudo-3D perspective. It is an educational project that demonstrates an understanding of basic game development concepts like rendering, movement, and collision detection.

## Features

- **Raycasting Engine:** A lightweight raycasting engine for 2.5D rendering.
- **Dynamic Player Movement:** Smooth and responsive controls.
- **Collision Detection:** Players can't walk through walls.
- **Customizable Maps:** Support for user-defined levels via `.cub` files.
- **Textured Walls:** Rendered with specified textures for walls.
- **Minimap Display:** View a small map to guide the player.

## Installation
### Prerequisites
### Clone the Repository

```bash
git clone https://github.com/cremedekiwi/c_cub3d.git cub3d
cd cub3d
```

### Build the Project
Run the following command in the project directory:

```bash
make
```

This will compile the project and generate the executable `cub3D`.

## Usage
Run Cub3D using the following command:

```bash
./cub3D [map_file.cub]
```

Replace `[map_file.cub]` with the path to a valid `.cub` file containing the map configuration.

### Example
```bash
./cub3D maps/example_map.cub
```

## Controls
| Key                | Action                   |
|--------------------|--------------------------|
| `W` / `Arrow Up`   | Move forward             |
| `S` / `Arrow Down` | Move backward            |
| `A`                | Strafe left              |
| `D`                | Strafe right             |
| `Left Arrow`       | Rotate view left         |
| `Right Arrow`      | Rotate view right        |
| `ESC`              | Exit the game            |

## Development

### Map File Format

Map files have a `.cub` extension and must follow these rules:

1. **Textures:** Specify paths to texture files for walls (e.g., `NO texture_north.xpm`).
2. **Colors:** Define floor and ceiling colors (e.g., `F 220,100,0` for floor).
3. **Map Layout:** Use `1` for walls, `0` for empty spaces, and `N, E, S, W` for the player’s starting position.

Example `.cub` file:
```
R 1024 768
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 255,255,255

111111
100001
100N01
100001
111111
```
