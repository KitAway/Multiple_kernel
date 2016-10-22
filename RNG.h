/* 
======================================================
 Copyright 2016 Liang Ma

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
======================================================
*
* Author:   Liang Ma (liang-ma@polito.it)
*
* Here declares the class RNG which is short for Random Number Generator.
* It implements 32bits Mersenne-Twist algorithm and Box-Muller transformation.
*
* RNG_N is the total size of the states
* mt_e/mt_o are two arrays that stores the states.
* extract_number produces two uniformly i.i.d. numbers
* init()/init_array() are two functions for state initialization.
*
*----------------------------------------------------------------------------
*/

#ifndef __RNG__
#define __RNG__

#include "hls_math.h"
template<typename T> class RNG
{
public:
	static const int RNG_H = 312;
	int index;
	unsigned int seed;
	unsigned int mt_e[RNG_H],mt_o[RNG_H];

	void init(unsigned int);
	void extract_number(unsigned int*,unsigned int*);
	void BOX_MULLER(T*, T*);
	int increase(int);
	int & operator ++();

	static void init_array(RNG*, unsigned int*,const int);

};

void generationRN(float *RNGs, const int SIZE);   // call price and put price
#endif

