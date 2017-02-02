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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *userNameLabel;
    QLineEdit *userNameInput;
    QLabel *userPassLabel;
    QLineEdit *userPassInput;
    QDialogButtonBox *authButtonBox;

    void setupUi(QDialog *AuthDialog)
    {
        if (AuthDialog->objectName().isEmpty())
            AuthDialog->setObjectName(QStringLiteral("AuthDialog"));
        AuthDialog->resize(246, 207);
        layoutWidget = new QWidget(AuthDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(43, 24, 169, 143));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        userNameLabel = new QLabel(layoutWidget);
        userNameLabel->setObjectName(QStringLiteral("userNameLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Monospace"));
        font.setPointSize(12);
        userNameLabel->setFont(font);

        verticalLayout->addWidget(userNameLabel);

        userNameInput = new QLineEdit(layoutWidget);
        userNameInput->setObjectName(QStringLiteral("userNameInput"));
        QFont font1;
        font1.setFamily(QStringLiteral("Monospace"));
        font1.setPointSize(11);
        userNameInput->setFont(font1);

        verticalLayout->addWidget(userNameInput);

        userPassLabel = new QLabel(layoutWidget);
        userPassLabel->setObjectName(QStringLiteral("userPassLabel"));
        userPassLabel->setFont(font);

        verticalLayout->addWidget(userPassLabel);

        userPassInput = new QLineEdit(layoutWidget);
        userPassInput->setObjectName(QStringLiteral("userPassInput"));
        userPassInput->setFont(font1);
        userPassInput->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        userPassInput->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(userPassInput);

        authButtonBox = new QDialogButtonBox(layoutWidget);
        authButtonBox->setObjectName(QStringLiteral("authButtonBox"));
        authButtonBox->setFont(font);
        authButtonBox->setOrientation(Qt::Horizontal);
        authButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(authButtonBox);

        QWidget::setTabOrder(userNameInput, userPassInput);

        retranslateUi(AuthDialog);
        QObject::connect(authButtonBox, SIGNAL(accepted()), AuthDialog, SLOT(accept()));
        QObject::connect(authButtonBox, SIGNAL(rejected()), AuthDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AuthDialog);
    } // setupUi

    void retranslateUi(QDialog *AuthDialog)
    {
        AuthDialog->setWindowTitle(QApplication::translate("AuthDialog", "Dialog", 0));
        userNameLabel->setText(QApplication::translate("AuthDialog", "Nom", 0));
        userPassLabel->setText(QApplication::translate("AuthDialog", "Mot de passe", 0));
    } // retranslateUi

};

namespace Ui {
    class AuthDialog: public Ui_AuthDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTAUTHDIALOG_H
