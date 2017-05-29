#include "notewindow.h"

NoteWindow::NoteWindow() : QWidget()
{
    setFixedSize(300, 150);

    bouton = new QPushButton("Je m'entraine", this);

    bouton->setToolTip("Juste un test");
    bouton->setCursor(Qt::PointingHandCursor);
    bouton->move(60, 20);

}
