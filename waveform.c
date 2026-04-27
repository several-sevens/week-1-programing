#include "waveform.h"
#include "io.h"
#include <math.h>
#include <stdio.h>

// rms calc _____________________________________________________________________________
double compute_phase_A_rms(waveformsample* data, int num_samples) {
    double sum_of_squares = 0.0;

    for (int i = 0; i < num_samples; i++) {
        sum_of_squares += (data[i].phase_A_voltage * data[i].phase_A_voltage);
    }

    double mean = sum_of_squares / num_samples;
    return sqrt(mean);
}
double compute_phase_B_rms(waveformsample* data, int num_samples) {
    double sum_of_squares1 = 0.0;

    for (int i = 0; i < num_samples; i++) {
        sum_of_squares1 += (data[i].phase_B_voltage * data[i].phase_B_voltage);
    }

    double mean = sum_of_squares1 / num_samples;
    return sqrt(mean);
}
double compute_phase_C_rms(waveformsample* data, int num_samples) {
    double sum_of_squares2 = 0.0;

    for (int i = 0; i < num_samples; i++) {
        sum_of_squares2 += (data[i].phase_C_voltage * data[i].phase_C_voltage);
    }

    double mean = sum_of_squares2 / num_samples;
    return sqrt(mean);
}

// dc calc ________________________________________________________________________________________________
double compute_phase_A_dc(waveformsample* data, int num_samples) {
    double sum = 0.0;
    for (int i = 0; i < num_samples; i++) {
        sum += data[i].phase_A_voltage;
    }
    return sum / num_samples;
}

double compute_phase_B_dc(waveformsample* data, int num_samples) {
    double sum = 0.0;
    for (int i = 0; i < num_samples; i++) {
        sum += data[i].phase_B_voltage;
    }
    return sum / num_samples;
}

double compute_phase_C_dc(waveformsample* data, int num_samples) {
    double sum = 0.0;
    for (int i = 0; i < num_samples; i++) {
        sum += data[i].phase_C_voltage;
    }
    return sum / num_samples;
}
//ptp calc ___________________________________________________________________________________________________
double compute_phase_A_ptp(waveformsample* data, int num_samples) {
    double max = data[0].phase_A_voltage;
    double min = data[0].phase_A_voltage;

    for (int i = 1; i < num_samples; i++) {
        if (data[i].phase_A_voltage > max) {
            max = data[i].phase_A_voltage;
        }
        if (data[i].phase_A_voltage < min) {
            min = data[i].phase_A_voltage;
        }
    }
    return max-min;
}
double compute_phase_B_ptp(waveformsample* data, int num_samples) {
    double max = data[0].phase_B_voltage;
    double min = data[0].phase_B_voltage;
    for (int i = 1; i < num_samples; i++) {
        if (data[i].phase_B_voltage > max) {
            max = data[i].phase_B_voltage;
        }
        if (data[i].phase_B_voltage < min) {
            min = data[i].phase_B_voltage;
        }
    }
    return max-min;
}
double compute_phase_C_ptp(waveformsample* data, int num_samples) {
    double max = data[0].phase_C_voltage;
    double min = data[0].phase_C_voltage;
    for (int i = 1; i < num_samples; i++) {
        if (data[i].phase_C_voltage > max) {
            max = data[i].phase_C_voltage;
        }
        if (data[i].phase_C_voltage < min) {
            min = data[i].phase_C_voltage;
        }
    }
    return max-min;
}

//clipping ___________________________________________________________________________________________
void clipping(waveformsample* data, int num_samples) {
    int clipped_samples = 0;

    printf(" clipping analisis \n");

    printf("      phase A      voltage B      voltage C  \n");

    for (int i = 0; i < num_samples; i++) {
        if (fabs(data[i].phase_A_voltage) >= 324.9) {
            printf(" %11.2f %11s %11s \n", data[i].phase_A_voltage, "-", "-");
            clipped_samples++;
        }
        if (fabs(data[i].phase_B_voltage) >= 324.9) {
            printf(" %11s %12.2f %10s \n", "-", data[i].phase_B_voltage, "-");
            clipped_samples++;
        }
        if (fabs(data[i].phase_C_voltage) >= 324.9) {
            printf(" %11s %11s %16.2f \n", "-", "-", data[i].phase_C_voltage);
            clipped_samples++;
        }
    }
}
// tolerance check _______________________________________________________________________________________
void check_compliance(double rms_a, double rms_b, double rms_c) {
    double nominal = 230.0;
    double lower = nominal * 0.90;  // 207
    double upper = nominal * 1.10;  // 253

    printf("\n Tolerance Check (230V ±10%%)\n");

    printf("Phase A RMS: %.2f V -> %s\n", rms_a,
           (rms_a >= lower && rms_a <= upper) ? "PASS" : "FAIL");

    printf("Phase B RMS: %.2f V -> %s\n", rms_b,
           (rms_b >= lower && rms_b <= upper) ? "PASS" : "FAIL");

    printf("Phase C RMS: %.2f V -> %s\n", rms_c,
           (rms_c >= lower && rms_c <= upper) ? "PASS" : "FAIL");

}