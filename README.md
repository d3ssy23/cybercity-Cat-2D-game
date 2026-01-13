<<<<<<< HEAD
# cybercity-Cat-2D-game
An easy 2D runner game in C with raylib framework

## Ready to use with Makefile
* /src
* $: make
* Go!
=======
# CyberCity Cat

A 2D endless runner game built with C and raylib. Control a cat character as you navigate through platforms, collect coins, and avoid zombies in a cyberpunk cityscape.

## Features

- **Smooth character movement** - Run, jump, and slide mechanics
- **Dynamic platform system** - Procedurally generated platforms
- **Enemy encounters** - Avoid zombies to maintain health
- **Coin collection** - Collect coins to increase your score
- **Health system** - Track your lives with a heart-based health bar
- **Parallax scrolling** - Multi-layer background for depth
- **Sound effects** - Immersive audio feedback

## Requirements

- C compiler (GCC/Clang)
- [raylib](https://www.raylib.com/) library
- `pkg-config` (for raylib configuration)

### Installing raylib

**macOS:**
```bash
brew install raylib
```

**Linux:**
```bash
# Ubuntu/Debian
sudo apt-get install libraylib-dev

# Or build from source
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP
sudo make install
```

## Building & Running

```bash
cd src
make
```

The game will automatically launch after compilation.

To clean build artifacts:
```bash
make clean
```

## Controls

- **RIGHT Arrow** - Move right / Run
- **SPACE** - Jump
- **DOWN Arrow** - Slide

## Credits

- Background art: Cyberpunk Street Environment by Luis Zuno (@ansimuz)

## License

This project is open source and available for educational purposes.
>>>>>>> 578a76b (readme)
