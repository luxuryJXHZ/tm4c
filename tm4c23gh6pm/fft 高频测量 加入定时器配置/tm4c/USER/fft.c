#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <fft.h>

struct compx EE(struct compx b1, struct compx b2)
{
	struct compx b3;
	b3.real = b1.real*b2.real - b1.imag*b2.imag;
	b3.imag = b1.real*b2.imag + b1.imag*b2.real;
	return (b3);
}

void FFT(struct compx *xin, int Num)
{
	int f, m, LH, nm, i, k, j, L;
	double p, ps ;
	int le, B, ip;
	float pi;
	struct compx w, t;
	
	LH = Num / 2; 
	f  = Num;
	for (m=1; (f=f/2)!=1; m++)     // 2^m=N
	{
		for (L=m; L>=1; L--)          // 这里和时域的也有差别
		{ 
			le = pow(2, L);             //用于计算次方
			B  = le / 2;                // 每一级碟形运算间隔的点数
			pi = 3.1415;
			for (j=0; j<=B-1; j++)
			{
				p  = pow(2, m-L) * j;
				ps = 2*pi/Num*p;
				w.real = cos(ps);
				w.imag = -sin(ps);
				for (i=j; i<=Num-1; i=i+le)
				{
					ip = i+B;  
					t  = xin[i];
					xin[i].real = xin[i].real + xin[ip].real;
					xin[i].imag = xin[i].imag + xin[ip].imag;  
					xin[ip].real = xin[ip].real - t.real;
					xin[ip].imag = xin[ip].imag - t.imag;     
					xin[ip] = EE(xin[ip], w);
				}
			}
		}
	}
	// 变址运算
	nm = Num - 2;   
	j  = Num / 2;
	for(i=1;i<=nm;i++)
	{
	if(i<j){t=xin[j];xin[j]=xin[i];xin[i]=t;}
	k=LH;
	while(j>=k){j=j-k;k=k/2;}
	j=j+k;
	}
}

double get_THD (float lBufMagArray[],int NPT)
{
    long fre,fmax,f1,f2,f3,f4,f5;
    int i;
    double THD;

    fmax=0;
    for(i=1;i<NPT/2;i++)
    {
        if(lBufMagArray[i]>fmax)
        {
            fre=i;
            fmax=lBufMagArray[i];
        }
    }
    f1=fmax;
    fmax=0;
    if(2*fre+2>=NPT)
    {
        f2=0;
        f3=0;
        f4=0;
        f5=0;
    }
    else
    {
        for(i=2*fre-2;i<2*fre+2;i++)
        {
            if(lBufMagArray[i]>fmax)
            {
                fmax=lBufMagArray[i];
            }
        }
        f2=fmax;
    }

    fmax=0;
    if(3*fre+2>=NPT)
    {
        f3=0;
        f4=0;
        f5=0;
    }
    else
    {
        for(i=3*fre-2;i<3*fre+2;i++)
        {
            if(lBufMagArray[i]>fmax)
            {
                fmax=lBufMagArray[i];
            }
        }
        f3=fmax;
    }


    fmax=0;
    if(4*fre+3>=NPT)
    {
        f4=0;
        f5=0;
    }
    else
    {
        for(i=4*fre-3;i<4*fre+3;i++)
        {
            if(lBufMagArray[i]>fmax)
            {
                fmax=lBufMagArray[i];
            }
        }
        f4=fmax;
    }

    fmax=0;
    if(5*fre+3>=NPT)
    {
        f5=0;
    }
    else
    {
        for(i=5*fre-3;i<5*fre+3;i++)
        {
            if(lBufMagArray[i]>fmax)
            {
            fmax=lBufMagArray[i];
            }
        }
        f5=fmax;
    }


    THD=(sqrt(f2*f2+f3*f3+f4*f4+f5*f5))/f1;
    return THD;
}