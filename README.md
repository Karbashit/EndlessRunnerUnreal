# EndlessRunnerUnreal

My game consists of 3 major components.
1. The primary base object. This is the player. All initialization and ticking of player-related things are handled here such as Movement, Input, Player related UI and more.
2. The PlatformFactory actor. This is where the scrolling platforms are spawned and handled.
3. The EnemyFactory. This is where enemies are spawned and difficulty is handled. (The more enemies, the more difficult the game gets).

Examples of effective C++ use in my code:
* The PlatformFactory never spawns or destroys any platforms after the initial platforms are spawned. They instead switch places after scrolling outside of camera view. For next turn-in i aim to turn this idea into a proper pooling system using a middle-hand class that handles the pool separately from the PlatformFactory class.
* Separating different areas of player behaviour into different classes, then having the player class make use of those classes when necessary.
