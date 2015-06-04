/********************************************************************************
** Form generated from reading UI file 'ArousalWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AROUSALWIDGET_H
#define UI_AROUSALWIDGET_H

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

class Ui_ArousalWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QSlider *arousal;
    QLabel *label_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *ArousalWidget)
    {
        if (ArousalWidget->objectName().isEmpty())
            ArousalWidget->setObjectName(QStringLiteral("ArousalWidget"));
        ArousalWidget->resize(814, 77);
        horizontalLayout = new QHBoxLayout(ArousalWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(ArousalWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/pics/AS_sleepy.png")));

        horizontalLayout->addWidget(label);

        widget = new QWidget(ArousalWidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        arousal = new QSlider(widget);
        arousal->setObjectName(QStringLiteral("arousal"));
        arousal->setValue(50);
        arousal->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(arousal);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/pics/AS_intensity_cue.png")));

        verticalLayout->addWidget(label_3);


        horizontalLayout->addWidget(widget);

        label_2 = new QLabel(ArousalWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/pics/AS_wideawake.png")));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        retranslateUi(ArousalWidget);

        QMetaObject::connectSlotsByName(ArousalWidget);
    } // setupUi

    void retranslateUi(QWidget *ArousalWidget)
    {
        ArousalWidget->setWindowTitle(QApplication::translate("ArousalWidget", "Form", 0));
        label->setText(QString());
        label_3->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ArousalWidget: public Ui_ArousalWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AROUSALWIDGET_H
