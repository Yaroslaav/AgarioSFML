# Agario SFML

Small Agar.io-style game built on a local engine layer and SFML.

## Setup

```powershell
git clone --recurse-submodules <repo>
cd AgarioSFML
cmake -S . -B build
cmake --build build --config Release
```

If the repository was cloned without submodules:

```powershell
git submodule update --init --recursive
```

## Dependencies

- `external/SFML`: the only third-party dependency used by CMake.
- SFML pulls its own transitive dependencies during configure/build.

## Structure

- `Engine`: reusable application, world, actor, component, input, rendering, and math code.
- `Agario/Actors`: gameplay entities such as cells and food.
- `Agario/Controllers`: player and bot control logic.
- `Agario/Components`: game-specific actor components.
- `Agario/Gameplay`: game rules and systems that coordinate actors.
- `Agario/World`: world state and spatial chunk grid.
- `assets`: runtime assets copied next to the executable after build.
