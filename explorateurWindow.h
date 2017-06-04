#ifndef EXPLORATEURWINDOW_H
#define EXPLORATEURWINDOW_H

#include <QWidget>
#include <QAction>

#include <QListWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>

#include <QPushButton>


class ExplorateurWindow : public QWidget{

    Q_OBJECT

public:
    ExplorateurWindow(QWidget *parent = 0);
    QListView* getListe() {return liste;}
    QPushButton* getButtonOpen() {return button_open;}

private:

    QVBoxLayout *fenetre_vbox;

    QLabel *titre;
    QListWidget *liste;

    QHBoxLayout *button_layout;
    QPushButton *button_open;
    QPushButton *button_close;

};

#endif // EXPLORATEURWINDOW_H
