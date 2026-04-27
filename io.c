#include <stdio.h>
#include <stdlib.h>
#include "io.h"


waveformsample* load_csv(char* filename) {

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s\n", filename);
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

