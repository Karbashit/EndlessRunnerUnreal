# Final Hand In Notes

It has been a really tough assignment for me as im pretty much new to unreal and also C++ and only implementing small features has taken a lot of time.

First of as you might see, the second version of the game doesn't have a working build. For some reason when building the project, UI is unreachable by any means. I've spent almost the entire night trying to debug this but neither google, chatgpt or classmates has been able
to get to the bottom of the problem and tried every single possible solution and debugging method i could think of. Very sorry about this. It works perfectly in engine though as intended.

I have full understanding if this fails me as its very clearly stated in the instructions to have a working build for both hand ins which i have respect for. However time is up and nobody has time to help me this late.
Next time ill make sure to try building my project more often.


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
