#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <typeinfo>

#include<QDebug>
#include<QAction>

#include "Notes.h"
#include "relations.h"
#include "notewindow.h"
#include "explorateurwindow.h"
#include "RelationWindow.h"
#include "arborescence.h"

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

    bool bool_arbo() {return pref_arbo;}

private:
    Ui::MainWindow *ui;

    bool pref_arbo;
    bool pref_corbeille;

    NoteWindow * note_window;
    ArticleWindow * article_window;
    MultimediaWindow * multimedia_window;
    TacheWindow * tache_window;

    ExplorateurWindow *explo_window;

    CreationRelationWindow * crea_rela_window;
    ExplorateurRelationWindow * explo_rela_window;
    CoupleWindow * couple_window;
    RelationVizingWindow * rela_viz_window;

    Arborescence * arbo;


    void fermer_slot_1();
    void fermer_slot_2();
    void fermer_slot_3();


public slots:
    void elargir(){
        if(!pref_arbo){
            setFixedSize(800, 440);
            pref_arbo = true;
        }
        else{
            setFixedSize(600, 440);
            pref_arbo = false;
        }
    }

    void cree_note();
    void create();

    void ouvrir_explorateur();
    void ouvrir_agenda_taches();
    void ouvre_note();
    void ouvre_note_asc();
    void ouvre_note_desc();
    void ouvrir_archives();
    void ouvrir_corbeille();
    void restaure_corbeille();
    void ouvrir_memento();

    void ouvrir_crea_rela();
    void parcourir_rela();
    void ouvrir_rela();
    void ouvre_couplage();
    void visualiser_rela();

    void ouvrir_arbo();
    void fermer_arbo();

    void ouvrir_explorateur_memento();
};



#endif // MAINWINDOW_H
