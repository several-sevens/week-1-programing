
#ifndef waveform_h
#define waveform_h
#include "io.h"
double compute_phase_A_rms(csvread* data, int num_samples);
double compute_phase_B_rms(csvread* data, int num_samples);
double compute_phase_C_rms(csvread* data, int num_samples);

double compute_phase_A_dc(csvread* data, int num_samples);
double compute_phase_B_dc(csvread* data, int num_samples);
double compute_phase_C_dc(csvread* data, int num_samples);

double compute_phase_A_ptp(csvread* data, int num_samples);
double compute_phase_B_ptp(csvread* data, int num_samples);
double compute_phase_C_ptp(csvread* data, int num_samples);

void clipping(csvread* data, int num_samples);

#endif