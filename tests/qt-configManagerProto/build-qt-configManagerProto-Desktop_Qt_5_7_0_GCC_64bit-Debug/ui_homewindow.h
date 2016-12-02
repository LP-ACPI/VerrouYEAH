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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *ZonneSavegardes;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QListView *listSaves;
    QFrame *zoneDrop;
    QHBoxLayout *horizontalLayout;
    QPushButton *newBackupButton;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuVerrouYEAH_accueil;

    void setupUi(QMainWindow *HomeWindow)
    {
        if (HomeWindow->objectName().isEmpty())
            HomeWindow->setObjectName(QStringLiteral("HomeWindow"));
        HomeWindow->resize(380, 372);
        centralWidget = new QWidget(HomeWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        ZonneSavegardes = new QScrollArea(centralWidget);
        ZonneSavegardes->setObjectName(QStringLiteral("ZonneSavegardes"));
        ZonneSavegardes->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 360, 261));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        listSaves = new QListView(scrollAreaWidgetContents);
        listSaves->setObjectName(QStringLiteral("listSaves"));

        verticalLayout_2->addWidget(listSaves);

        ZonneSavegardes->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(ZonneSavegardes);

        zoneDrop = new QFrame(centralWidget);
        zoneDrop->setObjectName(QStringLiteral("zoneDrop"));
        zoneDrop->setAutoFillBackground(true);
        zoneDrop->setFrameShape(QFrame::StyledPanel);
        zoneDrop->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(zoneDrop);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        newBackupButton = new QPushButton(zoneDrop);
        newBackupButton->setObjectName(QStringLiteral("newBackupButton"));

        horizontalLayout->addWidget(newBackupButton);


        verticalLayout->addWidget(zoneDrop);

        HomeWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(HomeWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        HomeWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(HomeWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 380, 20));
        menuVerrouYEAH_accueil = new QMenu(menuBar);
        menuVerrouYEAH_accueil->setObjectName(QStringLiteral("menuVerrouYEAH_accueil"));
        HomeWindow->setMenuBar(menuBar);

        menuBar->addAction(menuVerrouYEAH_accueil->menuAction());

        retranslateUi(HomeWindow);

        QMetaObject::connectSlotsByName(HomeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HomeWindow)
    {
        HomeWindow->setWindowTitle(QApplication::translate("HomeWindow", "HomeWindow", 0));
        newBackupButton->setText(QApplication::translate("HomeWindow", "Nouvelle sauvegarde", 0));
        menuVerrouYEAH_accueil->setTitle(QApplication::translate("HomeWindow", "options", 0));
    } // retranslateUi

};

namespace Ui {
    class HomeWindow: public Ui_HomeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEWINDOW_H
