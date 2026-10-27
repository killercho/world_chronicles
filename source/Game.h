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

    // The position that mouse dragging starts at.
    Vector2 m_mouseStartPos;
    // The rect that is resulting of the mouse dragging.
    // Saved here for optimization and passing to the units.
    Rectangle m_mouseDraggingRect;

    // Draws the mouse rect that is used for selection.
    void DrawMouseRectangle();

    // Creates text that shows what buttons are used for spawning units and buildings.
    // Used only for debug and will be deleted later.
    void CreateButtonMappingText();

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
