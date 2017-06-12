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
     * \return
     */
    QString getText() const { return text->toPlainText(); }
    /*!
     * \brief Getter de bouton de sauvegarde
     * \return
     */
    QPushButton* getSaveButton() { return save_button; }
    /*!
     * \brief Getter du bouton de suppression
     * \return
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
     * \brief slot de restauration
     */
    void restaureArchive();

};


class MultimediaWindow : public QWidget{

    Q_OBJECT

public:
    MultimediaWindow(QString _id, QString _title, QWidget *parent = 0);
    MultimediaWindow(Note& note, QWidget *parent = 0);
    QString getTitle() const { return title->text(); }
    QString getDescription() const { return description->toPlainText(); }
    QString getType() const { return fichier_type->currentText(); }
    QPushButton* getSaveButton() { return save_button; }
    QPushButton* getDeleteButton() { return delete_button; }

private:

    QVBoxLayout *fenetre_vbox;

    // ID
    QHBoxLayout *id_hbox;
    QLabel *id_label;
    QLabel *id;

    QHBoxLayout *title_hbox;
    QLabel *title_label;
    QLineEdit *title;

    QHBoxLayout *description_hbox;
    QLabel *description_label;
    QTextEdit *description;

    QHBoxLayout *fichier_hbox;
    QComboBox *fichier_type;
    QPushButton *fichier;

    QLabel *printed_path;
    QString path;

    QHBoxLayout *button_hbox;
    QPushButton *save_button;
    QPushButton *close_button;
    QPushButton *delete_button;

public slots:
    void save();
    void trouveFichier();
    void deleteMulti();
    void restaureArchive();

};



class TacheWindow : public QWidget{

    Q_OBJECT

public:
    TacheWindow(QString _id, QString _title, QWidget *parent = 0);
    TacheWindow(Note& note, QWidget *parent = 0);
    QString getTitle() const { return title->text(); }
    QString getAction() const { return action->toPlainText(); }
    QString getPriorite() const { return priorite->text(); }
    QDateTime getEcheance() const { return echeance->dateTime(); }
    QString getStatut() const { return statut->currentText(); }
    QPushButton* getSaveButton() { return save_button; }
    QPushButton* getDeleteButton() { return delete_button; }

private:

    QVBoxLayout *fenetre_vbox;

    // ID
    QHBoxLayout *id_hbox;
    QLabel *id_label;
    QLabel *id;

    QHBoxLayout *title_hbox;
    QLabel *title_label;
    QLineEdit *title;

    QHBoxLayout *action_hbox;
    QLabel *action_label;
    QTextEdit *action;

    QHBoxLayout *priorite_hbox;
    QLabel *priorite_label;
    QLineEdit *priorite;

    QHBoxLayout *echeance_hbox;
    QLabel *echeance_label;
    QDateTimeEdit *echeance;

    QHBoxLayout *statut_hbox;
    QLabel *statut_label;
    QComboBox *statut;

    QHBoxLayout *button_hbox;
    QPushButton *save_button;
    QPushButton *close_button;
    QPushButton *delete_button;

public slots:
    void save();
    void deleteTache();
    void restaureArchive();

};

#endif // NOTEWINDOW_H
