
#ifndef waveform_h
#define waveform_h
#include "io.h"
double compute_phase_A_rms(waveformsample* data, int num_samples);
double compute_phase_B_rms(waveformsample* data, int num_samples);
double compute_phase_C_rms(waveformsample* data, int num_samples);

double compute_phase_A_dc(waveformsample* data, int num_samples);
double compute_phase_B_dc(waveformsample* data, int num_samples);
double compute_phase_C_dc(waveformsample* data, int num_samples);

double compute_phase_A_ptp(waveformsample* data, int num_samples);
double compute_phase_B_ptp(waveformsample* data, int num_samples);
double compute_phase_C_ptp(waveformsample* data, int num_samples);

void check_compliance(double rms_a, double rms_b, double rms_c);

void clipping(waveformsample* data, int num_samples);

#endif