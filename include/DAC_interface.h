#ifndef DAC_INTERFACE_H
#define DAC_INTERFACE_H

/* read audio array */
void DAC_voidReadAudioArrSync(const u8 *audio_array, u16 ArraySize);
void DAC_voidReadAudioArrAsync(u8 *audio_array, u16 ArraySize);
/* increase frequency(speed) of the sound  */
void  DAC_voidIncreaseFreq(void);
/* decrese frequency(speed) of the sound  */
void  DAC_voidDecreaseFreq(void);

void DAC_delay(void);






#endif
