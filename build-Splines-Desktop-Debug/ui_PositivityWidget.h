/********************************************************************************
** Form generated from reading UI file 'PositivityWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSITIVITYWIDGET_H
#define UI_POSITIVITYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PositivityWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QSlider *positivity;
    QLabel *label_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *PositivityWidget)
    {
        if (PositivityWidget->objectName().isEmpty())
            PositivityWidget->setObjectName(QStringLiteral("PositivityWidget"));
        PositivityWidget->resize(810, 77);
        horizontalLayout = new QHBoxLayout(PositivityWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(PositivityWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/pics/AS_unhappy.png")));

        horizontalLayout->addWidget(label);

        widget = new QWidget(PositivityWidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        positivity = new QSlider(widget);
        positivity->setObjectName(QStringLiteral("positivity"));
        positivity->setValue(50);
        positivity->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(positivity);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/pics/AS_intensity_cue.png")));

        verticalLayout->addWidget(label_3);


        horizontalLayout->addWidget(widget);

        label_2 = new QLabel(PositivityWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/pics/AS_happy.png")));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(PositivityWidget);

        QMetaObject::connectSlotsByName(PositivityWidget);
    } // setupUi

    void retranslateUi(QWidget *PositivityWidget)
    {
        PositivityWidget->setWindowTitle(QApplication::translate("PositivityWidget", "Form", 0));
        label->setText(QString());
        label_3->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PositivityWidget: public Ui_PositivityWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSITIVITYWIDGET_H
