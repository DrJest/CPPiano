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

---
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

---
####Credits
dc.jest [at] gmail [dot] com