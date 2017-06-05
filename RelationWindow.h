#ifndef CREARELAWINDOW_H
#define CREARELAWINDOW_H


#include <QWidget>
#include <QList>

#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>

#include <QPushButton>
#include <QCheckBox>


class CreationRelationWindow : public QWidget{

    Q_OBJECT

public:
    CreationRelationWindow(QWidget *parent = 0);

    QPushButton* getButtonCreate() {return button_create;}

private:

    QList<QString> tab_id_x;
    QList<QString> tab_id_y;

    QVBoxLayout *fenetre_vbox;

    QHBoxLayout *titre_hbox;
    QLabel *titre_label;
    QLineEdit *titre;

    QHBoxLayout * description_hbox;
    QLabel *description_label;
    QTextEdit *description;

    QCheckBox *non_oriente;

    QListWidget *liste_x;
    QListWidget *liste_y;

    QHBoxLayout *button_layout;
    QPushButton *button_create;
    QPushButton *button_close;

};


#endif // CREARELAWINDOW_H
