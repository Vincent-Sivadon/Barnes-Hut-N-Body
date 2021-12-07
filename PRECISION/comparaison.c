#include <stdio.h>

int main() {
    FILE *fp0 = fopen("0.dat", "rb");
    if (!fp0)
    printf("Error in load_matx : can't open '%s'\n", "0.dat");

    #if defined SOA
        FILE *fpSOA = fopen("SOA.dat", "rb");
        if (!fpSOA)
        printf("Error in load_matx : can't open '%s'\n", "SOA.dat");
    #endif

    #if defined QUAD
        FILE *fpQUAD = fopen("quad.dat", "rb");
        if (!fpQUAD)
        printf("Error in load_matx : can't open '%s'\n", "quad.dat");
    #endif


    double f0=0, f1=0;
    for(int i=0 ; i<500*1000 ; i++){
        fscanf(fp0, "%lf\n", &f0);
        #if defined SOA
            fscanf(fpSOA, "%lf\n", &f1);
        #endif

        #if defined QUAD
            fscanf(fpQUAD, "%lf\n", &f1);
        #endif

        double delta = (f1 - f0)/f0;
        printf("%.12lf\n", delta);
    }

    fclose(fp0);

    #if defined SOA
        fclose(fpSOA);
    #endif

    #if defined QUAD
        fclose(fpQUAD);
    #endif

    return 0;
}