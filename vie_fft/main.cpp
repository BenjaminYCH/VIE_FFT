#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    char string[255];
    char s[255];

    int m;
    int myid,numprocs;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    remove("../result/Ene_Metal.txt");  //ɾ�������ļ�
	remove("../result/Grid.txt");       //ɾ�������ļ�
	remove("../result/Ene_Active.txt"); //ɾ�������ļ�

	MPI_Barrier(MPI_COMM_WORLD);

	for (m=1; m<=41; m++)  //Ƶ��
	{
		if (m%numprocs==myid)
		{
            strcpy(string, "./CG_FFT_VIE ");
            sprintf(s,"%d\n",m);
            strcat(string,s);
            system(string);
		}
	}

    MPI_Barrier(MPI_COMM_WORLD);

	char string_fre[256];      //ɨƵ��
    char string_metal[256];    //����������ʧ�����ļ�·��
    char string_active[256];   //�л��������������ļ�·��
    char string_grid[256];     //�����ʷ��ļ�·��
    //�ļ�ָ��
	FILE* file0;
	FILE* file1;
	FILE* file2;
	FILE* file3;
	FILE* file4;
	FILE* file5;

    //���ɾ���ļ�
    if (myid==1)  //���1������
    {
        //����ƴ���ļ�
        file3=fopen("../result/Ene_Metal.txt","w");
        file4=fopen("../result/Ene_Active.txt","w");
        file5=fopen("../result/Grid.txt","w");

        for (m=0; m<41; m++)
        {
            //���������ļ�
            strcpy(string_metal, "../result/Ene_Metal");
            strcpy(string_active, "../result/Ene_Active");
            strcpy(string_grid, "../result/Grid");
            sprintf(string_fre,"%d",m);
            strcat(string_metal,string_fre);
            strcat(string_active,string_fre);
            strcat(string_grid,string_fre);
            strcat(string_metal,".txt");
            strcat(string_active,".txt");
            strcat(string_grid,".txt");

            file0=fopen(string_metal,"r");
            file1=fopen(string_active,"r");
            file2=fopen(string_grid,"r");

            int wavelength1,wavelength2;
            double extinct;
            double absorb1,absorb2;
            int Fre_Point,Nx,Ny,Nz;
            double delta_x,delta_y,delta_z;

            //����������ս��棬��ʧ����
            fscanf(file0,"%d %lf %lf\n",&wavelength1,&extinct,&absorb1);
            //�������ղ��ϵĵ�λ�������������
            fscanf(file1,"%d %lf\n",&wavelength2,&absorb2);
            //���뽨ģ����Ϣ
            fscanf(file2,"%d %d %d %d %lf %lf %lf\n",&Fre_Point,&Nx,&Ny,&Nz,&delta_x,&delta_y,&delta_z);

            //д��������ս��棬��ʧ����
            fprintf(file3,"%d %.15lf %.15lf\n",wavelength1,extinct,absorb1);
            //д�����ղ��ϵĵ�λ�������������
            fprintf(file4,"%d %.15lf\n",wavelength2,absorb2);
            //д�뽨ģ����Ϣ
            fprintf(file5, "%d %d %d %d %.15lf %.15lf %.15lf\n",Fre_Point,Nx,Ny,Nz,delta_x,delta_y,delta_z);

            //�ر�ɾ�������ļ�
            fclose(file0);
            fclose(file1);
            fclose(file2);
            remove(string_metal);
            remove(string_active);
            remove(string_grid);
        }
        //�ر�д���ļ�
        fclose(file3);
        fclose(file4);
        fclose(file5);
    }

    MPI_Finalize();

    cout << "Finished" << endl;
    return 0;
}
