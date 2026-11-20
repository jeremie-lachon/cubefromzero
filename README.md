# cubefromzero

A first-person 3D raycasting engine written from scratch in C, in the style of Wolfenstein 3D. It renders a textured 3D view from a 2D grid map in real time.

Built by [1darko](https://github.com/1darko) and [jeremie-lachon](https://github.com/jeremie-lachon).

## Features

- Raycasting with separate horizontal and vertical grid intersection checks for accurate wall hits
- Textured walls, with a different texture for each direction (north, south, east, west)
- Doors and animated sprites placed on the map
- Minimap overlay
- Smooth movement with wall collision, keyboard and mouse look
- Map file parser with validation (closed walls, exactly one player start, required textures present)

## Build

Requires a Linux system with X11 and these development packages:

```bash
sudo apt install build-essential libx11-dev libxext-dev zlib1g-dev
```

Then:

```bash
git clone --recursive https://github.com/jeremie-lachon/cubefromzero.git
cd cubefromzero
make
```

The [MiniLibX](https://github.com/42Paris/minilibx-linux) graphics library is included as a git submodule; `make` fetches it automatically if it is missing.

## Usage

```bash
./cub3d maps/example.cub
```

| Key | Action |
|---|---|
| `W` `A` `S` `D` | Move |
| `←` `→` / mouse | Turn |
| `Esc` | Quit |

## Map format

A `.cub` file lists textures and colors, followed by the map grid:

```
NO ./texture/north.xpm
SO ./texture/south.xpm
WE ./texture/west.xpm
EA ./texture/east.xpm
DO ./texture/west.xpm
SP ./texture/west.xpm ./texture/east.xpm ./texture/south.xpm ./texture/north.xpm

F 1,2,1
C 150,5,0

111111111
100000001
10D000P01
1000N0001
111111111
```

| Key / symbol | Meaning |
|---|---|
| `NO` `SO` `WE` `EA` | Wall textures |
| `DO` | Door texture |
| `SP` | Sprite animation frames |
| `F` / `C` | Floor and ceiling colors (RGB) |
| `1` / `0` | Wall / empty floor |
| `N` `S` `E` `W` | Player start position and direction |
| `D` | Door |
| `P` | Sprite |
