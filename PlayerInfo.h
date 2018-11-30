#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <gtkmm.h>
#include "Controller.h"


// Struct that encapsulates a portion of the view model
struct PlayerInfo {
    Gtk::Frame frame;
    Gtk::VBox container;
    Gtk::Frame labelFrame;
    Gtk::Button button;
    Gtk::Label pointsLabel;
    Gtk::Label discardsLabel;

    // keep track of points, discards. etc to determine whether or not to update text in labels
    int points;
    int discards;
    bool isHuman;
    bool isStarted;

    // Has access to the View controller to delegate UI events to the Model
    Controller* controller_;

    // Bunch of setters to set specific values, see implementation for more details
    void setStarted();
    void setNotStarted();
    void disable();
    void enable();
    void toggleButtonLabel(bool nowIsHuman);
    void setNotStartedButtonLabels();
    void setId(int id);
    void setPoints(int newPoints);
    void setDiscards(int newDiscards);
    PlayerInfo();

    // event signal handler for the button's click event
    void onButtonClicked();
};

#endif // PLAYERINFO_H
