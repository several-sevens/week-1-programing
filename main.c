#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "waveform.h"

waveformsample * load_csv(char * str);

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Cannot find csv file!\n");
        return 1;
    }

    printf("Loading data from %s...\n", argv[1]);

    waveformsample* data = load_csv(argv[1]);

    if (data == NULL) {
        printf("Failed to load data. Program closing.\n");
        return 1;
    }
    printf("Data loaded successfully!\n\n");

    int num_samples = 1000;
    double phase_a_rms = compute_phase_A_rms(data, num_samples);
    double phase_b_rms = compute_phase_B_rms(data, num_samples);
    double phase_c_rms = compute_phase_C_rms(data, num_samples);

    double phase_a_dc = compute_phase_A_dc(data, num_samples);
    double phase_b_dc = compute_phase_B_dc(data, num_samples);
    double phase_c_dc = compute_phase_C_dc(data, num_samples);

    double phase_a_ptp = compute_phase_A_ptp(data, num_samples);
    double phase_b_ptp = compute_phase_B_ptp(data, num_samples);
    double phase_c_ptp = compute_phase_C_ptp(data, num_samples);


    printf(" Power Quality Analysis \n");
    printf("Phase A RMS Voltage: %.2f V\n", phase_a_rms);
    printf("Phase B RMS Voltage: %.2f V\n", phase_b_rms);
    printf("Phase C RMS Voltage: %.2f V\n", phase_c_rms);

    printf("Phase A dc Voltage: %.2f V\n", phase_a_dc);
    printf("Phase B dc Voltage: %.2f V\n", phase_b_dc);
    printf("Phase C dc Voltage: %.2f V\n", phase_c_dc);

    printf("Phase A Peak-to-Peak: %.2f V\n", phase_a_ptp);
    printf("Phase B Peak-to-Peak: %.2f V\n", phase_b_ptp);
    printf("Phase C Peak-to-Peak: %.2f V\n", phase_c_ptp);

    clipping(data, num_samples);

    check_compliance(phase_a_rms, phase_b_rms, phase_c_rms);


    free(data);
    printf("\nMemory freed safely. End of program.\n");

    return 0;
}