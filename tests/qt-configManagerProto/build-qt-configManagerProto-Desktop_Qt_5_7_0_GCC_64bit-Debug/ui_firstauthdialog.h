/********************************************************************************
** Form generated from reading UI file 'firstauthdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRSTAUTHDIALOG_H
#define UI_FIRSTAUTHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *authButtonBox;
    QLabel *userNameLabel;
    QLabel *userPassLabel;
    QLineEdit *userNameInput;
    QLineEdit *userPassInput;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(246, 193);
        authButtonBox = new QDialogButtonBox(Dialog);
        authButtonBox->setObjectName(QStringLiteral("authButtonBox"));
        authButtonBox->setGeometry(QRect(40, 140, 166, 21));
        QFont font;
        font.setFamily(QStringLiteral("Monospace"));
        font.setPointSize(12);
        authButtonBox->setFont(font);
        authButtonBox->setOrientation(Qt::Horizontal);
        authButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        userNameLabel = new QLabel(Dialog);
        userNameLabel->setObjectName(QStringLiteral("userNameLabel"));
        userNameLabel->setGeometry(QRect(40, 20, 30, 19));
        userNameLabel->setFont(font);
        userPassLabel = new QLabel(Dialog);
        userPassLabel->setObjectName(QStringLiteral("userPassLabel"));
        userPassLabel->setGeometry(QRect(40, 77, 120, 19));
        userPassLabel->setFont(font);
        userNameInput = new QLineEdit(Dialog);
        userNameInput->setObjectName(QStringLiteral("userNameInput"));
        userNameInput->setGeometry(QRect(40, 43, 166, 21));
        QFont font1;
        font1.setFamily(QStringLiteral("Monospace"));
        font1.setPointSize(11);
        userNameInput->setFont(font1);
        userPassInput = new QLineEdit(Dialog);
        userPassInput->setObjectName(QStringLiteral("userPassInput"));
        userPassInput->setGeometry(QRect(40, 100, 166, 21));
        userPassInput->setFont(font1);

        retranslateUi(Dialog);
        QObject::connect(authButtonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(authButtonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        userNameLabel->setText(QApplication::translate("Dialog", "Nom", 0));
        userPassLabel->setText(QApplication::translate("Dialog", "Mot de passe", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTAUTHDIALOG_H
