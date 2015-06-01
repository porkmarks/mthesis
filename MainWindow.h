#pragma once

#include <QDialog>
#include <QtGui>
#include <QtCore>

#include <chrono>

#include "ui_MainWindow.h"
#include "State.h"


class MainWindow : public QDialog
{
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void paintEvent(QPaintEvent *e);

    Ui::MainWindow m_ui;

    std::unique_ptr<State> m_crtState;

};
