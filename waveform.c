#include "waveform.h"
#include "io.h"
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

// rms calc _____________________________________________________________________________
double compute_phase_A_rms(csvread* data, int num_samples) {
    double sum_of_squares = 0.0;

    for (int i = 0; i < num_samples; i++) {
        sum_of_squares += (data[i].phase_A_voltage * data[i].phase_A_voltage);
    }

    double mean = sum_of_squares / num_samples;
    return sqrt(mean);
}
double compute_phase_B_rms(csvread* data, int num_samples) {
    double sum_of_squares1 = 0.0;

    for (int i = 0; i < num_samples; i++) {
        sum_of_squares1 += (data[i].phase_B_voltage * data[i].phase_B_voltage);
    }

    double mean = sum_of_squares1 / num_samples;
    return sqrt(mean);
}
double compute_phase_C_rms(csvread* data, int num_samples) {
    double sum_of_squares2 = 0.0;

    for (int i = 0; i < num_samples; i++) {
        sum_of_squares2 += (data[i].phase_C_voltage * data[i].phase_C_voltage);
    }

    double mean = sum_of_squares2 / num_samples;
    return sqrt(mean);
}

// dc calc ________________________________________________________________________________________________
double compute_phase_A_dc(csvread* data, int num_samples) {
    double sum = 0.0;
    for (int i = 0; i < num_samples; i++) {
        sum += data[i].phase_A_voltage;
    }
    return sum / num_samples;
}

double compute_phase_B_dc(csvread* data, int num_samples) {
    double sum = 0.0;
    for (int i = 0; i < num_samples; i++) {
        sum += data[i].phase_B_voltage;
    }
    return sum / num_samples;
}

double compute_phase_C_dc(csvread* data, int num_samples) {
    double sum = 0.0;
    for (int i = 0; i < num_samples; i++) {
        sum += data[i].phase_C_voltage;
    }
    return sum / num_samples;
}
//ptp calc ___________________________________________________________________________________________________
double compute_phase_A_ptp(csvread* data, int num_samples) {
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
double compute_phase_B_ptp(csvread* data, int num_samples) {
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
double compute_phase_C_ptp(csvread* data, int num_samples) {
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

void clipping(csvread* data, int num_samples) {
    int clipped_samples = 0;

    printf(" clipping analisis \n");

    printf("      phase A      voltage B      voltage C  \n");

    for (int i = 0; i < num_samples; i++) {
        if (fabs(data[i].phase_A_voltage) >= 324.9) {
            printf(" %11.2f %11s %11s \n", data[i].phase_A_voltage, "-", "-");
            clipped_samples++;
        }
        if (fabs(data[i].phase_B_voltage) >= 324.9) {
            printf(" %11s %12.2f %10s \n", "-", data[0].phase_B_voltage, "-");
            clipped_samples++;
        }
        if (fabs(data[i].phase_C_voltage) >= 324.9) {
            printf(" %11s %11s %16.2f \n", "-", "-", data[0].phase_C_voltage);
            clipped_samples++;
        }
    }
}
