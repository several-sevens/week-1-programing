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
} waveformsample;

waveformsample* load_csv(void);

void write_results(const char* filename,
                   double rms_a, double rms_b, double rms_c,
                   double dc_a, double dc_b, double dc_c,
                   double ptp_a, double ptp_b, double ptp_c);

#endif