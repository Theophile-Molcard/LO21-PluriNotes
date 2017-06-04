#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <typeinfo>

#include<QDebug>

#include "Notes.h"
#include "notewindow.h"
#include "explorateurwindow.h"

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Create()
    void editeur_article();
    void editeur_multimedia();
    void editeur_tache();

    // Ouvrir()
    void ouvre_tache(Note& note);
    void ouvre_multi(Note& note);
    void ouvre_article(Note& note);


private:
    Ui::MainWindow *ui;

    NoteWindow * note_window;
    ArticleWindow * article_window;
    MultimediaWindow * multimedia_window;
    TacheWindow * tache_window;

    ExplorateurWindow *explo_window;


public slots:
    void cree_note();
    void create();

    void ouvrir_explorateur();
    void ouvre_note();
};



#endif // MAINWINDOW_H
