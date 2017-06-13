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
     * \brief lien avec la pile des undo pour la suppression d'une relation
     * \param rel un pointeur sur la relation à supprimer
     */
    void deleteRelation(Relation* rel);
    /*!
     * \brief lien avec la pile des undo pour la suppression d'un couple
     * \param rel relation où se situe le couple
     * \param _x parametre x du couple (x;y)
     * \param _y parametre y du couple (x;y)
     * \param _label label du couple
     */
    void deleteCouple(QString rel, QString _x, QString _y, QString _label = "default");

private:
    Ui::MainWindow *ui; /*!< fenetre principale */

    QUndoStack *undoStack;/*!< pile des undo */
    QAction *undoAction;/*!< action pour annuler*/
    QAction *redoAction;/*!< action pour rétablir*/

    bool pref_arbo;/*!< préférence pour l'affichage de l'arborescence*/
    bool pref_corbeille;/*!< préférence pour le vidage automatique de la corbeille*/

    NoteWindow * note_window;/*!< fenetre des notes*/
    ArticleWindow * article_window;/*!< fenetre des articles*/
    MultimediaWindow * multimedia_window;/*!< fenetre des multimedias*/
    TacheWindow * tache_window;/*!< fenetre des taches*/

    ExplorateurWindow *explo_window;/*!< fenetre d'exploration*/

    CreationRelationWindow * crea_rela_window;/*!< fenetre de création de relation*/
    ExplorateurRelationWindow * explo_rela_window;/*!< fenetre d'exploration des relations */
    CoupleWindow * couple_window;/*!< fenetre des couples*/
    RelationVizingWindow * rela_viz_window;/*!< fenetre de visualisation d'une relation*/

    Arborescence * arbo;/*!<  fenetre de l'arborescence*/

    /*!
     * \brief ferme le premier slot
     *
     * ferme fenetres correspondantes à l'éditions des notes
     *
     */
    void fermer_slot_1();
    /*!
     * \brief ferme le second slot
     *
     * ferme la fenetre d'exploration
     *
     */
    void fermer_slot_2();
    /*!
     * \brief ferme le troisieme slot
     *
     * ferme les fenetres liées aux relations
     *
     */
    void fermer_slot_3();
    /*!
     * \brief coupe un évenement
     *
     * sert à la sortie de l'application
     *
     * \param event évenement à couper
     */
    void closeEvent (QCloseEvent *event);


public slots:
    /*!
     * \brief slot pour elargir la fenetre et afficher l'arborescence
     */
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
    /*!
     * \brief slot pour la corbeille automatique
     */
    void corbeilleAuto();

    /*!
     * \brief slot pour la création de note
     */
    void cree_note();
    /*!
     * \brief slot pour la création d'un type précis de note
     */
    void create();

    /*!
     * \brief slot pour l'ouverture de l'explorateur
     */
    void ouvrir_explorateur();
    /*!
     * \brief slot pour l'ouverture de l'agenda des taches
     */
    void ouvrir_agenda_taches();
    /*!
     * \brief slot pour l'ouverture de note
     */
    void ouvre_note();
    /*!
     * \brief slot pour l'ouverture des notes ascendantes
     */
    void ouvre_note_asc();
    /*!
     * \brief slot pour l'ouverture des notes descendantes
     */
    void ouvre_note_desc();
    /*!
     * \brief slot pour l'ouverture des notes archivées
     */
    void ouvrir_archives();
    /*!
     * \brief slot pour l'ouverture de la corbeille
     */
    void ouvrir_corbeille();
    /*!
     * \brief slot pour la restauration de la corbeille
     */
    void restaure_corbeille();
    /*!
     * \brief slot pour l'ouverture du memento
     */
    void ouvrir_memento();

    /*!
     * \brief slot pour l'ouverture de la fenetre de création de relation
     */
    void ouvrir_crea_rela();
    /*!
     * \brief slot pour la fenetre de parcours des relations
     */
    void parcourir_rela();
    /*!
     * \brief slot pour l'ouverture des relations
     */
    void ouvrir_rela();
    /*!
     * \brief slot pour l'ouverture des couplages
     */
    void ouvre_couplage();
    /*!
     * \brief slot pour la visualisation des relations
     */
    void visualiser_rela();

    /*!
     * \brief slot pour l'ouverture de l'arborescence
     */
    void ouvrir_arbo();
    /*!
     * \brief slot pour la fermeture de l'arborescence
     */
    void fermer_arbo();

    /*!
     * \brief slot pour l'ouverture de l'explorateur de memento/versions
     */
    void ouvrir_explorateur_memento();
};

/*! \class The DeleteRelationCommand
 * \brief Classe pour la commande de suppression de relation
 *
 * Permet d'utiliser le undo/redo
 *
 */
class DeleteRelationCommand : public QUndoCommand{
public:
    /*!
     * \brief constructeur de DeleteRelationCommand
     * \param rel relation sur laquelle porte la commande
     * \param parent Commande parente
     */
    explicit DeleteRelationCommand(Relation *rel, QUndoCommand *parent = 0);
    /*!
     * \brief permet d'annuler la commande
     */
    void undo() override;
    /*!
     * \brief permet de rétablir la commande
     */
    void redo() override;
private:
    Relation* relation;/*!< relation sur laquelle s'applique la commande*/
};

/*! \class DeleteCoupleCommand
 * \brief Classe pour la commande de suppression des couples
 *
 * Permet d'utiliser le undo/redo
 *
 */
class DeleteCoupleCommand : public QUndoCommand{
public:
    /*!
     * \brief Constructeur de DeleteCoupleCommand
     * \param rel relation sur laquelle porte la commande
     * \param _x attribut x du couple (x;y)
     * \param _y attribut y du couple (x;y)
     * \param _label label du couple
     * \param parent commande parente
     */
    explicit DeleteCoupleCommand(QString rel, QString _x, QString _y, QString _label = "default",  QUndoCommand *parent = 0);
    /*!
     * \brief permet d'annuler la commande
     */
    void undo() override;
    /*!
     * \brief permet de rétablir la commande
     */
    void redo() override;
private:
    QString relation; /*!< relation sur laquelle s'applique la commande*/
    QString x;/*!< attribut x du couple (x;y)*/
    QString y;/*!< attribut y du couple (x;y)*/
    QString label;/*!< label du couple*/
};
#endif // MAINWINDOW_H
