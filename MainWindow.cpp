#include "MainWindow.h"

#include "ShapeState.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent)
{
    m_ui.setupUi(this);

    m_crtState.reset(new ShapeState);
    m_crtState->init(this);

    auto timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, &QTimer::timeout, [this]()
    {
        update();
    });
    timer->start(16);
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent*)
{
    m_crtState->process();

    std::unique_ptr<State> newState = m_crtState->finish();
    if (newState != nullptr)
    {
        m_crtState = std::move(newState);
        m_crtState->init(this);
    }
}
