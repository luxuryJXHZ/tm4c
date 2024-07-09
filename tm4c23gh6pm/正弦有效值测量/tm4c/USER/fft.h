#ifndef fft_h
#define fft_h

struct compx    //定义一个复数结构体
{
  float real;
  float imag;
};
void FFT(struct compx *xin, int Num);
double get_THD(float lBufMagArray[],int NPT);
#endif