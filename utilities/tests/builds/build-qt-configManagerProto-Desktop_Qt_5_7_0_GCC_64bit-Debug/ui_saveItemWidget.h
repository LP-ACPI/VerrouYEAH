/********************************************************************************
** Form generated from reading UI file 'saveItemWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEITEMWIDGET_H
#define UI_SAVEITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QLabel *SaveName;
    QLabel *SaveSource;
    QLabel *SaveSource_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(271, 75);
        widget = new QWidget(Form);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 0, 214, 89));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        SaveName = new QLabel(widget);
        SaveName->setObjectName(QStringLiteral("SaveName"));
        QFont font;
        font.setFamily(QStringLiteral("Monospace"));
        font.setPointSize(14);
        SaveName->setFont(font);

        verticalLayout->addWidget(SaveName);

        SaveSource = new QLabel(widget);
        SaveSource->setObjectName(QStringLiteral("SaveSource"));

        verticalLayout->addWidget(SaveSource);

        SaveSource_2 = new QLabel(widget);
        SaveSource_2->setObjectName(QStringLiteral("SaveSource_2"));

        verticalLayout->addWidget(SaveSource_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        label->setText(QApplication::translate("Form", "icon", 0));
        SaveName->setText(QApplication::translate("Form", "NomSauvegarde", 0));
        SaveSource->setText(QApplication::translate("Form", "Source", 0));
        SaveSource_2->setText(QApplication::translate("Form", "Fr\303\251quence", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEITEMWIDGET_H
