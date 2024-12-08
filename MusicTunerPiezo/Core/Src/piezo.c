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

