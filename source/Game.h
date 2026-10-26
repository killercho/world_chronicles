#ifndef SOURCE_GAME_H_
#define SOURCE_GAME_H_

#include <base/GeneralParser.h>
#include <base/ResourceManager.h>
#include <units/Villager.h>
#include <buildings/Castle.h>
#include <factories/buildings/CastleFactory.h>
#include <raylib.h>
#include <memory>

// Holds the whole game loop.
// Eventually a main menu should loop this class
// that will be the client of the application.
class Game {
 private:
    // Parser for the settings used to initialize the window.
    GeneralParser m_generalParser;

    // Resource manager holding all the textures of the game.
    std::shared_ptr<ResourceManager> m_resourceManager;

    // Test subjects that are used only as harcoded values to test interactions:
    std::vector<std::shared_ptr<Villager>> m_villagers;
    CastleFactory m_castleFactory;

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
