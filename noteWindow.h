#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QWidget>
#include "Notes.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QFileDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDateTimeEdit>

/*!
* \file noteWindow.h
* \brief Définition des classes utiles aux fenetres liées aux notes
* \author Théophile Maxime Théo
* \version 0.99
*/

/*! \class NoteWindow
 * \brief classe fille de QWidget, permet de gérer la fenetre de Note
 */
class NoteWindow : public QWidget{

    Q_OBJECT

public:
    /*!
     * \brief Constructeur de NoteWindow
     * \param parent Widget parent de la fenetre
     */
    NoteWindow(QWidget *parent = 0);
    /*!
     * \brief Getter bouton de création
     * \return un pointeur sur le bouton de création
     */
    QPushButton* getPushButton(){ return create_button; }
    /*!
     * \brief getter id de la note à créer
     * \return l'id de la note
     */
    QString getId() const { return id->text(); }
    /*!
     * \brief Getter du titre de la note à créer
     * \return le titre de la note
     */
    QString getTitle() const { return title->text(); }
    /*!
     * \brief Getter type de la note à créer
     * \return le type de la note sous forme de QString
     */
    QString getType() const { return type->currentText(); }

private:

    QVBoxLayout *fenetre_vbox; /*!< Emplacemet vertical de la fenetre*/

    // ID
    QHBoxLayout *id_hbox; /*!< emplacement horizontal de l'id*/
    QLabel *id_label; /*!< label pour le champ id*/
    QLineEdit *id; /*!< champ id */

    QHBoxLayout *title_hbox; /*!< emplacement horizontal du titre */
    QLabel *title_label; /*!< label pour le champ du titre */
    QLineEdit *title; /*!< champ titre*/

    QHBoxLayout *type_hbox;/*!< emplacement horizontal du type*/
    QLabel *type_label; /*!< Label pour le champ type*/
    QComboBox *type; /*!< combo box pour le type*/

    QHBoxLayout *button_hbox; /*!< emplacement horizontal pour les boutons*/
    QPushButton *create_button;/*!<  bouton de création*/
    QPushButton *close_button;/*!<  bouton de fermeture */

};


/*! \class ArticleWindow
 * \brief Classe fille de QWidget pour la fenetre d'un article
 */
class ArticleWindow : public QWidget{

    Q_OBJECT

public:
    /*!
     * \brief Constructeur de ArticleWindow
     * \param _id id de la note
     * \param _title titre de la note
     * \param parent QWidget parent
     */
    ArticleWindow(QString _id, QString _title, QWidget *parent = 0);
    /*!
     * \brief Constructeur de ArticleWindow à partir d'une référence sur une note
     * on fait un dynamic cast sur la note pour la passer en article
     * \param note note à partir de laquelle on crée l'article
     * \param parent QWidget parent
     */
    ArticleWindow(Note& note, QWidget *parent = 0);
    /*!
     * \brief Getter du titre de l'article sur la page
     * \return le titre de l'article
     */
    QString getTitle() const { return title->text(); }
    /*!
     * \brief Getter du texte de l'article sur la page
     * \return le texte de l'article
     */
    QString getText() const { return text->toPlainText(); }
    /*!
     * \brief Getter de bouton de sauvegarde
     * \return un pointeur sur le bouton de sauvegarde
     */
    QPushButton* getSaveButton() { return save_button; }
    /*!
     * \brief Getter du bouton de suppression
     * \return un pointeur sur le bouton de suppression
     */
    QPushButton* getDeleteButton() { return delete_button; }

private:

    QVBoxLayout *fenetre_vbox;/*!< emplacement vertical de la fenetre */

    // ID
    QHBoxLayout *id_hbox;/*!< emplacement horizontal de l'id */
    QLabel *id_label;/*!< label pour le champ id */
    QLabel *id;/*!< id sous forme de label */

    QHBoxLayout *title_hbox;/*!< emplacement horizontal du titre */
    QLabel *title_label;/*!< label pour le champ titre*/
    QLineEdit *title;/*!< champ du titre*/

    QHBoxLayout *text_hbox;/*!< emplacement horizontal du texte */
    QLabel *text_label;/*!< label pour le champ du texte*/
    QTextEdit *text;/*!< champ du texte*/

    QHBoxLayout *button_hbox;/*!< emplacement horizontal pour les boutons*/
    QPushButton *save_button;/*!< bouton de sauvegarde*/
    QPushButton *close_button;/*!< bouton de fermeture*/
    QPushButton *delete_button;/*!< bouton de suppression*/

public slots:
    /*!
     * \brief Slot de sauvegarde
     */
    void save();
    /*!
     * \brief slot de suppression de l'article
     */
    void deleteArticle();
    /*!
     * \brief slot de restauration pour les notes archivées
     */
    void restaureArchive();

};

/*! \class MultimediaWindow
 * \brief Classe fille de QWidget, permet de gérer les fenetre de note Multimedia
 */
class MultimediaWindow : public QWidget{

    Q_OBJECT

public:
    /*!
     * \brief Constructeur de MultimediaWindow
     * \param _id id de la note Multimedia
     * \param _title titre de la note Multimedia
     * \param parent QWiddget parent de la fenetre
     */
    MultimediaWindow(QString _id, QString _title, QWidget *parent = 0);
    /*!
     * \brief Constructeur de MultimediaWindow à partir d'une référence sur une note
     * on fait un dynamic cast sur la note pour la passer en Multimedia
     * \param note référence sur la note
     * \param parent QWidget parent
     */
    MultimediaWindow(Note& note, QWidget *parent = 0);
    /*!
     * \brief Getter du titre sur la fenetre
     * \return le titre du multimedia
     */
    QString getTitle() const { return title->text(); }
    /*!
     * \brief Getter de la description sur la fenetre
     * \return la description du multimedia
     */
    QString getDescription() const { return description->toPlainText(); }
    /*!
     * \brief Getter du type
     * \return le type de la note
     */
    QString getType() const { return fichier_type->currentText(); }
    /*!
     * \brief Getter de bouton de sauvegarde
     * \return un pointeur sur le bouton de sauvegarde
     */
    QPushButton* getSaveButton() { return save_button; }
    /*!
     * \brief Getter du bouton de suppression
     * \return un pointeur sur le bouton de suppression
     */
    QPushButton* getDeleteButton() { return delete_button; }

private:

    QVBoxLayout *fenetre_vbox;/*!< emplacement vertical de la fenetre */

    // ID
    QHBoxLayout *id_hbox;/*!< emplacement horizontal de l'id */
    QLabel *id_label;/*!< label pour le champ id */
    QLabel *id;/*!< id sous forme de label */

    QHBoxLayout *title_hbox;/*!< emplacement horizontal du titre */
    QLabel *title_label;/*!< label pour le champ titre*/
    QLineEdit *title;/*!< champ du titre*/

    QHBoxLayout *description_hbox;/*!< emplacement horizontal pour la description*/
    QLabel *description_label;/*!< label pour le champ description */
    QTextEdit *description;/*!< champ description*/

    QHBoxLayout *fichier_hbox;/*!< emplacement horizontal le choix du fichier */
    QComboBox *fichier_type;/*!< combo box pour choisir le fichier*/
    QPushButton *fichier;/*!< bouton pour valider la selection du fichier*/

    QLabel *printed_path;/*!< label qui afficher le chemin vers le fichier*/
    QString path;/*!< chemin vers le fichier */

    QHBoxLayout *button_hbox;/*!< emplacement horizontal pour les boutons*/
    QPushButton *save_button;/*!< bouton de sauvegarde*/
    QPushButton *close_button;/*!< bouton de fermeture*/
    QPushButton *delete_button;/*!< bouton de suppression*/

public slots:
    /*!
     * \brief Slot pour la sauvegarde
     */
    void save();
    /*!
     * \brief Slot pour trouver un fichier
     */
    void trouveFichier();
    /*!
     * \brief slot de suppression du multimedia
     */
    void deleteMulti();
    /*!
     * \brief slot de restauration d'une note archivée
     */
    void restaureArchive();

};


/*! \class TacheWindows
 * \brief Classe fille de QWidget, permet de gérer les fenetres des taches
 */
class TacheWindow : public QWidget{

    Q_OBJECT

public:
    /*!
     * \brief Constructeur de TacheWindow
     * \param _id id de la tache
     * \param _title titre de la tache
     * \param parent QWidget parent
     */
    TacheWindow(QString _id, QString _title, QWidget *parent = 0);
    /*!
     * \brief Constructeur de TacheWindow à partir d'une référence sur une note
     * On fait un dynamic cast sur la référence pour qu'elle devienne une tache
     * \param note référence sur la note
     * \param parent QWidget parent
     */
    TacheWindow(Note& note, QWidget *parent = 0);
    /*!
     * \brief Getter du titre de la tache sur la fenetre
     * \return le titre de la tache
     */
    QString getTitle() const { return title->text(); }
    /*!
     * \brief Getter de l'action de la tache sur la fenetre
     * \return l'action de la tache
     */
    QString getAction() const { return action->toPlainText(); }
    /*!
     * \brief Getter de la priorité de la tache sur la fenetre
     * \return la priorité de la tache
     */
    QString getPriorite() const { return priorite->text(); }
    /*!
     * \brief Getter de l'échéance de la tache sur la fenetre
     * \return la date d'échéance de la tache
     */
    QDateTime getEcheance() const { return echeance->dateTime(); }
    /*!
     * \brief Getter du statut de la tache sur la fenetre
     * \return le statut de la tache
     */
    QString getStatut() const { return statut->currentText(); }
    /*!
     * \brief Getter du bouton de sauvegarde
     * \return un pointeur sur le bouton de sauvegarde
     */
    QPushButton* getSaveButton() { return save_button; }
    /*!
     * \brief Getter du bouton de suppression
     * \return un pointeur sur le bouton de suppression
     */
    QPushButton* getDeleteButton() { return delete_button; }

private:

    QVBoxLayout *fenetre_vbox;/*!< emplacement vertical de la fenetre */

    // ID
    QHBoxLayout *id_hbox;/*!< emplacement horizontal de l'id */
    QLabel *id_label;/*!< label pour le champ id */
    QLabel *id;/*!< id sous forme de label */

    QHBoxLayout *title_hbox;/*!< emplacement horizontal du titre */
    QLabel *title_label;/*!< label pour le champ du titre*/
    QLineEdit *title;/*!< champ du titre*/

    QHBoxLayout *action_hbox;/*!< emplacement horizontal de l'action */
    QLabel *action_label;/*!< label pour le champ de l'action*/
    QTextEdit *action;/*!< champ de l'action*/

    QHBoxLayout *priorite_hbox;/*!< emplacement horizontal pour la priorité*/
    QLabel *priorite_label;/*!< label pour le champ de la priorité*/
    QLineEdit *priorite;/*!< champ de la priorité*/

    QHBoxLayout *echeance_hbox;/*!< emplacement horizontal pour la date d'échéance*/
    QLabel *echeance_label;/*!< label pour le champ de la date d'échéance*/
    QDateTimeEdit *echeance;/*!< champ de la date d'échéance*/

    QHBoxLayout *statut_hbox;/*!< emplacement horizontal pour le statut*/
    QLabel *statut_label;/*!< label pour le champ du statut*/
    QComboBox *statut;/*!< champ du statut*/

    QHBoxLayout *button_hbox;/*!< emplacement horizontal pour les boutons*/
    QPushButton *save_button;/*!< bouton de sauvegarde*/
    QPushButton *close_button;/*!< bouton de fermeture*/
    QPushButton *delete_button;/*!< bouton de suppression*/

public slots:
    /*!
     * \brief slot pour la sauvegarde
     */
    void save();
    /*!
     * \brief slot pour la suppression de la tache
     */
    void deleteTache();
    /*!
     * \brief slot pour la restauration d'une tache archivée
     */
    void restaureArchive();

};

#endif // NOTEWINDOW_H
