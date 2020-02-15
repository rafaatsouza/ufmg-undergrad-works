# AEDS (Algorithms and data structure) I

Practical assignment which simulates the "Bomberman" game with C program language and Allegro library.

#### Build
Generates executable file using *Makefile*.

#### Instructions
The goal is to kill enemies (in red) using bombs, dropped while controlling bomberman (in blue). At the game start, bomberman position and the three enemies position are randomly defined following some criteries:
* Bomberman and enemies cannot share same exact location 
* Bomberman and enemies cannot be within less then 100px from each other.

When all enemies are dead, all are recriated at new positions following the same criteria, and all gets a speed boost; at all phases start bomberman gets invecibility in 2 first seconds.

Case bomberman get hit by some enemy or by a bomb, he dies and the screen show player's score.

#### Game commands:
* W, S, A, D: Moves bomberman across the map.
* Espace: Drops a bomb. The bombs explode 1 second after being dropped, and has explosion range equals 64x64.

#### Score Criteria:
* Kill enemy: 10 points + variable value (increases through game phases).
* Gets killed by bomb: -[10 points + variable value (increases through game phases)].
* Time: 1 point by seconds * variable value (increases through game phases). Obs: only count after 2nd phase.
