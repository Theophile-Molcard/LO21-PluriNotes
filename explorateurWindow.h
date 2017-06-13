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

/*!
* \file explorateurWindow.h
* \brief Définition des classes utiles à la fenetre d'exploration
* \author Théophile Maxime Théo
* \version 0.99
*/

/*! \class ExplorateurWindow
 * \brief Permet de gérer la fenetre d'exploration
 */
class ExplorateurWindow : public QWidget{

    Q_OBJECT

public:
    /*!
     * \brief Constructeur d'ExplorateurWindow
     * \param parent QWidget parent
     */
    ExplorateurWindow(QWidget *parent = 0);
    /*!
     * \brief Constructeur d'ExplorateurWindow pour l'agenda des taches
     * \param i permet de personnaliser
     * \param parent QWidget parent
     */
    ExplorateurWindow(int i, QWidget *parent = 0);
    /*!
     * \brief Constructeur ExplorateurWindow pour l'exploration d'une note
     * \param note note à explorer
     * \param parent QWidget parent
     */
    ExplorateurWindow(Note& note, QWidget *parent);
    /*!
     * \brief Getter du titre
     * \return le titre en QString
     */
    QString getTitre() {return titre->text(); }
    /*!
     * \brief Getter du titre
     * \return un pointeur sur un Qlabel
     */
    QLabel *getTitreWidget() {return titre; }
    /*!
     * \brief Getter de la liste des widget
     * \return un pointeur sur la liste
     */
    QListWidget* getListe() {return liste;}
    /*!
     * \brief Getter id correspondant à l'indice
     * \param indice indice
     * \return un id
     */
    QString getIdIndice(int indice) const {
        if(indice > tab_id.size())
            throw "erreur";
        else
            return tab_id[indice];
    }
    /*!
     * \brief Getter bouton d'ouverture
     * \return un pointeur sur le bouton d'ouverture
     */
    QPushButton* getButtonOpen() {return button_open;}

private:

    QList<QString> tab_id; /*!< tableau des id*/

    QVBoxLayout *fenetre_vbox;/*!< emplacement vertical pour la fenetre*/

    QLabel *titre;/*!< label pour le titre*/
    QListWidget *liste;/*!< Liste des widget*/
    QString NoteId;/*!< id de la note*/

    QHBoxLayout *button_layout;/*!< emplacement horizontal pour les boutons*/
    QPushButton *button_open;/*!< bouton d'ouverture*/
    QPushButton *button_close;/*!< bouton de fermeture*/

public slots:
    /*!
     * \brief slot pour la restauration de version
     */
    void restaurerVersion();


};

/*!
 * \brief Trie des taches par priorité
 * \param id liste des id
 * \param date liste des date
 * \param prio liste des priorité
 */
void sortByPrioDate(QList<QString>& id, QList<QDateTime> date, QList<int> prio);

#endif // EXPLORATEURWINDOW_H
