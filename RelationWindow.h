#ifndef CREARELAWINDOW_H
#define CREARELAWINDOW_H

#include"relations.h"

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
    CreationRelationWindow(Relation* rela, QWidget *parent = 0);

    QPushButton* getButtonCreate() {return button_create;}
    QPushButton* getButtonClose() {return button_close;}
    QLineEdit* getTitre() {return titre; }

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

    QHBoxLayout *button_layout;
    QPushButton *button_create;
    QPushButton *button_close;

};


class ExplorateurRelationWindow : public QWidget{

    Q_OBJECT

public:
    ExplorateurRelationWindow(QWidget *parent = 0);

    QPushButton* getButtonSuprime() {return button_supprimer;}
    QListWidget* getListe() {return liste; }

private:

    QVBoxLayout *fenetre_vbox;

    QLabel *titre;

    QListWidget *liste;

    QHBoxLayout *button_layout;
    QPushButton *button_supprimer;
    QPushButton *button_close;

};


class CoupleWindow : public QWidget{

    Q_OBJECT

public:
    CoupleWindow(Relation* rela, QWidget *parent = 0);

    QPushButton* getButtonCreate() {return button_create;}

private:

    QList<QString> tab_id_x;
    QList<QString> tab_id_y;

    QVBoxLayout *fenetre_vbox;

    QLabel *titre_rela;

    QHBoxLayout * couple_hbox;
    QLabel *couple_label;
    QLineEdit *couple;

    QListWidget *liste_x;
    QListWidget *liste_y;

    QHBoxLayout *button_layout;
    QPushButton *button_create;
    QPushButton *button_close;

};


#endif // CREARELAWINDOW_H
