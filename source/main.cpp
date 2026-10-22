#include <Game.h>

int main() {
    Game game;
    game.InitializeWindow();
    while (!game.ShouldExit()) {
        game.Process();
    }
    return 0;
}
