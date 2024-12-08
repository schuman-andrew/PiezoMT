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

#include "main.h"
#include "piezo.h"
#include "tim.h"
#include "gpio.h"
#include "string.h"
#include <stdbool.h>

static int volume = 10;
static int volChange = 5;

//timers 2, 3, 5, 12 in order
char* global_piezos[4] = {"OFF", "OFF", "OFF", "OFF"};

/**
 @brief sets all timer volume to 15 and stops all timers
 */
void initPiezo(){
	volumeUp();
	stopAll();
}

/**
 @brief stops all timers
 */
void stopAll(){
	HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_4);
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

/**
 @brief calculates output frequency
 @param freq -> output frequency for timer
 @return output frequency for timer
 */
int calcReload(double freq){
	return (TIMER_SPEED/freq);
}

/**
 @brief outputs note to timer 2, outputs on piezo
 @param note -> note to be played on piezo
 */
void playNoteTIM2(char * note, bool on){
	if(on == true){
		//pitch map to get freq
		int freq = getFreq(note);
		int reload = calcReload(freq);
		//printf("!!!play note - %d\n", freq);

		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);

		__HAL_TIM_SET_AUTORELOAD(&htim2, reload);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	} else if (on == false){
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	}
}

/**
 @brief outputs note to timer 3, outputs on piezo
 @param note -> note to be played on piezo
 */
void playNoteTIM3(char * note, bool on){
	if(on == true){
		//pitch map to get freq
		int freq = getFreq(note);
		int reload = calcReload(freq);
		//printf("!!!play note - %d\n", freq);

		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);

		__HAL_TIM_SET_AUTORELOAD(&htim3, reload);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	} else if (on == false){
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	}
}

/**
 @brief outputs note to timer 5, outputs on piezo
 @param note -> note to be played on piezo
 */
void playNoteTIM5(char * note, bool on){
	if(on == true){
		//pitch map to get freq
		int freq = getFreq(note);
		int reload = calcReload(freq);
		//printf("!!!play note - %d\n", freq);

		HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_4);

		__HAL_TIM_SET_AUTORELOAD(&htim5, reload);
		HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
	} else if (on == false){
		HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_4);
	}
}

/**
 @brief outputs note to timer 12, outputs on piezo
 @param note -> note to be played on piezo
 */
void playNoteTIM12(char * note, bool on){
	if(on == true){
		//pitch map to get freq
		int freq = getFreq(note);
		int reload = calcReload(freq);
		//printf("!!!play note - %d\n", freq);

		HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_1);

		__HAL_TIM_SET_AUTORELOAD(&htim12, reload);
		HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	} else if (on == false){
		HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_1);
	}
}

/**
 @brief increases volume on all piezos by 10%
 */
void volumeUp(){

	if(volume <= 45){
		volume += volChange;

		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1, (volume));
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, (volume));
		__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4, (volume));
		__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1, (volume));
	}
	//printf("Vol up - %d\n", volume);
}

/**
 @brief decreases volume on all piezos by 10%
 */
void volumeDown(){

	if(volume >= 5){
		volume -= volChange;

		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1, (volume));
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, (volume));
		__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4, (volume));
		__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1, (volume));
	}
	//printf("Vol down - %d\n", volume);
}

/**
 @brief selects an available piezo to play the note on and plays the note
 @param note -> note to be played on piezo
 @return 0 if a piezo was available and is playing the note
         1 if all piezos were already in use and the note is not playing
 */
uint8_t piezoSelectOn(char * note) {
	char* piezo_note;
	for(uint8_t i = 0; i < 4; i++) {
		piezo_note = global_piezos[i];
		if(strcmp(piezo_note, "OFF") == 0) {
			if(i == 0) {
				playNoteTIM2(note, true);
			} else if (i == 1) {
				playNoteTIM3(note, true);
			} else if (i == 2) {
				playNoteTIM5(note, true);
			} else {
				playNoteTIM12(note, true);
			}
			global_piezos[i] = note;
			return 0;
		}
	}
	return 1;
}

/**
 @brief finds which piezo is playing the note and turns it off
 @param note -> note to be turned off
 @return 0 if a piezo playing the note was found and turned off
         1 if a piezo playing the note was not found and nothing was turned off
 */
uint8_t piezoSelectOff(char * note) {
	char* piezo_note;
	for(uint8_t i = 0; i < 4; i++) {
		piezo_note = global_piezos[i];
		if(strcmp(piezo_note, note) == 0) {
			if(i == 0) {
				playNoteTIM2(note, false);
			} else if (i == 1) {
				playNoteTIM3(note, false);
			} else if (i == 2) {
				playNoteTIM5(note, false);
			} else {
				playNoteTIM12(note, false);
			}
			global_piezos[i] = "OFF";
			return 0;
		}
	}
	return 1;
}
