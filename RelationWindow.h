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
#include <QComboBox>

/*!
* \file RelationWindow.h
* \brief Définition des classes utiles aux fenetres liés aux relations
* \author Théophile Maxime Théo
* \version 0.99
*/

/*! \class CreationRelationWindow
 * \brief class fille de Qwidget, permet de gérer la fenetre de création de relation
 */
class CreationRelationWindow : public QWidget{

    Q_OBJECT /*!< Macro Qt*/

public:
    /*!
     * \brief Constructeur de CreationRelationWindow à partir d'un QWidget parent
     * \param parent Qwidget parent
     */
    CreationRelationWindow(QWidget *parent = 0);
    /*!
     * \brief Constructeur de CreationRelationWindow à partir d'un QWidget parent et d'une relation
     * \param rela relation
     * \param parent Qwidget parent
     */
    CreationRelationWindow(Relation* rela, QWidget *parent = 0);

    /*!
     * \brief Getter bouton de création
     * \return un pointeur sur le bouton de création
     */
    QPushButton* getButtonCreate() {return button_create;}
    /*!
     * \brief Getter bouton de fermeture
     * \return un pointeur sur le bouton de fermeture
     */
    QPushButton* getButtonClose() {return button_close;}
    /*!
     * \brief Getter bouton de suppression
     * \return un pointeur sur le bouton de suppression
     */
    QPushButton* getButtonDelete() {return button_delete;}
    /*!
     * \brief Getter pour le champ du titre de la relation
     * \return le titre écrit à la création
     */
    QLineEdit* getTitre() {return titre; }

private:

    QList<QString> tab_id_x; /*!< liste des id x des relations (x;y) */
    QList<QString> tab_id_y;  /*!< liste des id y des relations (x;y) */

    QVBoxLayout *fenetre_vbox; /*!< Emplacement vertical pour la fenetre */

    QHBoxLayout *titre_hbox; /*!< Emplacement horizontal pour le titre*/
    QLabel *titre_label; /*!< label pour le champ du titre*/
    QLineEdit *titre; /*!< champ du titre */
    QString titre_ancien; /*!< sauvegarde de l'ancien titre */

    QHBoxLayout * description_hbox; /*!< Emplacement horizontal pour la description */
    QLabel *description_label; /*!< label pour le champ de la description */
    QTextEdit *description; /*!< champ de la description */

    QCheckBox *non_oriente; /*!< Case à cocher pour le statut de l'orientation de la relation */

    QHBoxLayout *button_layout; /*!< emplacement horizontal pour les boutons*/
    QHBoxLayout *button_layout_1; /*!< emplacement horizontal pour les boutons */
    QHBoxLayout *button_layout_2; /*!< emplacement horizontal pour les boutons */
    QPushButton *button_create; /*!< bouton de création de relation*/
    QPushButton *button_close; /*!< bouton de fermeture */
    QPushButton *button_save; /*!< bouton de sauvegarde*/
    QPushButton *button_delete; /*!< bouton de suppression */

public slots:
    /*!
     * \brief Slot lançant la création
     */
    void create();
    /*!
     * \brief Slot lançant la sauvegarde
     */
    void save();
    /*!
     * \brief Slot lançant la suppression
     */
    void delete_rela();


};

/*! \class ExplorateurRelationWindow
 * \brief classe fille de QWidget, permet de gérer la fenetre d'exploration des relations
 */
class ExplorateurRelationWindow : public QWidget{

    Q_OBJECT

public:
    /*!
     * \brief Constructeur de ExplorateurRelationWindow
     * \param parent Qwidget parent de la fenetre
     */
    ExplorateurRelationWindow(QWidget *parent = 0);

    /*!
     * \brief Getter bouton suppression
     * \return un pointeur sur le bouton
     */
    QPushButton* getButtonSuprime() {return button_supprimer;}
    /*!
     * \brief Getter champ selection des relations à partir d'une liste
     * \return un pointeur sur une QListWidget
     */
    QListWidget* getListe() {return liste; }

private:

    QVBoxLayout *fenetre_vbox;/*!< emplacement vertical pour la fenetre */

    QLabel *titre;/*!< label pour le titre */

    QListWidget *liste;/*!< champ de selection des relations à partir d'une liste*/

    QHBoxLayout *button_layout;/*!< emplacement horizontal pour les boutons*/
    QPushButton *button_supprimer;/*!< bouton de suppression*/
    QPushButton *button_close;/*!< bouton de fermeture*/

};


/*! \class CoupleWindow
 * \brief Classe fille de QWidget, permet de gérer la fenetre liée aux couples
 */
class CoupleWindow : public QWidget{

    Q_OBJECT

public:
    /*!
     * \brief Constructeur de CoupleWindow
     * \param rela relation à laquelle les couples appartiennent
     * \param parent parent de la fenetre
     */
    CoupleWindow(Relation* rela, QWidget *parent = 0);

    /*!
     * \brief Getter du bouton de création
     * \return pointeur sur le buton de création
     */
    QPushButton* getButtonCreate() {return button_create;}

private:

    QList<QString> tab_id_x;/*!< liste des notes pour la partie x du couple (x;y)*/
    QList<QString> tab_id_y;/*!< liste des notes pour la partie y du couple (x;y)*/

    QVBoxLayout *fenetre_vbox;/*!< emplacement vertical de la fenetre */

    QLabel *titre_rela;/*!< label pour le titre de la relation */

    QHBoxLayout * couple_hbox;/*!< emplacement horizontal pour les couples */
    QLabel *couple_label;/*!< label pour le champ texte du couple*/
    QLineEdit *couple;/*!< Champ texte pour le couple*/

    QListWidget *liste_x;/*!< selection à partir d'une liste de note (de leurs ids)*/
    QListWidget *liste_y;/*!< selection à partir d'une liste de note (de leurs ids)*/

    QHBoxLayout *button_layout;/*!< emplacement horizontal pour les boutons*/
    QPushButton *button_create;/*!< bouton de création */
    QPushButton *button_close;/*!< bouton de fermeture */

public slots:
    /*!
     * \brief Slot lançant la sauvegarde
     */
    void save();

};


/*! \class RelationVizingWindow
 * \brief Classe fille de QWidget, permet de visualiser des relations
 */
class RelationVizingWindow : public QWidget{

    Q_OBJECT

public:
    /*!
     * \brief Constructeur de RelationVizingWindow
     * \param parent QWidget parent de la fenetre
     */
    RelationVizingWindow(QWidget *parent = 0);

    /*!
     * \brief Getter bouton suppression
     * \return un pointeur sur le bouton de suppression
     */
    QPushButton* getButtonSuprime() {return button_supprimer;}
    /*!
     * \brief Getter de la liste de couple de la relation
     * \return un poineur sur la liste de couple
     */
    QListWidget* getListeCouple() {return liste_couples; }

    /*!
     * \brief AfficherCouplesRelation
     * \param rel
     */
    void afficherCouplesRelation(QString rel);

private:

    QVBoxLayout *fenetre_vbox;/*!< Emplacement vertical pour la fenetre */

    QComboBox *relation;/*!< ComboBox (bouton + popup) */

    QListWidget *liste_couples;/*!< liste de couples */

    QHBoxLayout *button_layout;/*!< emplacement horizontal pour les boutons*/
    QPushButton *button_supprimer;/*!< bouton supprimer*/
    QPushButton *button_close;/*!< bouton femeture*/

    QHBoxLayout *label_hbox;/*!< emplacement horizontal pour les labels*/
    QLabel *label_label;/*!< label pour le champ label */
    QLineEdit *label;/*!< champ texte pour le label*/
    QPushButton * label_save;/*!< bouton de sauvegarde */

public slots:
    /*!
     * \brief Slot pour afficher les Couples
     */
    void afficherCouples();
    /*!
     * \brief Slot pour editer un couple
     */
    void editer_couple();
    /*!
     * \brief Slot pour sauvegarder un label
     */
    void saveLabel();
    /*!
     * \brief Slot pour la suppression d'un couple
     */
    void deleteCouple();
    /*!
     * \brief slot pour l'activation de la suppression
     */
    void activer_suppr(){
        if(relation->currentText() == "Reference")
            button_supprimer->setEnabled(false);
        else
            button_supprimer->setEnabled(true);
    }

};


#endif // CREARELAWINDOW_H
