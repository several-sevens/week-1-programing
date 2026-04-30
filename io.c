#include <stdio.h>
#include <stdlib.h>
#include "io.h"


waveformsample* load_csv(void) {

        FILE* fp = fopen("power_quality_log.csv", "r");
    if (fp == NULL)
        fp = fopen("../power_quality_log.csv", "r");
    if (fp == NULL) {
        printf("Could not open power_quality_log.csv\n");
        return NULL;
    }

    waveformsample *csv = (waveformsample*)malloc(1000  * sizeof(waveformsample));
    if (csv == NULL) {
        fclose(fp);
        return NULL;
    }

    char line[256];
    if (fgets(line, sizeof(line), fp) == NULL) {
        fclose(fp);
        free(csv);
        return NULL;
    }

    for (int i = 0; i < 1000 ; i++) {
        fscanf(fp, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
            &csv[i].timestamp,
            &csv[i].phase_A_voltage,
            &csv[i].phase_B_voltage,
            &csv[i].phase_C_voltage,
            &csv[i].line_current,
            &csv[i].frequency,
            &csv[i].power_factor,
            &csv[i].thd_percent);
    }

    fclose(fp);
    return csv;
}
void write_results(const char* filename,
                   double rms_a, double rms_b, double rms_c,
                   double dc_a, double dc_b, double dc_c,
                   double ptp_a, double ptp_b, double ptp_c,
                   int clip_a, int clip_b, int clip_c) {

    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: could not write to %s\n", filename);
        return;
    }

    double nominal = 230.0;
    double lower = nominal * 0.90;
    double upper = nominal * 1.10;

    fprintf(fp, "=== Power Quality Analysis Report ===\n\n");

    fprintf(fp, "\n--- Tolerance Compliance (230V +/-10%%) ---\n");
    fprintf(fp, "Phase A: %.2f V -> %s\n", rms_a,
        (rms_a >= lower && rms_a <= upper) ? "PASS" : "FAIL");
    fprintf(fp, "Phase B: %.2f V -> %s\n", rms_b,
        (rms_b >= lower && rms_b <= upper) ? "PASS" : "FAIL");
    fprintf(fp, "Phase C: %.2f V -> %s\n", rms_c,
        (rms_c >= lower && rms_c <= upper) ? "PASS" : "FAIL");

    fprintf(fp, "--- RMS Voltage ---\n");
    fprintf(fp, "Phase A: %.2f V\n", rms_a);
    fprintf(fp, "Phase B: %.2f V\n", rms_b);
    fprintf(fp, "Phase C: %.2f V\n", rms_c);

    fprintf(fp, "\n--- DC Offset ---\n");
    fprintf(fp, "Phase A: %.2f V\n", dc_a);
    fprintf(fp, "Phase B: %.2f V\n", dc_b);
    fprintf(fp, "Phase C: %.2f V\n", dc_c);

    fprintf(fp, "\n--- Peak-to-Peak Amplitude ---\n");
    fprintf(fp, "Phase A: %.2f V\n", ptp_a);
    fprintf(fp, "Phase B: %.2f V\n", ptp_b);
    fprintf(fp, "Phase C: %.2f V\n", ptp_c);

    fprintf(fp, "\n--- Clipping Detection ---\n");
    fprintf(fp, "Phase A: %d clipped samples\n", clip_a);
    fprintf(fp, "Phase B: %d clipped samples\n", clip_b);
    fprintf(fp, "Phase C: %d clipped samples\n", clip_c);

    fclose(fp);
    printf("\nResults written to %s\n", filename);
}
