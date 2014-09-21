#include <windows.h>
double microtime(){
	static __int64 freq=0;
	if(freq==0){
	QueryPerformanceFrequency ((LARGE_INTEGER*)&freq);
	}
	static __int64 t=0,t1;
	QueryPerformanceCounter ((LARGE_INTEGER*)&t1);
	double dt=double(t1-t)/freq;
	if(t==0)dt=0;
	t=t1;
	return dt;
}
template <typename T>
T modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}
unsigned int random(unsigned int max=32767){
	static unsigned int r=233;
	r=(23*modpow<unsigned long long>(157,r,max)+657)%max;
	return r;
}