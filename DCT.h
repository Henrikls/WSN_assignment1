#ifndef _DCT_H_
#define _DCT_H_

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "inv_H_and_H.h" //L_size, H and INV_H

#define SIG_SIZE 512
static const double ecg_signal[] = {0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.020, -0.21, -0.33, -0.37, -0.335, -0.285, -0.23, -0.215, -0.20, -0.19, -0.20, -0.20, -0.21, -0.23, -0.25, -0.255, -0.245, -0.24, -0.215, -0.235, -0.23, -0.23, -0.205, -0.18, -0.165, -0.195, -0.21, -0.215, -0.195, -0.17, -0.155, -0.175, -0.195, -0.21, -0.20, -0.20, -0.195, -0.185, -0.185, -0.18, -0.175, -0.175, -0.165, -0.14, -0.12, -0.115, -0.13, -0.155, -0.19, -0.19, -0.185, -0.18, -0.16, -0.14, -0.13, -0.11, -0.12, -0.13, -0.13, -0.125, -0.095, -0.095, -0.090, -0.080, -0.075, -0.070, -0.075, -0.065, -0.055, -0.060, -0.055, -0.040, -0.030, -0.020, -0.015, -0.015, -0.010, 0.015, 0.035, 0.025, 0.015, 0.015, 0.025, 0.025, 0.040, 0.040, 0.030, 0.015, 0.020, 0.035, 0.045, 0.050, 0.025, 0.020, 0.020, 0.010, 0.010, 0, -0.0050, -0.025, -0.020, -0.030, -0.030, -0.035, -0.045, -0.055, -0.060, -0.065, -0.075, -0.080, -0.075, -0.075, -0.075, -0.070, -0.075, -0.080, -0.090, -0.10, -0.095, -0.095, -0.085, -0.095, -0.10, -0.10, -0.115, -0.115, -0.13, -0.14, -0.15, -0.16, -0.145, -0.155, -0.16, -0.17, -0.185, -0.175, -0.17, -0.165, -0.17, -0.17, -0.165, -0.18, -0.18, -0.20, -0.20, -0.215, -0.205, -0.21, -0.205, -0.21, -0.22, -0.225, -0.225, -0.24, -0.225, -0.21, -0.205, -0.195, -0.19, -0.20, -0.19, -0.19, -0.185, -0.17, -0.17, -0.175, -0.165, -0.165, -0.185, -0.185, -0.205, -0.205, -0.21, -0.195, -0.195, -0.19, -0.195, -0.195, -0.195, -0.185, -0.175, -0.175, -0.20, -0.225, -0.25, -0.24, -0.24, -0.24, -0.25, -0.26, -0.27, -0.28, -0.305, -0.335, -0.35, -0.34, -0.285, -0.205, -0.135, -0.095, -0.045, 0.010, 0.075, 0.14, 0.175, 0.135, 0.045, -0.155, -0.425, -0.71, -0.915, -1.09, -1.255, -1.395, -1.465, -1.505, -1.49, -1.45, -1.39, -1.34, -1.27, -1.155, -1.025, -0.95, -0.93, -0.93, -0.91, -0.885, -0.865, -0.84, -0.80, -0.755, -0.715, -0.66, -0.63, -0.58, -0.54, -0.51, -0.465, -0.435, -0.395, -0.365, -0.315, -0.265, -0.20, -0.155, -0.090, -0.040, -0.015, -0.010, 0.0050, 0.030, 0.055, 0.080, 0.085, 0.090, 0.11, 0.11, 0.13, 0.15, 0.155, 0.15, 0.18, 0.185, 0.205, 0.22, 0.235, 0.235, 0.255, 0.27, 0.29, 0.29, 0.30, 0.30, 0.305, 0.325, 0.315, 0.31, 0.315, 0.315, 0.345, 0.36, 0.37, 0.375, 0.375, 0.365, 0.375, 0.385, 0.41, 0.405, 0.40, 0.40, 0.405, 0.40, 0.41, 0.395, 0.40, 0.385, 0.39, 0.395, 0.385, 0.38, 0.355, 0.355, 0.355, 0.35, 0.325, 0.30, 0.28, 0.25, 0.25, 0.25, 0.25, 0.235, 0.21, 0.175, 0.165, 0.16, 0.145, 0.14, 0.145, 0.13, 0.10, 0.080, 0.040, 0.015, -0.010, -0.025, -0.025, -0.030, -0.040, -0.045, -0.070, -0.105, -0.080, -0.075, -0.085, -0.090, -0.11, -0.13, -0.12, -0.115, -0.125, -0.15, -0.17, -0.16, -0.16, -0.15, -0.155, -0.16, -0.17, -0.185, -0.18, -0.18, -0.19, -0.18, -0.17, -0.16, -0.14, -0.14, -0.145, -0.17, -0.18, -0.175, -0.16, -0.155, -0.155, -0.165, -0.15, -0.155, -0.15, -0.145, -0.145, -0.165, -0.195, -0.205, -0.19, -0.18, -0.165, -0.17, -0.16, -0.17, -0.165, -0.17, -0.17, -0.17, -0.17, -0.185, -0.19, -0.18, -0.18, -0.18, -0.175, -0.20, -0.21, -0.20, -0.20, -0.21, -0.215, -0.21, -0.20, -0.175, -0.16, -0.145, -0.145, -0.135, -0.14, -0.135, -0.13, -0.12, -0.115, -0.11, -0.105, -0.10, -0.095, -0.11, -0.14, -0.175, -0.18, -0.18, -0.18, -0.165, -0.175, -0.175, -0.175, -0.165, -0.165, -0.165, -0.175, -0.165, -0.16, -0.155, -0.15, -0.155, -0.16, -0.16, -0.155, -0.145, -0.15, -0.15, -0.185, -0.20, -0.20, -0.195, -0.19, -0.19, -0.195, -0.20, -0.195, -0.185, -0.175, -0.175, -0.155, -0.17, -0.17, -0.165, -0.15, -0.16, -0.165, -0.175, -0.17, -0.17, -0.185, -0.215, -0.225, -0.19, -0.125, -0.040, 0.050, 0.125, 0.215, 0.32, 0.415, 0.50, 0.605, 0.725, 0.845, 0.94, 1.06, 1.11, 1.1, 1.005, 0.86, 0.615, 0.24, -0.11, -0.335, -0.46, -0.515, -0.54, -0.51, -0.44, -0.385, -0.36, -0.35, -0.335, -0.32, -0.295, -0.30, -0.30, -0.325, -0.335, -0.335};
static double decomp_sig[SIG_SIZE];

#define M_size 8
//compression ratio is L/M therefore we can use M/L * sig_size to find the compressed signal size since M<L
#define COMP_DATA_SIZE (SIG_SIZE * M_size / L_size)
static double comp_sig[COMP_DATA_SIZE];

//given L is a multiple of 8 which is an even number then one can use that the gaussian matrix 
//will only get rotated and nothing else will change therefore inv_H can get calculated at the same time as H
//One have to remeber to have a big enough floating point for this to hold true which isn't that great for TelosB
//note: I will simulate how long it takes for the mote to calculate the 8x8 and 16x16 H matrices separately from the transformation.
void Gen_H()
{
    float sel_L = 1.0 * L_size;
    double H[L_size][L_size];
    double inv_H[L_size][L_size];
    
    //precompute the stuff that doesn't change per iteration
    double const_value = M_PI / sel_L;
    float fk = 0;
    for (uint8_t k = 0; k < L_size; k++)
    {
        float fn = 0;
        for (uint8_t n = 0; n < L_size; n++)
        {
            float sq = 0;
            if (k == 0){
                sq = sqrt( (2 - 1) / sel_L );
            }
            else{
                sq = sqrt( 2 / sel_L );
            }
            H[k][n] = 0;
            H[k][n] = sq * cos(const_value * (fn + 0.5) * fk);
            inv_H[n][k] = H[k][n];
            fn = fn+1;
        }
        fk = fk +1;
    }
    //print H
    /*
    int i,j;
    printf("{");
    for (i = 0; i < sel_L; i++){
        printf("{");
        for (j = 0; j < sel_L; j++){
            if(j+1 != sel_L){
                printf("%.3f, ",H[i][j]);
            }
            else{
                printf("%.3f",H[i][j]);
            }
        }
        printf("},");
        printf("\n");  
    }
    printf("***************************************************************\n");
    //print inv_H
    printf("{");
    for (i = 0; i < sel_L; i++){
        printf("{");
        for (j = 0; j < sel_L; j++){
            if(j+1 != sel_L){
                printf("%.3f, ",inv_H[i][j]);
            }
            else{
                printf("%.3f",inv_H[i][j]);
            }
        }
        printf("},");
        printf("\n");  
    }
    */
}

void compress_and_decompress(){
    //I make this calculation to see how many iterations I have to go through below before the signal is fully compressed
    uint8_t iter = SIG_SIZE/L_size;
    //I have made the mulMat function which multiplies 2 matrices now the only problem is to have those 2 matrices to have same dimensions
    //I make this possible by only taking parts of the signal at a time.
    for(uint8_t k = 0; k < iter; k++) {
        double L_signal[L_size];
        for(uint8_t l = 0; l < L_size; l++) {
            //insert the right information into the L_sized signal
            L_signal[l] = ecg_signal[L_size*k+l];
        }
        //mostly taken from geeksforgeeks
        //used to multiply 2 matrices and store them in a third
        for (int i = 0; i < L_size; i++) {
            double rslt = 0;
            for (int j = 0; j < L_size; j++) {
                rslt += H[i][j] * L_signal[j];
            }
            comp_sig[M_size*k+i] = rslt;
        }
    }
    //print the compressed signal
    /*for (int i=0; i < COMP_DATA_SIZE; i++){
        printf("%.3f ",comp_sig[i]); 
        if(i % 16 == 0){
            printf("\n");
        }
    }
    printf("\n");*/
    //decompress
    uint8_t iter_M = COMP_DATA_SIZE/L_size;
    //we do most of the same as before
    for(uint8_t k = 0; k < iter_M; k++) {
        double M_signal[L_size];
        for(uint8_t l = 0; l < M_size; l++) {
            //insert the right information into the L_sized signal
            M_signal[l] = comp_sig[L_size*k+l];
            //printf("%.3f, ",comp_sig[L_size*k+l]);
        }
        for(uint8_t q = M_size; q < L_size; q++) {
            //pad with 0's
            M_signal[q] = 0;
        }
        for (int i = 0; i < L_size; i++) {
            double rslt = 0;
            for (int j = 0; j < M_size; j++) {
                rslt += inv_H[i][j] * M_signal[j];
            }
            decomp_sig[L_size*k+i] = rslt;
            //printf("%.3f, ",rslt);
        }
        //printf("\n");
    }
    //print the decompressed signal
    for (int i=1; i < COMP_DATA_SIZE+1; i++){
        printf("%.3f, ",decomp_sig[i-1]); 
        if(i % 16 == 0){
            printf("\n");
        }
    }
    printf("\n");
}

#endif // _DCT_H_
