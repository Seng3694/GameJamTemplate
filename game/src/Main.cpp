#include "Game.hpp"
#include "TestState.hpp"

int main()
{
    gjt::Game game("Template", 800, 600);
    game.run<TestState>();
    return 0;
}
