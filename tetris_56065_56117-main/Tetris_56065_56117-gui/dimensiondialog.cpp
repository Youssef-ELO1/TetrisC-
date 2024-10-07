#include "dimensiondialog.h"
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QIntValidator>
#include <QLabel>
#include <QMessageBox>


/**
 * @brief Constructeur de la classe DimensionDialog.
 *
 * Initialise la boîte de dialogue avec les champs pour entrer les dimensions du jeu, et configure les éléments de l'interface.
 * Définit également les actions pour les boutons et gère les interactions utilisateur nécessaires à la validation des dimensions saisies.
 *
 * @param parent Le widget parent de cette boîte de dialogue.
 */

DimensionDialog::DimensionDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Enter Game Dimensions");

    colsLineEdit = new QLineEdit;
    rowsLineEdit = new QLineEdit;

    // Set up validators to accept only integers
    colsLineEdit->setValidator(new QIntValidator);
    rowsLineEdit->setValidator(new QIntValidator);

    QFont helveticaFont("Helvetica");
    helveticaFont.setPointSize(11);
    QLabel *welcomeLabel = new QLabel("Bienvenue sur Tetris : 56065 56117  !<br><br>Si votre score atteint 10 000 points ou si vous effacez 20 lignes, vous remportez la partie !<br><br>Vous disposez de 5 minutes pour y parvenir !<br><br>Vous jouez avec les flèches et les lettre D et R pour drop et Rotation inverse<br><br>Bon jeu !");
    welcomeLabel->setWordWrap(true);
    welcomeLabel->setFont(helveticaFont);


    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Rows:", rowsLineEdit);
    formLayout->addRow("Cols:", colsLineEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    QPushButton *defaultButton = new QPushButton("Default");
    buttonBox->addButton(defaultButton, QDialogButtonBox::ActionRole);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &DimensionDialog::checkValuesAndAccept); // Check si ya des valeurs
    connect(defaultButton, &QPushButton::clicked, this, &DimensionDialog::defaultValues);
    connect(this, &DimensionDialog::rejected, this, &DimensionDialog::closeParent);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(welcomeLabel);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

/**
 * @brief Destructeur de la classe DimensionDialog.
 *
 * Ferme le widget parent lorsque la boîte de dialogue est détruite.
 */

DimensionDialog::~DimensionDialog()
{
    parentWidget()->close();
}

/**
 * @brief Récupère le nombre de colonnes spécifié par l'utilisateur.
 *
 * @return Le nombre de colonnes en tant que entier.
 */

int DimensionDialog::getCols() const
{
    return colsLineEdit->text().toInt();
}

/**
 * @brief Récupère le nombre de lignes spécifié par l'utilisateur.
 *
 * @return Le nombre de lignes en tant que entier.
 */

int DimensionDialog::getRows() const
{
    return rowsLineEdit->text().toInt();
}


/**
 * @brief Vérifie les valeurs entrées et accepte la boîte de dialogue si elles sont valides.
 *
 * Affiche un message d'erreur si les champs sont vides, sinon valide et ferme la boîte de dialogue.
*/

void DimensionDialog::checkValuesAndAccept() {
    // Vérifiez si les champs de dimension sont vides
    if (colsLineEdit->text().isEmpty() || rowsLineEdit->text().isEmpty()) {
        QMessageBox messageBox(QMessageBox::Warning, "Empty Fields", "Veuillez entrer des valeurs pour les dimensions du jeu.", QMessageBox::Ok, this);
        messageBox.exec();
    } else {
        accept();
    }
}

/**
 * @brief Ferme le widget parent.
 *
 * Utilisée comme slot connecté au signal 'rejected' de la boîte de dialogue.
*/

void DimensionDialog::closeParent() {
    parentWidget()->close();
}

/**
 * @brief Définit les valeurs par défaut des dimensions du jeu et accepte la boîte de dialogue.
 *
 * Fixe les dimensions par défaut à 10 colonnes et 20 lignes, puis valide la boîte de dialogue.
*/

void DimensionDialog::defaultValues() {
    colsLineEdit->setText("10");
    rowsLineEdit->setText("20");
    accept();
}
