#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <gtkmm.h>
#include "Controller.h"

// Ties a button to an image, useful for displaying the player's hand
struct ImageButton {
    Gtk::Button button;
    Gtk::Image image;

    // The index of the button in the horizontal layour, aka, the index corresponding to the Model's hand
    int index;

    // has accesss tp the View controller to directly emit events to the Model.
    Controller* controller_;

    // Constructor, sets the image of the button to be image
    ImageButton();

    // Click event handler for the button
    void onClicked();

    // enable/disable the button
    void disable();
    void enable();
};

#endif // IMAGEBUTTON_H
