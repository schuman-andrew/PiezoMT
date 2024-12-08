/*********************************************************
 * @file 			: picthmap.h
 * @project         : Music Tuner Project
 * @brief           : Pitch Mapping Program (INCREMENT HZ)
 * @author          : Julian Carvalho & Andrew Schuman
 * @class           : CPE3600-111
 * @date            : 24 November 2024
 *********************************************************
 */

#ifndef INC_PITCHMAP_H_
#define INC_PITCHMAP_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_FREQUENCY 28000
#define CHAR_NOTE_LENGTH 4
#define CENTS_SCALAR 1200
#define PERCENT_SCALAR 100
#define FIFTY_MICROSECONDS 500000
#define A4_INDEX 48  // Index of A4 in the note array

/**
 * Struct containing note name and frequency
 */
typedef struct {
	char note[CHAR_NOTE_LENGTH];
	double frequency;
} FrequencyNote;

/**
 * getFreq
 *  - Returns frequency of corresponding note from noteFrequencies[]
 */
double getFreq(char * note);

/**
 * Initializes note frequencies based on the global concert pitch.
 */
void initializeNoteFrequencies();

/**
 @brief Maps the frequency inputted to the closest note's FrequencyNote.frequency
 @param inputFrequency -> The input frequency to the function from main
 @return FrequencyNote -> The Note in the array that is closest to the
 input frequency to this function
 */
FrequencyNote mapFrequencyToClosest(double inputFrequency);

/**
 * @brief Calculates the Cents deviation from the reference
 */
double calculateCents(double f_actual, double f_reference);

/**
 * @brief Calculates the percentage error of the actual frequency
 */
double calculatePercentageError(double f_experimental, double f_actual);

#endif /* INC_PITCHMAP_H_ */
