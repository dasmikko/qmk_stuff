# rekna's Kyria rev2 Keymap

The keymap is a pretty basic, no crazy tap-dance mods or alike. It is very beginner friendly, and feel free to use it as a base.

It uses Danish layout, so it includes ÆØÅ.

I personally use it daily, and find it very intuitive.

## Installation
Clone the repo into `qmk_firmware/keyboards/splitkb/keymaps/` with the following command:

`git clone https://github.com/dasmikko/qmk_stuff.git rekna`

To compile and flash the keymap run the following command inside the qmk_firmware folder:

`./util/docker_build.sh splitkb/kyria/rev2:rekna:flash`

Tap the reset button once while plugged in.

Firmware should be flashed now.

If you just want to build the hex or uf2 file, run: 

`./util/docker_build.sh splitkb/kyria/rev2:rekna:uf2`

## Features
The keymap contains code for showing a funny little animated bongocat, that shows you your current WPM.
You can enable it in the `config.h` file.

## Layers
There is 6 layers in total: Main, Nav, Synbol, Function, Adjust and Gaming. I've placed the layer buttons in the thumb region for easy access.

### Main
This the default layer, where you have the QWERTY layout.

Space and backspace is placed at the thumbs, for quick typing. Ctrl, Shift is placed where you expect it.

### Nav
This layer is for most navigational keys, like the arrow/media keys.

### Symbols
Here you find all the synbols and special charactars you need. I've tried making as many symbols only require only 2 fingers. A few symbols still do require the alt gr key.

The brackets, parenthesis and square brackets are in a cluster for easy usage, as they are very commonly used in programming.

### Function
This layer is for the function keys F1-F12 and numpad. There is 2 keys to access the layer. One momentarely enables the layer, and the second toggles between it.

### Adjust
This is manly for adjusting RGB lights.

### Gaming
This one i use for gaming. It shifts the main layer one row down, so you are all the number keys, but lose the lowest row in the main one.

## Configuring 
You can edit the `config.h` and the `keymap.c`.

### Logo on the secondary side
Edit the `keymap.c`

### Layout
The repository contains the latest json file for the layout, and you can edit here: https://config.qmk.fm/
