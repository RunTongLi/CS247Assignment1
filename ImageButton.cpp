#include "ImageButton.h"


ImageButton::ImageButton()
{
    button.set_image(image);
    button.signal_clicked().connect(sigc::mem_fun(*this, &ImageButton::onClicked));
}

void ImageButton::disable()
{
    button.set_sensitive(false);
}

void ImageButton::enable()
{
    button.set_sensitive(true);
}

void ImageButton::onClicked()
{
    controller_->cardClicked(index);
}
