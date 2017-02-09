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
    QLabel *BackupName;
    QLabel *BackupSource;
    QLabel *BackupCible;
    QPushButton *decryptButton;

    void setupUi(QWidget *BackupWidget)
    {
        if (BackupWidget->objectName().isEmpty())
            BackupWidget->setObjectName(QStringLiteral("BackupWidget"));
        BackupWidget->resize(545, 67);
        icon = new QLabel(BackupWidget);
        icon->setObjectName(QStringLiteral("icon"));
        icon->setGeometry(QRect(30, 10, 41, 41));
        icon->setAlignment(Qt::AlignCenter);
        trashButton = new QPushButton(BackupWidget);
        trashButton->setObjectName(QStringLiteral("trashButton"));
        trashButton->setGeometry(QRect(490, 10, 41, 51));
        layoutWidget = new QWidget(BackupWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 0, 261, 66));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        BackupName = new QLabel(layoutWidget);
        BackupName->setObjectName(QStringLiteral("BackupName"));
        QFont font;
        font.setFamily(QStringLiteral("Monospace"));
        font.setPointSize(14);
        BackupName->setFont(font);

        verticalLayout->addWidget(BackupName);

        BackupSource = new QLabel(layoutWidget);
        BackupSource->setObjectName(QStringLiteral("BackupSource"));
        BackupSource->setLineWidth(1);

        verticalLayout->addWidget(BackupSource);

        BackupCible = new QLabel(layoutWidget);
        BackupCible->setObjectName(QStringLiteral("BackupCible"));

        verticalLayout->addWidget(BackupCible);

        decryptButton = new QPushButton(BackupWidget);
        decryptButton->setObjectName(QStringLiteral("decryptButton"));
        decryptButton->setGeometry(QRect(430, 10, 41, 51));

        retranslateUi(BackupWidget);

        QMetaObject::connectSlotsByName(BackupWidget);
    } // setupUi

    void retranslateUi(QWidget *BackupWidget)
    {
        BackupWidget->setWindowTitle(QApplication::translate("BackupWidget", "Form", 0));
        icon->setText(QString());
        trashButton->setText(QString());
        BackupName->setText(QApplication::translate("BackupWidget", "NomSauvegarde", 0));
        BackupSource->setText(QApplication::translate("BackupWidget", "Source", 0));
        BackupCible->setText(QApplication::translate("BackupWidget", "Cible", 0));
        decryptButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BackupWidget: public Ui_BackupWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKUPWIDGET_H
