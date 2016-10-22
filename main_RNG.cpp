#include <iostream>
using namespace std;
#include <cmath>
#include "RNG.h"

int main() {
	const int N = 10;
	float rngs[N];

	
  generationRN(rngs, N); 

	for(int i = 0; i< N;i++)
		cout<<"RNG["<<i<<"]="<<rngs[i]<<endl;
	return 0;
}

