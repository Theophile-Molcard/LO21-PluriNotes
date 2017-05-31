#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>

#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>


class NoteWindow : public QWidget{

    Q_OBJECT

public:
    NoteWindow(QWidget *parent = 0);

private:

    QVBoxLayout *fenetre_vbox;

    // ID
    QHBoxLayout *id_hbox;
    QLabel *id_label;
    QLineEdit *id;

    QHBoxLayout *title_hbox;
    QLabel *title_label;
    QLineEdit *title;

    QHBoxLayout *type_hbox;
    QLabel *type_label;
    QComboBox *type; // on voudrait plutot un edit


    QPushButton *create;

};

#endif // NOTEWINDOW_H
