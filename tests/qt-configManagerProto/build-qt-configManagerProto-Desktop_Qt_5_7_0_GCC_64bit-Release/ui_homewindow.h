/********************************************************************************
** Form generated from reading UI file 'homewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEWINDOW_H
#define UI_HOMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeWindow
{
public:
    QAction *actionRAZ;
    QAction *actionUtilisateur;
    QAction *action_propos;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QFrame *zoneDrop;
    QListWidget *backupList;
    QPushButton *newBackupButton;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuVerrouYEAH_accueil;
    QMenu *menu_aide;

    void setupUi(QMainWindow *HomeWindow)
    {
        if (HomeWindow->objectName().isEmpty())
            HomeWindow->setObjectName(QStringLiteral("HomeWindow"));
        HomeWindow->resize(580, 400);
        HomeWindow->setMinimumSize(QSize(580, 400));
        HomeWindow->setMaximumSize(QSize(580, 400));
        actionRAZ = new QAction(HomeWindow);
        actionRAZ->setObjectName(QStringLiteral("actionRAZ"));
        actionUtilisateur = new QAction(HomeWindow);
        actionUtilisateur->setObjectName(QStringLiteral("actionUtilisateur"));
        action_propos = new QAction(HomeWindow);
        action_propos->setObjectName(QStringLiteral("action_propos"));
        centralWidget = new QWidget(HomeWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        zoneDrop = new QFrame(centralWidget);
        zoneDrop->setObjectName(QStringLiteral("zoneDrop"));
        zoneDrop->setAutoFillBackground(true);
        zoneDrop->setFrameShape(QFrame::StyledPanel);
        zoneDrop->setFrameShadow(QFrame::Raised);
        backupList = new QListWidget(zoneDrop);
        backupList->setObjectName(QStringLiteral("backupList"));
        backupList->setGeometry(QRect(11, 11, 541, 251));
        newBackupButton = new QPushButton(zoneDrop);
        newBackupButton->setObjectName(QStringLiteral("newBackupButton"));
        newBackupButton->setGeometry(QRect(10, 270, 541, 61));

        verticalLayout->addWidget(zoneDrop);

        HomeWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(HomeWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        HomeWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(HomeWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 580, 21));
        menuVerrouYEAH_accueil = new QMenu(menuBar);
        menuVerrouYEAH_accueil->setObjectName(QStringLiteral("menuVerrouYEAH_accueil"));
        menu_aide = new QMenu(menuBar);
        menu_aide->setObjectName(QStringLiteral("menu_aide"));
        HomeWindow->setMenuBar(menuBar);

        menuBar->addAction(menuVerrouYEAH_accueil->menuAction());
        menuBar->addAction(menu_aide->menuAction());
        menuVerrouYEAH_accueil->addAction(actionUtilisateur);
        menuVerrouYEAH_accueil->addAction(actionRAZ);
        menu_aide->addAction(action_propos);

        retranslateUi(HomeWindow);

        QMetaObject::connectSlotsByName(HomeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HomeWindow)
    {
        HomeWindow->setWindowTitle(QApplication::translate("HomeWindow", "HomeWindow", 0));
        actionRAZ->setText(QApplication::translate("HomeWindow", "RAZ", 0));
        actionUtilisateur->setText(QApplication::translate("HomeWindow", "Utilisateur", 0));
        action_propos->setText(QApplication::translate("HomeWindow", "\303\240 propos", 0));
        newBackupButton->setText(QApplication::translate("HomeWindow", "Nouvelle sauvegarde", 0));
        menuVerrouYEAH_accueil->setTitle(QApplication::translate("HomeWindow", "options", 0));
        menu_aide->setTitle(QApplication::translate("HomeWindow", "aide", 0));
    } // retranslateUi

};

namespace Ui {
    class HomeWindow: public Ui_HomeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEWINDOW_H
