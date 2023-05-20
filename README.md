# Final Hand In Notes

It has been a really tough assignment for me as im pretty much new to unreal and also C++ and only implementing small features has taken a lot of time.

The new features that were missing/or added between part1 and part2 are: 
1. The addition of a startmenu/scoreboard 
2. score,
3. more balanced difficulty, 
4. multiplayer 
5. the 25% random removal of projectiles after dodging
6. Major graphics overhaul
7. A game over screen

I've moved around some code to be in more appropiate places or even made new classes entirely for some features.
For an example the maingame UI in part1 was created inside of the playerobject, but it is now moved to an entirely different class called "SharedUI" to be able to support
two players and for it to be easier to access depending on which player take damage and so on.
