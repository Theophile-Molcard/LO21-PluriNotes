#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <typeinfo>

#include<QDebug>
#include<QAction>
#include<QUndoCommand>

#include "Notes.h"
#include "relations.h"
#include "notewindow.h"
#include "explorateurwindow.h"
#include "RelationWindow.h"
#include "arborescence.h"

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QSettings>



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

    void visualiser_rela_specifique(QString rela);

    bool bool_arbo() {return pref_arbo;}

    //Undo-Redo
    void deleteRelation(Relation* rel);
    void deleteCouple(QString rel, QString _x, QString _y, QString _label = "default");

private:
    Ui::MainWindow *ui;

    QUndoStack *undoStack;
    QAction *undoAction;
    QAction *redoAction;

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
    void closeEvent (QCloseEvent *event);


public slots:
    void elargir(){
        QSettings settings("config.ini",QSettings::IniFormat);
        settings.setValue("AffArbo",!pref_arbo);
        if(!pref_arbo){
            setFixedSize(800, 440);
            pref_arbo = true;
        }
        else{
            setFixedSize(600, 440);
            pref_arbo = false;
        }
    }

    void corbeilleAuto();

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

class DeleteRelationCommand : public QUndoCommand{
public:
    explicit DeleteRelationCommand(Relation *rel, QUndoCommand *parent = 0);
    void undo() override;
    void redo() override;
private:
    Relation* relation;
};

class DeleteCoupleCommand : public QUndoCommand{
public:
    explicit DeleteCoupleCommand(QString rel, QString _x, QString _y, QString _label = "default",  QUndoCommand *parent = 0);
    void undo() override;
    void redo() override;
private:
    QString relation;
    QString x;
    QString y;
    QString label;
};
#endif // MAINWINDOW_H
