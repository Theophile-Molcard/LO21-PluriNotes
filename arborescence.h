#ifndef ARBORESCENCE_H
#define ARBORESCENCE_H

#include"Notes.h"

#include<QWidget>
#include<QTreeWidget>
#include<QTreeView>
#include<QLabel>
#include<QLayout>
#include<QList>
#include<QPushButton>

/*!
* \file arborescence.h
* \brief Définition des classes utiles à la fenetre d'arborescence
* \author Théophile Maxime Théo
* \version 0.99
*/

/*! \class Arborescence
 * \brief Permet de gérer la fenetre de l'arborescence
 */
class Arborescence : public QWidget{

    Q_OBJECT

public:
    /*!
     * \brief Constructeur de Arborescence
     * \param note sur laquelle porte l'arborescence
     * \param parent QWidget parent
     */
    Arborescence(Note& note, QWidget *parent = 0);

    /*!
     * \brief Getter des descendants
     * \return l'arbre des descendants
     */
    QTreeWidget* getDescendants() {return descendants; }
    /*!
     * \brief Getter des Ascendants
     * \return l'arbre des ascendants
     */
    QTreeWidget* getAscendants() {return ascendants; }

    /*!
     * \brief Getter bouton des ascendants
     * \return un pointeur sur le bouton des ascendants
     */
    QPushButton* getButtonAsc() {return button_asc; }
    /*!
     * \brief Getter bouton des descendants
     * \return un pointeur sur le bouton des descendants
     */
    QPushButton* getButtonDesc() {return button_desc; }

private:

    QVBoxLayout *fenetre_vbox;/*!<  emplacement vertical pour la fenetre */

    QHBoxLayout *label_hbox;/*!< emplacement horizontal pour le label*/
    QLabel *id_label;/*!< label pour l'id*/
    QLabel *titre_label;/*!< label pour le titre*/

    QHBoxLayout *button_layout;/*!< emplacement horizontal pour les boutons*/
    QPushButton *button_asc;/*!< bouton pour les ascendants*/
    QPushButton *button_desc;/*!< boutons pour les descendants*/

    QTreeWidget *descendants;/*!< arbre des descendants*/
    QTreeWidget *ascendants;/*!< arbre des ascendants*/

    QList<QString> id_asc;/*!< liste des id des ascendants*/
    QList<QString> id_dsc;/*!< liste des id des descendants*/

    QList<QString> id_asc_root;/*!< liste des id pour la racine des ascendants*/
    QList<QString> id_dsc_root;/*!< liste des id pour la racine des descendants*/

    /*!
     * \brief setter pour la racine des Ascendants à partir d'une note
     * \param note note
     */
    void setAscendantsRacine(Note& note);
    /*!
     * \brief setter pour les Ascendants d'un id à partir d'un arbre
     * \param id id
     * \param tree arbre
     */
    void setAscendants(QString id, QTreeWidgetItem* tree);
    /*!
     * \brief setter pour la racine des Descendants à partir d'une note
     * \param note note
     */
    void setDescendantsRacine(Note& note);
    /*!
     * \brief setter pour les Descendants d'un id à partir d'un arbre
     * \param id id
     * \param tree arbre
     */
    void setDescendants(QString id, QTreeWidgetItem* tree);

    /*!
     * \brief ajoute une racine à un arbre
     * \param parent arbre parent
     * \param nom nom de la racine
     * \return
     */
    QTreeWidgetItem* addRoot(QTreeWidget * parent, QString nom);
    /*!
     * \brief ajout d'un enfant à l'arbre
     * \param parent arbre parent
     * \param nom de l'enfant
     * \return un pointeur sur un arbre
     */
    QTreeWidgetItem* addChild(QTreeWidgetItem * parent, QString nom);


public slots:

};



#endif // ARBORESCENCE_H
