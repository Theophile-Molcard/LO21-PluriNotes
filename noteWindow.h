#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


class NoteWindow : public QWidget{

    Q_OBJECT

public:
    NoteWindow();

private:

    QPushButton *bouton;

};

#endif // NOTEWINDOW_H
