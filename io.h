#ifndef io_h
#define io_h

typedef struct {
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
} csvread;
double compute_phase_A_rms(csvread* data, int num_samples);
double compute_phase_B_rms(csvread* data, int num_samples);
double compute_phase_C_rms(csvread* data, int num_samples);
#endif