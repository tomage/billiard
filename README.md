# Billiard

Years ago (~2008), I made this little game for a course in computer graphics at University of Iceland.

The main reason I decided to pick up up again and modernize, is that I thought the way physics were handled was quite neat.

Also, I needed a non-trivial project to refresh my memory on C++, as well as learn better the modern tooling.


## How is it interesting?

Instead of the traditional approach of moving each object along it's velocity vector by it's speed over the frames-per-second, and resolving collisions in a crude way (risking clipping etc), this game calculates the first collision once the first ball (white) starts to move. It then simulates the situation right after the collision, and repeats the exercise. This way, it builds up a picture of all the collisions until the energy level in the system is below some threshold. It stores all those collision states, and then simulates them.

This allows the user to pause the game, change the time-step/speed of the game, and even go backwards/forwards over those states.


## Future of this repo

I might do some more work on it in the future if I have time, but this is really just a toy project.

I wrote this when starting out learning both how OpenGL worked, as well as getting familiar with C++. Also, it was written when C++03 was the latest and greatest. So no doubt there's a _ton_ of basic improvements that could be made.

I did take the original code (that I found on an old hard disk drive), and at least ported into CMake, and gave some structure. Then I did some rudimentary refactors.

For kicks, I tried to keep those refactors in a very clean git-history, both as an exercise in doing neat/atomic refactors, but also just for fun.


Copyright (C) 2021  Tómas Árni Jónasson (see [license (GPLv3.0)](LICENSE.txt)
