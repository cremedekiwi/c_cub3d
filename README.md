# cub3D

A 3D raycasting game engine inspired by Wolfenstein 3D. This project demonstrates fundamental computer graphics concepts including raycasting, texture mapping, and real-time rendering.

<img src="https://raw.githubusercontent.com/cremedekiwi/c_cub3d/refs/heads/main/gif.gif" alt="Animation">

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Map Format](#map-format)
- [Project Structure](#project-structure)
- [Bonus Features](#bonus-features)
- [Technical Details](#technical-details)
- [Dependencies](#dependencies)
- [Authors](#authors)

## Features

### Mandatory Features

- **Raycasting Engine**: Lightweight 2.5D rendering system
- **First-Person View**: Navigate through a 3D environment
- **Textured Walls**: Support for XPM texture files
- **Smooth Movement**: WASD movement with arrow key rotation
- **Collision Detection**: Players cannot walk through walls
- **Customizable Maps**: Load levels from `.cub` configuration files
- **Color Mapping**: Configurable floor and ceiling colors
- **Minimap**: Real-time minimap display showing player position and field of view

### Bonus Features

- **Interactive Doors**: Press 'E' to toggle doors open/closed
- **Mouse Look**: Look around using mouse movement
- **Animated Torch**: Flickering torch animation in the corner
- **Sprint Mode**: Hold Shift to move faster
- **Enhanced Graphics**: Additional visual effects and improvements

## Installation

### Prerequisites

- GCC compiler
- Make
- X11 development libraries (Linux)
- MLX (MiniLibX) graphics library

### Clone and Build

```bash
git clone https://github.com/cremedekiwi/c_cub3d.git cub3d
cd cub3d
make
```

For bonus version:

```bash
make bonus
```

## Usage

### Basic Usage

```bash
./cub3d [map_file.cub]
```

### Example

```bash
./cub3d maps/mandatory/valid/map_cave.cub
```

### Bonus Version

```bash
./cub3d_bonus maps/bonus/valid/map_cave.cub
```

## Controls

| Key       | Action                 |
| --------- | ---------------------- |
| `W`       | Move forward           |
| `S`       | Move backward          |
| `A`       | Strafe left            |
| `D`       | Strafe right           |
| `←` / `→` | Rotate view left/right |
| `ESC`     | Exit game              |

### Bonus Controls

| Key       | Action       |
| --------- | ------------ |
| `E`       | Toggle doors |
| `Shift`   | Sprint mode  |
| **Mouse** | Look around  |

## Map Format

Map files use the `.cub` extension and follow this structure:

### Configuration Section

```
NO ./textures/north_wall.xpm    # North wall texture
SO ./textures/south_wall.xpm    # South wall texture
WE ./textures/west_wall.xpm     # West wall texture
EA ./textures/east_wall.xpm     # East wall texture
DO ./textures/door.xpm          # Door texture (bonus)

F 220,100,0                     # Floor color (RGB)
C 255,255,255                   # Ceiling color (RGB)
```

### Map Section

```
111111111
100000001
10N000001
100000001
111111111
```

### Map Characters

- `1`: Wall
- `0`: Empty space
- `N/S/E/W`: Player starting position and orientation
- `D`: Door (bonus feature)
- ` ` (space): Treated as wall for map boundaries

### Example Map File

```
NO ./textures/oak.xpm
SO ./textures/oak.xpm
WE ./textures/oak.xpm
EA ./textures/oak.xpm
DO ./textures/door.xpm

F 160,82,45
C 135,206,235

        11111111111
      11100000000111
     111000110100001
     100001100100001
   11101111000100001
  110000111111100001
  100000000000000011
  100E0011111111101
  10000000000000001
  11111111111111111
```

## Project Structure

```
cub3d/
├── includes/
│   ├── cub3d.h              # Main header
│   ├── cub3d_bonus.h        # Bonus header
│   └── libft.h              # Library header
├── sources/
│   ├── mandatory/           # Core implementation
│   │   ├── main.c
│   │   ├── raycasting.c
│   │   ├── render.c
│   │   ├── movement.c
│   │   ├── input.c
│   │   ├── parse.c
│   │   └── ...
│   └── bonus/               # Bonus features
│       ├── main_bonus.c
│       ├── door_bonus.c
│       ├── torch_bonus.c
│       └── ...
├── libft/                   # Custom C library
├── minilibx-linux/          # Graphics library
├── maps/                    # Example maps
│   ├── mandatory/
│   └── bonus/
├── textures/                # Texture files
└── Makefile
```

## Bonus Features

### Interactive Doors

- Doors can be opened and closed by pressing 'E'
- Must be within range of the door
- Doors are represented by 'D' in the map file
- Requires door texture specification with `DO` directive

### Mouse Controls

- Mouse movement controls camera rotation
- Mouse is automatically hidden and re-centered
- Smooth and responsive camera movement

### Animated Torch

- 11-frame torch animation in the bottom-right corner
- Creates atmospheric lighting effect
- Frames automatically cycle for realistic flame movement

### Sprint Mode

- Hold Left Shift to move 5x faster
- Useful for quickly traversing large maps
- Works with all movement directions

## Technical Details

### Raycasting Algorithm

The engine uses a DDA (Digital Differential Analyzer) algorithm to cast rays from the player's position and determine wall intersections. Key components:

- **Ray Casting**: Calculates intersections with horizontal and vertical grid lines
- **Wall Rendering**: Projects 3D walls onto 2D screen space
- **Texture Mapping**: Maps texture coordinates to screen pixels
- **Distance Correction**: Prevents fisheye effect using cosine correction

### Performance Optimizations

- Efficient ray-to-wall intersection detection
- Optimized texture sampling
- Minimal memory allocations during runtime
- Hardware-accelerated rendering via MLX

### Map Validation

The engine performs comprehensive map validation:

- Ensures map is closed (surrounded by walls)
- Validates texture file existence and format
- Checks color value ranges (0-255)
- Verifies single player starting position
- Flood-fill algorithm to detect open boundaries

## Dependencies

### Libraries

- **MLX (MiniLibX)**: Graphics and window management
- **libft**: Custom C standard library implementation
- **Math library**: For trigonometric calculations
- **X11 libraries**: Window system integration

## Building and Debugging

### Build Commands

```bash
make          # Build mandatory version
make bonus    # Build bonus version
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild everything
```

## Authors

- **habernar** - Core raycasting engine and rendering
- **jarumuga** - Bonus features and user interface
