/********************************************************************************
** Form generated from reading UI file 'backupwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKUPWIDGET_H
#define UI_BACKUPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BackupWidget
{
public:
    QLabel *icon;
    QPushButton *trashButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *backupName;
    QLabel *backupSource;
    QLabel *backupTarget;
    QPushButton *configButton;

    void setupUi(QWidget *BackupWidget)
    {
        if (BackupWidget->objectName().isEmpty())
            BackupWidget->setObjectName(QStringLiteral("BackupWidget"));
        BackupWidget->resize(545, 80);
        icon = new QLabel(BackupWidget);
        icon->setObjectName(QStringLiteral("icon"));
        icon->setGeometry(QRect(30, 10, 61, 61));
        icon->setAlignment(Qt::AlignCenter);
        trashButton = new QPushButton(BackupWidget);
        trashButton->setObjectName(QStringLiteral("trashButton"));
        trashButton->setGeometry(QRect(470, 20, 41, 41));
        layoutWidget = new QWidget(BackupWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 10, 261, 61));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        backupName = new QLabel(layoutWidget);
        backupName->setObjectName(QStringLiteral("backupName"));
        QFont font;
        font.setFamily(QStringLiteral("Monospace"));
        font.setPointSize(14);
        backupName->setFont(font);

        verticalLayout->addWidget(backupName);

        backupSource = new QLabel(layoutWidget);
        backupSource->setObjectName(QStringLiteral("backupSource"));
        backupSource->setLineWidth(1);

        verticalLayout->addWidget(backupSource);

        backupTarget = new QLabel(layoutWidget);
        backupTarget->setObjectName(QStringLiteral("backupTarget"));

        verticalLayout->addWidget(backupTarget);

        configButton = new QPushButton(BackupWidget);
        configButton->setObjectName(QStringLiteral("configButton"));
        configButton->setGeometry(QRect(390, 10, 61, 61));

        retranslateUi(BackupWidget);

        QMetaObject::connectSlotsByName(BackupWidget);
    } // setupUi

    void retranslateUi(QWidget *BackupWidget)
    {
        BackupWidget->setWindowTitle(QApplication::translate("BackupWidget", "Form", 0));
        icon->setText(QString());
        trashButton->setText(QString());
        backupName->setText(QApplication::translate("BackupWidget", "NomSauvegarde", 0));
        backupSource->setText(QApplication::translate("BackupWidget", "Source", 0));
        backupTarget->setText(QApplication::translate("BackupWidget", "Cible", 0));
        configButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BackupWidget: public Ui_BackupWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKUPWIDGET_H
