/********************************************************************************
** Form generated from reading UI file 'BeginWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEGINWIDGET_H
#define UI_BEGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BeginWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *nameLabel;
    QLineEdit *lineEdit;
    QPushButton *startButton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *BeginWidget)
    {
        if (BeginWidget->objectName().isEmpty())
            BeginWidget->setObjectName(QStringLiteral("BeginWidget"));
        BeginWidget->resize(957, 690);
        horizontalLayout_2 = new QHBoxLayout(BeginWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label = new QLabel(BeginWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        nameLabel = new QLabel(BeginWidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        horizontalLayout->addWidget(nameLabel);

        lineEdit = new QLineEdit(BeginWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        startButton = new QPushButton(BeginWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setCheckable(true);

        horizontalLayout->addWidget(startButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        retranslateUi(BeginWidget);

        QMetaObject::connectSlotsByName(BeginWidget);
    } // setupUi

    void retranslateUi(QWidget *BeginWidget)
    {
        BeginWidget->setWindowTitle(QApplication::translate("BeginWidget", "Form", 0));
        label->setText(QApplication::translate("BeginWidget", "Hello human! Please identify yourself and press the button to begin the experiment  ", 0));
        nameLabel->setText(QApplication::translate("BeginWidget", "Name and Surname ", 0));
        lineEdit->setText(QString());
        startButton->setText(QApplication::translate("BeginWidget", "Let's go!", 0));
    } // retranslateUi

};

namespace Ui {
    class BeginWidget: public Ui_BeginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEGINWIDGET_H
