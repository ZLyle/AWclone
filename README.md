## Advance Wars Clone
######(change name later to not get sued)

#### Compiling/Making

Commands to build (invoke within build directory), prefer Debug and Release:
```
> cmake -G <generator> -DCMAKE_BUILD_TYPE=<type> <path up (to project root)>
```
Example:
```
> cmake -G "Unix Makefiles" ..
> cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
> cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
```
This will generate a Makefile for the generator you passed `cmake`. Use `make` to with that Makefile to compile the program into its folder. You should be able to use make to recompile specific parts, but you'll mostly just `make all` and run it as needed.

Running `cmake` generates a ton of shit, keep those out of the git. Keep anything from VS out too if it's not project essential (most if not all of it).
