#ifndef fft_h
#define fft_h

struct compx    //����һ�������ṹ��
{
  float real;
  float imag;
};
void FFT(struct compx *xin, int Num);
double get_THD(float lBufMagArray[],int NPT);
#endif