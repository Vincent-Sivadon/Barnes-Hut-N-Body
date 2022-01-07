
#include <stdio.h>

FILE* openFile(char* filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        printf("Error in load file : can't open '%s'\n", filename);
    return fp;
}

int main()
{
    // Number of time steps used
    int Nt = 10;


    // Array to store data
    double base[5][Nt];
    double soa[5][Nt];
    double oct[5][Nt];

    // Array to store processed data
    double base_mean[5]    ; double base_sigma[5];
    double soa_mean[5]     ; double soa_sigma[5];
    double oct_mean[5]     ; double oct_sigma[5];

    double sizes[5] = {500, 1000, 5000, 10000, 16384};

    // Initialiaze arrays
    for(int i=0 ; i<5 ; i++)
    {
        base_mean[i] = 0 ; base_sigma[i] = 0;
        soa_mean[i]  = 0 ; soa_sigma[i]  = 0;
        oct_mean[i] = 0 ; oct_sigma[i] = 0;
    }

    FILE *f_base500   = openFile("files/base500.dat");
    FILE *f_base1000  = openFile("files/base1000.dat");
    FILE *f_base5000  = openFile("files/base5000.dat");
    FILE *f_base10000 = openFile("files/base10000.dat");
    FILE *f_base16384 = openFile("files/base16384.dat");

    FILE *f_soa500   = openFile("files/soa500.dat");
    FILE *f_soa1000  = openFile("files/soa1000.dat");
    FILE *f_soa5000  = openFile("files/soa5000.dat");
    FILE *f_soa10000 = openFile("files/soa10000.dat");
    FILE *f_soa16384 = openFile("files/soa16384.dat");

    FILE *f_oct500   = openFile("files/oct500.dat");
    FILE *f_oct1000  = openFile("files/oct1000.dat");
    FILE *f_oct5000  = openFile("files/oct5000.dat");
    FILE *f_oct10000 = openFile("files/oct10000.dat");
    FILE *f_oct16384 = openFile("files/oct16384.dat");

    double b500, b1000, b5000, b10000, b16384;
    double s500, s1000, s5000, s10000, s16384;
    double o500, o1000, o5000, o10000, o16384;
    double tmp;

    // Getting data
    for(int i=0 ; i<Nt ; i++)
    {
        fscanf(f_base500,   "%lf\n", &b500);
        fscanf(f_base1000,  "%lf\n", &b1000);        
        fscanf(f_base5000,  "%lf\n", &b5000);        
        fscanf(f_base10000, "%lf\n", &b10000);        
        fscanf(f_base16384, "%lf\n", &b16384);        

        fscanf(f_soa500,   "%lf\n", &s500);
        fscanf(f_soa1000,  "%lf\n", &s1000);        
        fscanf(f_soa5000,  "%lf\n", &s5000);        
        fscanf(f_soa10000, "%lf\n", &s10000);        
        fscanf(f_soa16384, "%lf\n", &s16384);        

        fscanf(f_oct500,   "%lf\n", &o500);
        fscanf(f_oct1000,  "%lf\n", &o1000);        
        fscanf(f_oct5000,  "%lf\n", &o5000);        
        fscanf(f_oct10000, "%lf\n", &o10000);        
        fscanf(f_oct16384, "%lf\n", &o16384);        

        base[0][i] = b500;
        base[1][i] = b1000;
        base[2][i] = b5000;
        base[3][i] = b10000;
        base[4][i] = b16384;

        soa[0][i] = s500;
        soa[1][i] = s1000;
        soa[2][i] = s5000;
        soa[3][i] = s10000;
        soa[4][i] = s16384;

        oct[0][i] = o500;
        oct[1][i] = o1000;
        oct[2][i] = o5000;
        oct[3][i] = o10000;
        oct[4][i] = o16384;
    }

    // Mean
    for(int i=0 ; i<5 ; i++)
        for(int j=0 ; j<Nt ; j++)
        {
            base_mean[i] += base[i][j]/Nt;
            soa_mean[i]  += soa[i][j]/Nt;
            oct_mean[i] += oct[i][j]/Nt;
        }

    // Standard Deviation
    for(int i=0 ; i<5 ; i++)
        for(int j=0 ; j<Nt ; j++)
        {
            base_sigma[i] += (base[i][j] - base_mean[i]) * (base[i][j] - base_mean[i]);
            soa_sigma[i]  += (soa[i][j]  - soa_mean[i])  * (soa[i][j]  - soa_mean[i]);
            oct_sigma[i] += (oct[i][j] - oct_mean[i]) * (oct[i][j] - oct_mean[i]);
        }

    
    // Writing processed data
    FILE *f_base_mean  = fopen("files/base_mean.dat" , "wb");
    FILE *f_soa_mean   = fopen("files/soa_mean.dat"  , "wb");
    FILE *f_oct_mean   = fopen("files/oct_mean.dat" , "wb");

    FILE *f_base_sigmam = fopen("files/base_sigmam.dat", "wb");
    FILE *f_base_sigmap = fopen("files/base_sigmap.dat", "wb");

    FILE *f_soa_sigmam  = fopen("files/soa_sigmam.dat" , "wb");
    FILE *f_soa_sigmap  = fopen("files/soa_sigmap.dat" , "wb");

    FILE *f_oct_sigmam = fopen("files/oct_sigmam.dat", "wb");
    FILE *f_oct_sigmap = fopen("files/oct_sigmap.dat", "wb");

    // Speed up
    FILE *f_oct_speedup  = fopen("files/oct_speedup.dat", "wb");
    FILE *f_soa_speedup  = fopen("files/soa_speedup.dat" , "wb");

    for(int i=0 ; i<5 ; i++)
    {
        fprintf(f_base_mean, "%lf ", sizes[i]);
        fprintf(f_base_mean, "%lf \n", base_mean[i]);

        fprintf(f_soa_mean, "%lf ", sizes[i]);
        fprintf(f_soa_mean, "%lf \n" , soa_mean[i]);

        fprintf(f_oct_mean, "%lf ", sizes[i]);
        fprintf(f_oct_mean, "%lf \n", oct_mean[i]);

        fprintf(f_base_sigmap, "%lf ", sizes[i]);
        fprintf(f_base_sigmap, "%lf \n", base_mean[i] + base_sigma[i]);
        fprintf(f_base_sigmam, "%lf ", sizes[i]);
        fprintf(f_base_sigmam, "%lf \n", base_mean[i] - base_sigma[i]);

        fprintf(f_soa_sigmap, "%lf ", sizes[i]);
        fprintf(f_soa_sigmap, "%lf \n" , soa_mean[i] + soa_sigma[i]);
        fprintf(f_soa_sigmam, "%lf ", sizes[i]);
        fprintf(f_soa_sigmam, "%lf \n" , soa_mean[i] - soa_sigma[i]);

        fprintf(f_oct_sigmap, "%lf ", sizes[i]);
        fprintf(f_oct_sigmap, "%lf \n", oct_mean[i] + oct_sigma[i]);
        fprintf(f_oct_sigmam, "%lf ", sizes[i]);
        fprintf(f_oct_sigmam, "%lf \n", oct_mean[i] - oct_sigma[i]);

        // Speedup
        fprintf(f_oct_speedup, "%lf ", sizes[i]);
        fprintf(f_oct_speedup, "%lf \n", base_mean[i] / oct_mean[i]);

        fprintf(f_soa_speedup, "%lf ", sizes[i]);
        fprintf(f_soa_speedup, "%lf \n", base_mean[i] / soa_mean[i]);
    }

    fclose(f_base500);
    fclose(f_base1000);
    fclose(f_base5000);
    fclose(f_base10000);
    fclose(f_base16384);

    fclose(f_soa500);
    fclose(f_soa1000);
    fclose(f_soa5000);
    fclose(f_soa10000);
    fclose(f_soa16384);

    fclose(f_oct500);
    fclose(f_oct1000);
    fclose(f_oct5000);
    fclose(f_oct10000);
    fclose(f_oct16384);

    fclose(f_base_mean);
    fclose(f_soa_mean);
    fclose(f_oct_mean);

    fclose(f_base_sigmap);
    fclose(f_base_sigmam);
    fclose(f_soa_sigmap);
    fclose(f_soa_sigmam);
    fclose(f_oct_sigmap);
    fclose(f_oct_sigmam);

    // Speedup
    fclose(f_oct_speedup);
    fclose(f_soa_speedup);


    return 0;
}