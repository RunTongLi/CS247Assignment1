#include "PlayerInfo.h"

PlayerInfo::PlayerInfo()
    :
    points(0),
    discards(9),
    isHuman(true),
    isStarted(false)
{
    frame.add(container);
    container.add(labelFrame);
    container.add(button);
    container.add(pointsLabel);
    container.add(discardsLabel);

    setNotStartedButtonLabels();

    button.signal_clicked().connect(sigc::mem_fun(*this, &PlayerInfo::onButtonClicked));
}

// Change the function of the button to be "Ragequit" after the game has started
void PlayerInfo::setStarted()
{
    isStarted = true;
    button.set_label("Rage!");
}

// And change it back after the game ends back to selecting Human/Computer
void PlayerInfo::setNotStarted()
{
    isStarted = false;
    enable();
    setNotStartedButtonLabels();
}

// "set_sensitive" to false makes the button greyed out and unclickable
void PlayerInfo::disable()
{
    button.set_sensitive(false);
}

// "set_sensitive" to true sets it back to clickable
void PlayerInfo::enable()
{
    button.set_sensitive(true);
}

void PlayerInfo::toggleButtonLabel(bool nowIsHuman)
{
    if (nowIsHuman ^ isHuman) { // XOR tells us if the values are different
        isHuman = nowIsHuman;
        setNotStartedButtonLabels();
    }
}

void PlayerInfo::setNotStartedButtonLabels()
{
    button.set_label(isHuman ? "Human" : "Computer");
}

void PlayerInfo::setId(int id)
{
    labelFrame.set_label("Player " + std::to_string(id));
}


void PlayerInfo::setPoints(int newPoints)
{
    pointsLabel.set_text("Points: " + std::to_string(newPoints));
}

void PlayerInfo::setDiscards(int newDiscards)
{
    discardsLabel.set_text("Discards: " + std::to_string(newDiscards));
}

// handler for button click events
void PlayerInfo::onButtonClicked()
{
    if (isStarted) {
        controller_->rageQuitButtonClicked();
    } else {
        toggleButtonLabel(!isHuman);
    }
}
