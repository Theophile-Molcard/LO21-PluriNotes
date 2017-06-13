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

/*!
* \file mainwindow.h
* \brief Définition des classes utiles à la fenetre principale
* \author Théophile Maxime Théo
* \version 0.99
*/

/*! \namespace Ui
 * \brief contient la class MainWindow
 */
namespace Ui {
class MainWindow;
}

/*! \class MainWindow
 * \brief Classe fille de QMainWindow, permet de gérer la fenetre principale
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    /*!
     * \brief Constructeur de MainWindow
     * \param parent QWidget parent
     */
    explicit MainWindow(QWidget *parent = 0);
    /*!
     * \brief destructeur de MainWindow
     */
    ~MainWindow();

    // Create()
    /*!
     * \brief Créer une fenetre pour éditer un article
     */
    void editeur_article();
    /*!
     * \brief Créer une fenetre pour éditer un multimedia
     */
    void editeur_multimedia();
    /*!
     * \brief Créer une fenetre pour éditer une tache
     */
    void editeur_tache();

    // Ouvrir()
    /*!
     * \brief ouvre l'éditeur de tache à partir des données d'une note
     * \param note référence sur la note qui contient les information de la tache
     */
    void ouvre_tache(Note& note);
    /*!
     * \brief ouvre l'éditeur de multimedia à partir des données d'une note
     * \param note référence sur la note qui contient les information du multimedia
     */
    void ouvre_multi(Note& note);
    /*!
     * \brief ouvre l'éditeur d'article à partir des données d'une note
     * \param note référence sur la note qui contient les information de l'article
     */
    void ouvre_article(Note& note);

    /*!
     * \brief ouvre l'aperçu d'une relation
     * \param rela relation à ouvrir
     */
    void visualiser_rela_specifique(QString rela);

    /*!
     * \brief booléen pour afficher l'arborescence des relations
     * \return true si on affiche, false sinon
     */
    bool bool_arbo() {return pref_arbo;}

    //Undo-Redo
    /*!
     * \brief deleteRelation
     * \param rel
     */
    void deleteRelation(Relation* rel);
    /*!
     * \brief deleteCouple
     * \param rel
     * \param _x
     * \param _y
     * \param _label
     */
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
