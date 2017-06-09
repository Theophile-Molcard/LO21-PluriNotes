#ifndef EXPLORATEURWINDOW_H
#define EXPLORATEURWINDOW_H

#include "Notes.h"

#include <QWidget>
#include <QList>

#include <QListWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>

#include <QPushButton>


class ExplorateurWindow : public QWidget{

    Q_OBJECT

public:
    ExplorateurWindow(QWidget *parent = 0);
    ExplorateurWindow(int i, QWidget *parent = 0);
    ExplorateurWindow(Note& note, QWidget *parent);
    QString getTitre() {return titre->text(); }
    QLabel *getTitreWidget() {return titre; }
    QListWidget* getListe() {return liste;}
    QString getIdIndice(int indice) const {
        if(indice > tab_id.size())
            throw "erreur";
        else
            return tab_id[indice];
    }
    QPushButton* getButtonOpen() {return button_open;}

private:

    QList<QString> tab_id;

    QVBoxLayout *fenetre_vbox;

    QLabel *titre;
    QListWidget *liste;
    QString NoteId;

    QHBoxLayout *button_layout;
    QPushButton *button_open;
    QPushButton *button_close;

public slots:
    void restaurerVersion();


};

void sortByPrioDate(QList<QString>& id, QList<QDateTime> date, QList<int> prio);

#endif // EXPLORATEURWINDOW_H
