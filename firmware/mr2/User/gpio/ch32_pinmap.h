#ifndef __CH32_PINMAP_H
#define __CH32_PINMAP_H

// ===========================================================
//   ????????????? ????? ????? ??? CH32 (V003, X035, V203)
// ===========================================================
//
// ?????:
//   - #define ADC_CHANNEL_PAx   <????? ??????>   (???? ???? ADC)
//   - #define PWM_PIN_PAx       TIMx,ch          (???? ???????????? PWM)
//   - #define HAS_ADC_PAx       1 / 0
//   - #define HAS_PWM_PAx       1 / 0
//
// ?????????????: analogRead(PAx), analogWrite(PBx, val)
// ===========================================================


// ===========================================================
// CH32V003 (?????????, ?? 20 ???)
// ===========================================================
#if defined(CH32V003)

// --- ADC ---
#define ADC_CHANNEL_PA1   1
#define ADC_CHANNEL_PA2   2
#define ADC_CHANNEL_PA3   3
#define ADC_CHANNEL_PA4   4
#define ADC_CHANNEL_PA5   5
#define ADC_CHANNEL_PA6   6
#define ADC_CHANNEL_PA7   7

#define HAS_ADC_PA1 1
#define HAS_ADC_PA2 1
#define HAS_ADC_PA3 1
#define HAS_ADC_PA4 1
#define HAS_ADC_PA5 1
#define HAS_ADC_PA6 1
#define HAS_ADC_PA7 1

// --- PWM (TIM1) ---
#define PWM_PIN_PA2  TIM1,1
#define PWM_PIN_PA3  TIM1,2
#define PWM_PIN_PA4  TIM1,3
#define PWM_PIN_PA7  TIM1,4

#define HAS_PWM_PA2 1
#define HAS_PWM_PA3 1
#define HAS_PWM_PA4 1
#define HAS_PWM_PA7 1


// ===========================================================
// CH32X035 (???????, ?? 48 ???, ?????? STM32F030/F051)
// ===========================================================
#elif defined(CH32X035)

// --- ADC ---
#define ADC_CHANNEL_PA0   0
#define ADC_CHANNEL_PA1   1
#define ADC_CHANNEL_PA2   2
#define ADC_CHANNEL_PA3   3
#define ADC_CHANNEL_PA4   4
#define ADC_CHANNEL_PA5   5
#define ADC_CHANNEL_PA6   6
#define ADC_CHANNEL_PA7   7
#define ADC_CHANNEL_PB0   8
#define ADC_CHANNEL_PB1   9

#define HAS_ADC_PA0 1
#define HAS_ADC_PA1 1
#define HAS_ADC_PA2 1
#define HAS_ADC_PA3 1
#define HAS_ADC_PA4 1
#define HAS_ADC_PA5 1
#define HAS_ADC_PA6 1
#define HAS_ADC_PA7 1
#define HAS_ADC_PB0 1
#define HAS_ADC_PB1 1

// --- PWM (TIM1, TIM3, TIM14/15/16) ---
#define PWM_PIN_PA8  TIM1,1
#define PWM_PIN_PA9  TIM1,2
#define PWM_PIN_PA10 TIM1,3
#define PWM_PIN_PA11 TIM1,4

#define PWM_PIN_PA6  TIM3,1
#define PWM_PIN_PA7  TIM3,2
#define PWM_PIN_PB0  TIM3,3
#define PWM_PIN_PB1  TIM3,4

#define PWM_PIN_PA4  TIM14,1
#define PWM_PIN_PA2  TIM15,1
#define PWM_PIN_PA3  TIM15,2
#define PWM_PIN_PA6  TIM16,1

#define HAS_PWM_PA8  1
#define HAS_PWM_PA9  1
#define HAS_PWM_PA10 1
#define HAS_PWM_PA11 1
#define HAS_PWM_PA6  1
#define HAS_PWM_PA7  1
#define HAS_PWM_PB0  1
#define HAS_PWM_PB1  1
#define HAS_PWM_PA4  1
#define HAS_PWM_PA2  1
#define HAS_PWM_PA3  1


// ===========================================================
// CH32V203 (STM32F103-???????????, ?? 64 ???)
// ===========================================================
#elif defined(CH32V203)

// --- ADC ---
#define ADC_CHANNEL_PA0   0
#define ADC_CHANNEL_PA1   1
#define ADC_CHANNEL_PA2   2
#define ADC_CHANNEL_PA3   3
#define ADC_CHANNEL_PA4   4
#define ADC_CHANNEL_PA5   5
#define ADC_CHANNEL_PA6   6
#define ADC_CHANNEL_PA7   7
#define ADC_CHANNEL_PB0   8
#define ADC_CHANNEL_PB1   9
#define ADC_CHANNEL_PC0  10
#define ADC_CHANNEL_PC1  11
#define ADC_CHANNEL_PC2  12
#define ADC_CHANNEL_PC3  13
#define ADC_CHANNEL_PC4  14
#define ADC_CHANNEL_PC5  15

#define HAS_ADC_PA0 1
#define HAS_ADC_PA1 1
#define HAS_ADC_PA2 1
#define HAS_ADC_PA3 1
#define HAS_ADC_PA4 1
#define HAS_ADC_PA5 1
#define HAS_ADC_PA6 1
#define HAS_ADC_PA7 1
#define HAS_ADC_PB0 1
#define HAS_ADC_PB1 1
#define HAS_ADC_PC0 1
#define HAS_ADC_PC1 1
#define HAS_ADC_PC2 1
#define HAS_ADC_PC3 1
#define HAS_ADC_PC4 1
#define HAS_ADC_PC5 1

// --- PWM (TIM2, TIM3, TIM4) ---
#define PWM_PIN_PA0  TIM2,1
#define PWM_PIN_PA1  TIM2,2
#define PWM_PIN_PA2  TIM2,3
#define PWM_PIN_PA3  TIM2,4

#define PWM_PIN_PA6  TIM3,1
#define PWM_PIN_PA7  TIM3,2
#define PWM_PIN_PB0  TIM3,3
#define PWM_PIN_PB1  TIM3,4

#define PWM_PIN_PB6  TIM4,1
#define PWM_PIN_PB7  TIM4,2
#define PWM_PIN_PB8  TIM4,3
#define PWM_PIN_PB9  TIM4,4

#define HAS_PWM_PA0 1
#define HAS_PWM_PA1 1
#define HAS_PWM_PA2 1
#define HAS_PWM_PA3 1
#define HAS_PWM_PA6 1
#define HAS_PWM_PA7 1
#define HAS_PWM_PB0 1
#define HAS_PWM_PB1 1
#define HAS_PWM_PB6 1
#define HAS_PWM_PB7 1
#define HAS_PWM_PB8 1
#define HAS_PWM_PB9 1

#endif // family selector

#endif // __CH32_PINMAP_H