/********************************************************************************
** Form generated from reading UI file 'createnewsave.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATENEWSAVE_H
#define UI_CREATENEWSAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *saveNameLabel;
    QLineEdit *saveNameInput;
    QHBoxLayout *horizontalLayout_2;
    QLabel *srcDirLabel;
    QPushButton *srcDirChoose;
    QHBoxLayout *horizontalLayout;
    QLabel *trgDirLabel;
    QPushButton *trgDirChoose;
    QLabel *commentLabel;
    QPlainTextEdit *commentInput;
    QDialogButtonBox *newSaveButtonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(305, 405);
        widget = new QWidget(Dialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 30, 260, 352));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        saveNameLabel = new QLabel(widget);
        saveNameLabel->setObjectName(QStringLiteral("saveNameLabel"));

        horizontalLayout_3->addWidget(saveNameLabel);

        saveNameInput = new QLineEdit(widget);
        saveNameInput->setObjectName(QStringLiteral("saveNameInput"));

        horizontalLayout_3->addWidget(saveNameInput);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        srcDirLabel = new QLabel(widget);
        srcDirLabel->setObjectName(QStringLiteral("srcDirLabel"));

        horizontalLayout_2->addWidget(srcDirLabel);

        srcDirChoose = new QPushButton(widget);
        srcDirChoose->setObjectName(QStringLiteral("srcDirChoose"));

        horizontalLayout_2->addWidget(srcDirChoose);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 10);
        trgDirLabel = new QLabel(widget);
        trgDirLabel->setObjectName(QStringLiteral("trgDirLabel"));

        horizontalLayout->addWidget(trgDirLabel);

        trgDirChoose = new QPushButton(widget);
        trgDirChoose->setObjectName(QStringLiteral("trgDirChoose"));

        horizontalLayout->addWidget(trgDirChoose);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addLayout(verticalLayout_2);

        commentLabel = new QLabel(widget);
        commentLabel->setObjectName(QStringLiteral("commentLabel"));

        verticalLayout->addWidget(commentLabel);


        verticalLayout_3->addLayout(verticalLayout);

        commentInput = new QPlainTextEdit(widget);
        commentInput->setObjectName(QStringLiteral("commentInput"));
        commentInput->setEnabled(true);
        commentInput->setMaximumSize(QSize(256, 250));
        commentInput->setBaseSize(QSize(150, 150));

        verticalLayout_3->addWidget(commentInput);


        verticalLayout_4->addLayout(verticalLayout_3);

        newSaveButtonBox = new QDialogButtonBox(widget);
        newSaveButtonBox->setObjectName(QStringLiteral("newSaveButtonBox"));
        newSaveButtonBox->setOrientation(Qt::Horizontal);
        newSaveButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(newSaveButtonBox);

        newSaveButtonBox->raise();
        saveNameLabel->raise();
        commentInput->raise();
        saveNameInput->raise();
        srcDirLabel->raise();
        srcDirChoose->raise();
        trgDirLabel->raise();
        commentLabel->raise();
        QWidget::setTabOrder(saveNameInput, srcDirChoose);
        QWidget::setTabOrder(srcDirChoose, trgDirChoose);
        QWidget::setTabOrder(trgDirChoose, commentInput);

        retranslateUi(Dialog);
        QObject::connect(newSaveButtonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(newSaveButtonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        saveNameLabel->setText(QApplication::translate("Dialog", "Nom", 0));
        srcDirLabel->setText(QApplication::translate("Dialog", "Source", 0));
        srcDirChoose->setText(QApplication::translate("Dialog", "choisir la source", 0));
        trgDirLabel->setText(QApplication::translate("Dialog", "Cible", 0));
        trgDirChoose->setText(QApplication::translate("Dialog", "choisir destination", 0));
        commentLabel->setText(QApplication::translate("Dialog", "Commentaire:", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATENEWSAVE_H
