#include <gtkmm/main.h>
#include <iostream>
#include "Game.h"
#include "Controller.h"
#include <string>
#include "View.h"

int main(int argc, char** argv)
{
    Gtk::Main kit(argc, argv);
    // start the game by creating a game object.
    Game game;
    Controller controller(&game);
    View view(&controller, &game);
    Gtk::Main::run(view);
    return 0;
}
