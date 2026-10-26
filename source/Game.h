#ifndef SOURCE_GAME_H_
#define SOURCE_GAME_H_

#include <base/GeneralParser.h>
#include <base/GameObjectManager.h>

#include <factories/buildings/CastleFactory.h>
#include <factories/units/VillagerFactory.h>

#include <raylib.h>
#include <memory>

// Holds the whole game loop.
// Eventually a main menu should loop this class
// that will be the client of the application.
class Game {
 private:
    // Parser for the settings used to initialize the window.
    GeneralParser m_generalParser;

    // Holds all the game objects that the player controls.
    // Its position in the hierarchy could change during development.
    std::shared_ptr<GameObjectManager> m_gameObjectManager;

    // The rect that mouse dragging creates.
    Rectangle m_mouseRect;

    // Draws the mouse rect that is used for selection.
    void DrawMouseRectangle();

 public:
    Game();
    ~Game();

    // Initializes and starts the window if the parser parsed correct settings.
    void InitializeWindow();

    // Returns true if the game should end and the main should exit.
    bool ShouldExit() const;

    // Processes the game.
    // Essentually the whole game loop is supposed to come here.
    void Process();
};

#endif  // SOURCE_GAME_H_
