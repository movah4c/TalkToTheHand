#ifndef AUDIO_H
#define AUDIO_H

#include <QtGui>
#include <QVector>
#include <QString>
#include <QWidget>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>

/**
 * Play Audio class.
 * This class is the one which connects the hardware audio device to
 * the application and helps the user to control the audio volume and
 * the application to send the audio stream to the audio device.
 * This class is inherited publicly from the QObject so that it can be
 * easily connected to the other Qt Widgets with the use of signals and
 * slots.
 */
class PlayAudio : public QObject
{
    Q_OBJECT
public:
     /**
      * Constructor of Play Audio class.
      * This constructor initializes the media objects from the phonon
      * package to interact with the audio device. It also sets the tick
      * interval for the audio device. Then it connects different signals
      * and slots so that it can interact effectively with the main window.
      * @param parent a pointer to QWidget class which acts as parent to this widget
      */
      PlayAudio(QWidget *parent);

      /**
       * Destructor of the Play Audio class.
       * Deletes all the pointers which were initialized in the constructors.
       */
      ~PlayAudio();

      /**
       * A public function taking QString as argument.
       * This function is called from the main window and the audio file
       * which is to be played or spoken is passed to this filename. The
       * internal play list acts as a queue and adds all these requests
       * to be played.
       * @param filename an object to QString which stores file name to be played
       */
      void addToPlayList(QString filename);

      /**
       * A public function.
       * This is a public function which is called when the volume has
       * to be changed.
       * @param volume an integer type denoting the present volume
       */
      void changeVolume(int volume);

private slots:
      /**
       * A private slot.
       * This private slot is connected to the tick time so that it checks
       * or updates every second for the audio list being played and other
       * tasks such as audio is going to end or not.
       * @param time a qint64 type variable denoting update time
       */
      void tick(qint64 time);

      /**
       * A private slot.
       * This slot is called when the member being played now is about to
       * be completed and a shuffle has to be made in the playlist queue.
       */
      void aboutToFinish();

private:
      /**
       * A private pointer to Phonon::SeekSlider
       * Phonon seek slider is used to get a slider for updating volume
       * information internally as changed by the user.
       */
      Phonon::SeekSlider *seekSlider;

      /**
       * A private pointer to Phonon::MediaObject
       * This phonon media object contains all the play list and audio
       * which is being played or is about to be played.
       */
      Phonon::MediaObject *mediaObject;

      /**
       * A private pointer to Phonon::AudioOutput
       * This is the pointer to the class which manages all the audio
       * ouput modes, volumes, etc.
       */
      Phonon::AudioOutput *audioOutput;

      /**
       * A private pointer to Phonon::VolumeSlider
       * This is the pointer to the Volume Slider which actually takes
       * input from the user and gives it to the inner modules.
       */
      Phonon::VolumeSlider *volumeSlider;

      /**
       * A private vector of Phonon::MediaSources
       * This vector act as a queue for the media objects being played
       * and which are going to be played. If any audio is still being
       * played and other comes in, it is kept in this queue.
       */
      QVector<Phonon::MediaSource> sources;
};

#endif // AUDIO_H
