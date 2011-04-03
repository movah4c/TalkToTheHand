#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QtGui>

/**
 * Settings Class
 * This class is used to change the settings in which the system operates and
 * matching module radius to increase matching efficiency.
 */
class Settings : public QWidget
{
    Q_OBJECT
public:
    /**
     * A public QLabel.
     * The is scale label on the settings window.
     */
    QLabel *scaleLabel;

    /**
     * A public QLabel.
     * The is update interval label on the settings window.
     */
    QLabel *updateIntervalLabel;

    /**
     * A public QLabel.
     * The is scale label on the settings window.
     */
    QDoubleSpinBox *scaleSpinBox;

    /**
     * A public QDoubleSpinBox.
     * The is update interval spin box on the settings window.
     */
    QDoubleSpinBox *updateIntervalSpinBox;

    /**
     * A public QPushButton.
     * The is push button to apply settings on the settings window.
     */
    QPushButton *applyButton;

    /**
     * A public QPushButton.
     * The is cancel push button on the settings window.
     */
    QPushButton *cancelButton;


    Settings(QWidget *parent=0);
    ~Settings();

};


#endif // SETTINGS_H
