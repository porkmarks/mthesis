#include "AssesmentState.h"
#include <iostream>

const std::chrono::seconds ASSESMENT_DURATION(30);


AssesmentState::AssesmentState(std::shared_ptr<StateData> data)
{
    m_data = data;
}

AssesmentState::~AssesmentState()
{
    delete m_widget;
}


void AssesmentState::init(QWidget* mainWidget)
{


    //create a new widget to put our sliders into
    m_widget = new QWidget(mainWidget);

    //add the widget to the main widget (the main window)
    mainWidget->layout()->addWidget(m_widget);

    //the sliders will be layed out vertically
    m_widget->setLayout(new QVBoxLayout(m_widget));

    //add a spacer to push everything up
    m_widget->layout()->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    m_widget->layout()->setSpacing(50);


    //create 2 widgets for our 2 sliders. The widgets are owned by m_widget (their parent)
    auto* arousalWidget = new QWidget(m_widget);
    auto* positivityWidget = new QWidget(m_widget);

    //construct the UIs in the widgets. This will spawn all the icons and sliders
    m_arousalUi.setupUi(arousalWidget);
    m_positivityUi.setupUi(positivityWidget);

    //random number generator
    std::random_device rd;
    std::default_random_engine ren(rd());
    std::uniform_int_distribution<int> rnd(0, 100);


    //randomize the order in which the sliders are added to the layout
    if (rnd(ren) < 50)
    {
        m_widget->layout()->addWidget(arousalWidget);
        m_widget->layout()->addWidget(positivityWidget);
    }
    else
    {
        m_widget->layout()->addWidget(positivityWidget);
        m_widget->layout()->addWidget(arousalWidget);
    }

    //add finish button
    //should be disabled until both sliders are moved
    m_button = new QPushButton("Assess the shape in order to continue", m_widget);
    // set size and location of the button
    m_widget->layout()->addWidget(m_button);
    m_button->setEnabled(false);
    m_button->setCheckable(true);


    QObject::connect(m_arousalUi.slider, &QSlider::sliderReleased, [this]() { m_wasArousalPressed = true; });
    QObject::connect(m_arousalUi.slider, &QSlider::valueChanged, [this](int value) { m_wasArousalPressed = true; });

    QObject::connect(m_positivityUi.slider, &QSlider::sliderReleased, [this]() { m_wasPositivityPressed = true; });
    QObject::connect(m_positivityUi.slider, &QSlider::valueChanged, [this](int value) { m_wasPositivityPressed = true; });

    // Connect button signal to appropriate slot
     //connect(m_button, SIGNAL (clicked()), m_widget, SLOT (activateButton());



    //add a spacer to push everything up
    m_widget->layout()->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

StateData& AssesmentState::getData()
{
    return *m_data;
}

void AssesmentState::process()
{
    if (m_wasArousalPressed == true && m_wasPositivityPressed == true)
    {
        m_button->setEnabled(true);
        m_button->setText("Save and Continue");
    }
}

std::unique_ptr<State> AssesmentState::finish()
{
    if (m_button->isChecked())
    {
        auto& stateData = getData();
        stateData.positivity = m_positivityUi.slider->value();
        stateData.arousal = m_arousalUi.slider->value();

        return std::unique_ptr<State>(new IdleState(m_data));
    }
    else
    {
        return nullptr;
    }
}
