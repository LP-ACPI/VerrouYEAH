/********************************************************************************
** Form generated from reading UI file 'authdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHDIALOG_H
#define UI_AUTHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthDialog
{
public:
    QTabWidget *authTabWidget;
    QWidget *authTab;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QComboBox *loginList;
    QCheckBox *favoriteUser;
    QSpacerItem *verticalSpacer;
    QLabel *userPassLabel;
    QLineEdit *userPassInput;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *authButtonBox;
    QLabel *logo;
    QWidget *creationTab;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *userPassLabel_3;
    QLineEdit *newUserLoginInput;
    QLabel *userPassLabel_2;
    QLineEdit *newUserPassInput;
    QLabel *userPassLabel_4;
    QLineEdit *newUserPassInputConfirm;
    QSpacerItem *verticalSpacer_3;
    QDialogButtonBox *subscriptButtonBox;

    void setupUi(QDialog *AuthDialog)
    {
        if (AuthDialog->objectName().isEmpty())
            AuthDialog->setObjectName(QStringLiteral("AuthDialog"));
        AuthDialog->resize(250, 335);
        AuthDialog->setMinimumSize(QSize(250, 300));
        AuthDialog->setMaximumSize(QSize(250, 335));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/icone_temporaire.png"), QSize(), QIcon::Normal, QIcon::Off);
        AuthDialog->setWindowIcon(icon);
        AuthDialog->setStyleSheet(QStringLiteral(""));
        authTabWidget = new QTabWidget(AuthDialog);
        authTabWidget->setObjectName(QStringLiteral("authTabWidget"));
        authTabWidget->setGeometry(QRect(0, 0, 251, 341));
        authTabWidget->setStyleSheet(QStringLiteral(""));
        authTab = new QWidget();
        authTab->setObjectName(QStringLiteral("authTab"));
        layoutWidget = new QWidget(authTab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 110, 201, 191));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        loginList = new QComboBox(layoutWidget);
        loginList->setObjectName(QStringLiteral("loginList"));
        loginList->setStyleSheet(QLatin1String("height:28px;\n"
"font-size:21px;"));

        verticalLayout->addWidget(loginList);

        favoriteUser = new QCheckBox(layoutWidget);
        favoriteUser->setObjectName(QStringLiteral("favoriteUser"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(favoriteUser->sizePolicy().hasHeightForWidth());
        favoriteUser->setSizePolicy(sizePolicy);
        favoriteUser->setMinimumSize(QSize(0, 28));
        favoriteUser->setAutoFillBackground(false);

        verticalLayout->addWidget(favoriteUser);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        userPassLabel = new QLabel(layoutWidget);
        userPassLabel->setObjectName(QStringLiteral("userPassLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Monospace"));
        font.setPointSize(12);
        userPassLabel->setFont(font);
        userPassLabel->setStyleSheet(QStringLiteral(""));
        userPassLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout->addWidget(userPassLabel);

        userPassInput = new QLineEdit(layoutWidget);
        userPassInput->setObjectName(QStringLiteral("userPassInput"));
        QFont font1;
        font1.setFamily(QStringLiteral("Monospace"));
        font1.setPointSize(11);
        userPassInput->setFont(font1);
        userPassInput->setStyleSheet(QStringLiteral(""));
        userPassInput->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        userPassInput->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(userPassInput);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        authButtonBox = new QDialogButtonBox(layoutWidget);
        authButtonBox->setObjectName(QStringLiteral("authButtonBox"));
        authButtonBox->setFont(font);
        authButtonBox->setStyleSheet(QStringLiteral(""));
        authButtonBox->setOrientation(Qt::Horizontal);
        authButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        authButtonBox->setCenterButtons(true);

        verticalLayout->addWidget(authButtonBox);

        logo = new QLabel(authTab);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setGeometry(QRect(20, 10, 211, 100));
        logo->setMinimumSize(QSize(0, 100));
        logo->setMaximumSize(QSize(16777215, 16777215));
        logo->setAlignment(Qt::AlignCenter);
        logo->setIndent(0);
        authTabWidget->addTab(authTab, QString());
        creationTab = new QWidget();
        creationTab->setObjectName(QStringLiteral("creationTab"));
        layoutWidget_2 = new QWidget(creationTab);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 30, 222, 221));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        userPassLabel_3 = new QLabel(layoutWidget_2);
        userPassLabel_3->setObjectName(QStringLiteral("userPassLabel_3"));
        userPassLabel_3->setFont(font);
        userPassLabel_3->setStyleSheet(QStringLiteral(""));
        userPassLabel_3->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_2->addWidget(userPassLabel_3);

        newUserLoginInput = new QLineEdit(layoutWidget_2);
        newUserLoginInput->setObjectName(QStringLiteral("newUserLoginInput"));
        newUserLoginInput->setFont(font1);
        newUserLoginInput->setStyleSheet(QStringLiteral(""));
        newUserLoginInput->setInputMethodHints(Qt::ImhNone);
        newUserLoginInput->setEchoMode(QLineEdit::Normal);

        verticalLayout_2->addWidget(newUserLoginInput);

        userPassLabel_2 = new QLabel(layoutWidget_2);
        userPassLabel_2->setObjectName(QStringLiteral("userPassLabel_2"));
        userPassLabel_2->setFont(font);
        userPassLabel_2->setStyleSheet(QStringLiteral(""));
        userPassLabel_2->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_2->addWidget(userPassLabel_2);

        newUserPassInput = new QLineEdit(layoutWidget_2);
        newUserPassInput->setObjectName(QStringLiteral("newUserPassInput"));
        newUserPassInput->setFont(font1);
        newUserPassInput->setStyleSheet(QStringLiteral(""));
        newUserPassInput->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        newUserPassInput->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(newUserPassInput);

        userPassLabel_4 = new QLabel(layoutWidget_2);
        userPassLabel_4->setObjectName(QStringLiteral("userPassLabel_4"));
        userPassLabel_4->setFont(font);
        userPassLabel_4->setStyleSheet(QStringLiteral(""));
        userPassLabel_4->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_2->addWidget(userPassLabel_4);

        newUserPassInputConfirm = new QLineEdit(layoutWidget_2);
        newUserPassInputConfirm->setObjectName(QStringLiteral("newUserPassInputConfirm"));
        newUserPassInputConfirm->setFont(font1);
        newUserPassInputConfirm->setStyleSheet(QStringLiteral(""));
        newUserPassInputConfirm->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        newUserPassInputConfirm->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(newUserPassInputConfirm);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        subscriptButtonBox = new QDialogButtonBox(layoutWidget_2);
        subscriptButtonBox->setObjectName(QStringLiteral("subscriptButtonBox"));
        subscriptButtonBox->setFont(font);
        subscriptButtonBox->setStyleSheet(QStringLiteral(""));
        subscriptButtonBox->setOrientation(Qt::Horizontal);
        subscriptButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        subscriptButtonBox->setCenterButtons(true);

        verticalLayout_2->addWidget(subscriptButtonBox);

        authTabWidget->addTab(creationTab, QString());

        retranslateUi(AuthDialog);

        authTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AuthDialog);
    } // setupUi

    void retranslateUi(QDialog *AuthDialog)
    {
        AuthDialog->setWindowTitle(QApplication::translate("AuthDialog", "Authentification", 0));
#ifndef QT_NO_TOOLTIP
        favoriteUser->setToolTip(QApplication::translate("AuthDialog", "Connexion automaitique \303\240 cet utilisateur", 0));
#endif // QT_NO_TOOLTIP
        favoriteUser->setText(QApplication::translate("AuthDialog", "connexion automatique", 0));
        userPassLabel->setText(QApplication::translate("AuthDialog", "Mot de passe", 0));
        logo->setText(QApplication::translate("AuthDialog", "Logo", 0));
        authTabWidget->setTabText(authTabWidget->indexOf(authTab), QApplication::translate("AuthDialog", "Identification", 0));
        userPassLabel_3->setText(QApplication::translate("AuthDialog", "Nouvel utilisateur", 0));
        userPassLabel_2->setText(QApplication::translate("AuthDialog", "Mot de passe", 0));
        userPassLabel_4->setText(QApplication::translate("AuthDialog", "Confirmer mot de passe", 0));
        authTabWidget->setTabText(authTabWidget->indexOf(creationTab), QApplication::translate("AuthDialog", "Inscription", 0));
    } // retranslateUi

};

namespace Ui {
    class AuthDialog: public Ui_AuthDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHDIALOG_H
