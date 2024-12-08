/*********************************************************
 * @file 			: picthmap.c
 * @project         : Music Tuner Project
 * @brief           : Pitch Mapping Program (INCREMENT HZ)
 * @author          : Julian Carvalho & Andrew Schuman
 * @class           : CPE3600-111
 * @date            : 24 November 2024
 *********************************************************
 */

#include "main.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include "pitchmap.h"

int numNotes = 88;

/*
 Global variable representing concert pitch (default is A4 at 440 Hz).
 This can be modified dynamically to change the reference pitch.
 */
double concert_pitch = 440.00;

/**
 * Array of note names for easy indexing.
 */
const char *noteNames[] = { "A0 ", "A#0", "B0 ", "C1 ", "C#1", "D1 ", "D#1",
		"E1 ", "F1 ", "F#1", "G1 ", "G#1", "A1 ", "A#1", "B1 ", "C2 ", "C#2",
		"D2 ", "D#2", "E2 ", "F2 ", "F#2", "G2 ", "G#2", "A2 ", "A#2", "B2 ",
		"C3 ", "C#3", "D3 ", "D#3", "E3 ", "F3 ", "F#3", "G3 ", "G#3", "A3 ",
		"A#3", "B3 ", "C4 ", "C#4", "D4 ", "D#4", "E4 ", "F4 ", "F#4", "G4 ",
		"G#4", "A4 ", "A#4", "B4 ", "C5 ", "C#5", "D5 ", "D#5", "E5 ", "F5 ",
		"F#5", "G5 ", "G#5", "A5 ", "A#5", "B5 ", "C6 ", "C#6", "D6 ", "D#6",
		"E6 ", "F6 ", "F#6", "G6 ", "G#6", "A6 ", "A#6", "B6 ", "C7 ", "C#7",
		"D7 ", "D#7", "E7 ", "F7 ", "F#7", "G7 ", "G#7", "A7 ", "A#7", "B7 ",
		"C8 " };

/**
 * Initializes note frequencies based on the global concert pitch.
 */
FrequencyNote noteFrequencies[88];

/**
 * getFreq
 *  - Returns frequency of corresponding note from noteFrequencies[]
 */
double getFreq(char *note) {
	numNotes = sizeof(noteFrequencies) / sizeof(noteFrequencies[0]);
	int freqNum = 0;
	double freq;
	//printf("Array Size(getFreq) - %d\n", numNotes);

	for (int x = 0; x < numNotes; x++) {
		if (strcmp(noteFrequencies[x].note, note) == 0) {
			freqNum = x;
		}
	}

	freq = noteFrequencies[freqNum].frequency;
	//printf("Freq - %f, %s\n", freq, noteFrequencies[freqNum].note);
	//printf("Freq - %d, %s\n", (int)freq, noteFrequencies[freqNum].note);

	return freq;
}

/**
 * Initializes note frequencies based on the global concert pitch.
 */
void initializeNoteFrequencies() {
	for (int i = 0; i < 88; i++) {
		double semitoneOffset = i - A4_INDEX;
		noteFrequencies[i].frequency = concert_pitch
				* pow(2, semitoneOffset / 12.0);
		sprintf(noteFrequencies[i].note, "%s", noteNames[i]);
		//printf("%s, %f\n", noteFrequencies[i].note, noteFrequencies[i].frequency);
	}
}

/**
 @brief Maps the frequency inputted to the closest note's FrequencyNote.frequency
 @param inputFrequency -> The input frequency to the function from main
 @return FrequencyNote -> The Note in the array that is closest to the
 input frequency to this function
 */
FrequencyNote mapFrequencyToClosest(double inputFrequency) {
	numNotes = sizeof(noteFrequencies) / sizeof(noteFrequencies[0]);
	FrequencyNote closestNote = noteFrequencies[0];
	double minDifference = fabs(inputFrequency - closestNote.frequency);

	for (int i = 1; i < numNotes; i++) {
		double difference = fabs(inputFrequency - noteFrequencies[i].frequency);
		if (difference < minDifference) {
			closestNote = noteFrequencies[i];
			minDifference = difference;
		}
	}

	return closestNote;
}

/**
 * @brief Calculates the Cents deviation from the reference
 */
double calculateCents(double f_actual, double f_reference) {
	return CENTS_SCALAR * log2(f_actual / f_reference);
}

/**
 * @brief Calculates the percentage error of the actual frequency
 */
double calculatePercentageError(double f_experimental, double f_actual) {
	return fabs((f_experimental - f_actual) / f_actual) * PERCENT_SCALAR;
}
