#ifndef MATCHING_H
#define MATCHING_H

#include <QWidget>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include "heap.h"

using namespace std;
using namespace cv;

#define NO_OF_GESTURES 50

/**
 * MatchGesture Class.
 * This class receives current frames and uses the HAAR cascade trained xmls to
 * match gesture. The matched gesture is converted to a character and then sent
 * to the main window module for speaking and display. It is inherited publicly
 * from QWidget so that it can be linked with other Qt modules using Signals and
 * Slots.
 */
class MatchGesture : public QWidget
{
    Q_OBJECT
private:
    /**
     * A private function.
     * This function takes the image matrix as input and tries to match the gesture.
     * If it gets the recognized gesture, it draws a circle around it.
     * @param img a Mat reference to the image to take current input frame.
     * @param cascade a CascadeClassifier reference which uses the Haar to match gesture.
     * @param nestedCascade a CascadeClassifier reference which used to match sub category.
     * @param scale a double type which specifies the matching radius.
     */
    void detectAndDraw( Mat& img,
                       CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
                       double scale);

    /**
     * A private vector of strings.
     * Stores filenames of trained Haar Cascade XML files for all gestures.
     */
    vector<string> allCascadeNames;

    /**
     * A private integer type array.
     * This array contains the number of occurences of the matched characters per session.
     */
    int charactersOccurences[NO_OF_GESTURES];

    /**
     * A private integer type variable.
     * This integer denotes the maximum occurences of a character.
     */
    int maxTillNow;

    /**
     * A private integer type variable.
     * This intger denotes the index of the maximum occurred character.
     */
    int maxIndexTillNow;

    /**
     * A private character type variable.
     * This character stores the maximum occurred character in particular interval.
     */
    char matchedCharacter;

    /**
     * A private string variable.
     * This variable stores the current cascade filename.
     */
    string cascadeName;

    /**
     * A private string variable.
     * This variable stores the current nested cascade filename.
     */
    string nestedCascadeName;

    /**
     * A private Mat variable.
     * This variable stores the current frame to match.
     */
    Mat frame;

    /**
     * A private Mat variable.
     * This variable stores the copy of current frame to match.
     */
    Mat frameCopy;

    /**
     * A private Mat variable.
     * This variable stores the matched image.
     */
    Mat image;

    /**
     * A private CascadeClassifier variable.
     * This cascade classifier stores the HAAR settings for matching.
     */
    CascadeClassifier cascade;

    /**
     * A private CascadeClassifier variable.
     * This cascade classifier stores the nested HAAR settings for matching.
     */
    CascadeClassifier nestedCascade;

    /**
     * A private double variable.
     * This double variable stores the scale radius for matching.
     */
    double scale;


public:
    /**
     * A constructor.
     * This Matching constructor takes the argument as parent window of type QWidget
     * and generates. It initializes the cascade classifiers.
     */
    MatchGesture(QWidget *parent=0);

    /**
     * A Destructor.
     */
    ~MatchGesture();

    /**
     * A public function.
     * This function is called from the other module when a matching has to be done.
     * @param iplImage an IplImage type to recieve the image to match.
     */
    IplImage* getMatch(IplImage *iplImage);

    /**
     * A public function.
     * This function is called when a probable matched character is required from this
     * module in a particular time interval.
     */
    void getProbableCharacter();

signals:
    /**
     * A Qt Signal.
     * This signal is emitted whenever a character is matched.
     */
    void sendForDisplay(char c);


};

#endif // MATCHING_H
