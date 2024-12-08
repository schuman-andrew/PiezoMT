/*********************************************************
 * @file 			: piezo.h
 * @project         : Music Tuner Project
 * @brief           : Piezo Output - notes, chords, volume
 * 		- PINS: PB4(TIM3_CH1), PA15(TIM2_CH1), PH6(TIM12_CH1), PI0 (TIM5_CH4)
 * 		Board PINS: D3, D9, D6, D5
 * @author          : Andrew Schuman & Kamila Errigo
 * @class           : CPE3600-111
 * @date            : 24 November 2024
 *********************************************************
 */

#ifndef INC_PIEZO_H_
#define INC_PIEZO_H_

#include <stdbool.h>

//frequency to all timers used
#define TIMER_SPEED 500000

/**
 @brief sets all timer volume to 15 and stops all timers
 */
void initPiezo();

/**
 @brief stops all timers
 */
void stopAll();

/**
 @brief outputs note to timer 3, outputs on piezo
 @param note -> note to be played on piezo
 */
void playNote(char * note);

/**
 @brief outputs note to timer 2, outputs on piezo
 @param note -> note to be played on piezo
 */
void playNoteTIM2(char * note, bool on);

/**
 @brief outputs note to timer 3, outputs on piezo
 @param note -> note to be played on piezo
 */
void playNoteTIM3(char * note, bool on);

/**
 @brief outputs note to timer 5, outputs on piezo
 @param note -> note to be played on piezo
 */
void playNoteTIM5(char * note, bool on);

/**
 @brief outputs note to timer 12, outputs on piezo
 @param note -> note to be played on piezo
 */
void playNoteTIM12(char * note, bool on);

/**
 @brief increases volume on all piezos by 10%
 */
void volumeUp();

/**
 @brief decreases volume on all piezos by 10%
 */
void volumeDown();

#endif /* INC_PIEZO_H_ */
