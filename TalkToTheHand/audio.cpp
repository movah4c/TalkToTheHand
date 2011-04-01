#include "audio.h"
#include <iostream>

/** Constructor */
PlayAudio::PlayAudio(QWidget *parent=0)
{
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, parent);
    mediaObject = new Phonon::MediaObject(parent);


    mediaObject->setTickInterval(1000);

    /** Connecting media object to different slots */
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));

    /** Connecting media object and audioOutput */
    Phonon::createPath(mediaObject, audioOutput);

}

/** Destructor */
PlayAudio::~PlayAudio()
{
    /** deleting all pointers allocated in this class */
    delete seekSlider;
    delete mediaObject;
    delete audioOutput;
    delete volumeSlider;
}

/** Add media to the play list */
void PlayAudio::addToPlayList(QString filename)
{

    Phonon::MediaSource source(filename);
    sources.push_back(source);
    /** Checking for empty conditions*/
    if(mediaObject->queue().size()==0)
    {
        mediaObject->enqueue(sources.front());
        mediaObject->play();
    }
}

void PlayAudio::tick(qint64 time)
{
    /** This portion is executed every second when the audio is being played */

}

/** Things to be done when audio is about to finish */
void PlayAudio::aboutToFinish()
{

    sources.pop_front();
    if(sources.size()!=0)
        mediaObject->enqueue(sources[0]);

}

/** Change output volume */
void PlayAudio::changeVolume(int volume)
{
    audioOutput->setVolume((qreal)volume);
}
