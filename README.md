#CPPiano
Qt4 interfaced keyboard

---

###Requirements
Needs g++, make, qt4-dev, qt4-phonon

###Build
Clone repository with 
> $ git clone http://github.com/drjest/CPPiano.git

Move to CPPiano directory and rebuild project
> $ mv CPPiano

> $ qmake -project

> $ qmake

You'll need to edit CPPiano.pro and substitute 
> $(GCC) = g++ 

with

> g++ -std=c++11

Then you can build with make
> $ make

###Use
####CLI Arguments
If you call CPPiano with following flags:

Flag | Parameters | Description 
---- | ---------- | -----------
h    | -none-     | Prints help usage
v    | -none-     | Prints version informations
k    | String     | Loads a layout file for keyboard
l    | int        | Lower Octave [1-7]
u    | int        | Upper Octave [1-7]

####GUI
Most of keys [1-9][a-z] are reserved for keyboard mapping.
`+` and `-` change octave for key mapping

#####Key Mapping
2 key maps are included:
- Default: maps in piano-position central line of the keyboard, from a(a of the previous octave) to p (c of the following one), With positioned sharp keys
- Complete: maps 3 complete octaves from 1 (c of prev. octave) to m (c of the very following one)
If you want to create a custom keymap you have to create a blank file, then map each key in a line in this format
> key note

where note is in the format

[a-g][($p)($c)($n)]#?

in which $p,$c,$n are macros for previous, current and following octave. 

####Credits
dc.jest [at] gmail [dot] com