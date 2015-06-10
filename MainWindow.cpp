#include "MainWindow.h"

#include "ShapeState.h"
#include "BeginState.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent)
{
    m_ui.setupUi(this);

   // setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);
    //setWindowFlags(Qt::Tool);
    resize(QApplication::desktop()->size());

    m_crtState.reset(new BeginState);
    m_crtState->init(this);

    m_serialPort.reset(new QSerialPort("/dev/ttyACM0"));
    m_serialPort->setBaudRate(9600);
    if (m_serialPort->open(QIODevice::ReadWrite) == false)
    {
        QMessageBox::critical(this, "Error!!!", "Cannot open serial port");
        //abort();
    }

    QDir().mkdir("data");


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

    auto available = m_serialPort->bytesAvailable();
    if (available > 0)
    {
        std::vector<char> incomingData;
        incomingData.resize(available);

        m_serialPort->read(incomingData.data(), available);

        StateData& stateData = m_crtState->getData();
        if (stateData.sensorDataFile.is_open())
        {
            for (auto c: incomingData)
            {
                if (c == '\r')
                {
                    ; // we don't do anything
                }
                else if (c == '\n')
                {
                    //we're done with this line, start a new data
                    stateData.sensorData.push_back(SensorData());
                }
                else
                {
                    //first line? Add ad new data
                    if (stateData.sensorData.empty())
                    {
                        stateData.sensorData.push_back(SensorData());
                    }

                    //accumulate the data from the current line
                    SensorData& data = stateData.sensorData.back();
                    data.value.push_back(c);
                }
            }
        }
    }


    std::unique_ptr<State> newState = m_crtState->finish();
    if (newState != nullptr)
    {
        m_crtState = std::move(newState);
        m_crtState->init(this);
    }
}
