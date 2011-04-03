#include "include/settings.h"

Settings::Settings(QWidget *parent) : QWidget(parent)
{
    updateIntervalLabel = new QLabel(tr("Update Interval "));
    scaleLabel = new QLabel(tr("Scale Radius "));
    updateIntervalSpinBox = new QDoubleSpinBox;
    scaleSpinBox = new QDoubleSpinBox;
    applyButton = new QPushButton(tr("Apply"), this);
    cancelButton = new QPushButton(tr("Cancel"), this);

    scaleSpinBox->setValue(3.0);
    updateIntervalSpinBox->setValue(3.0);

    QHBoxLayout *tempLayout1 = new QHBoxLayout;
    QHBoxLayout *tempLayout2 = new QHBoxLayout;
    QHBoxLayout *tempLayout4 = new QHBoxLayout;
    QVBoxLayout *tempLayout3 = new QVBoxLayout;

    tempLayout1->addWidget(scaleLabel);
    tempLayout1->addWidget(scaleSpinBox);

    tempLayout2->addWidget(updateIntervalLabel);
    tempLayout2->addWidget(updateIntervalSpinBox);

    tempLayout4->addWidget(applyButton);
    tempLayout4->addWidget(cancelButton);

    tempLayout3->addLayout(tempLayout1);
    tempLayout3->addLayout(tempLayout2);
    tempLayout3->addLayout(tempLayout4);


    setLayout(tempLayout3);
    setFixedSize(300, 200);

    setWindowTitle(tr("Application Settings"));


}

Settings::~Settings()
{

}

