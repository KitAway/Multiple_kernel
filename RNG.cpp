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
* In the definition of Box_Muller(), sin/cos are used instead of sinf/cosf
* due to bugs in the synthesizer (C/RTL co-simulation is failing).
*
* macro__SINF_COSF_BUG_FIXED__ controls the switch between the two version.
*
*----------------------------------------------------------------------------
*/

#include "RNG.h"

template<typename T> void RNG<T>::init(unsigned int seed)
{
	const int RNG_F = 0x6C078965;
	const int RNG_W = 32;
	this->index = 0;
	this->seed=seed;
	unsigned int tmp=seed;

	loop_seed_init:for (int i = 0; i < RNG_H; i++)
	{
		mt_e[i]=tmp;
		tmp= RNG_F*(tmp^ (tmp >> (RNG_W - 2))) + i*2+1;
		mt_o[i]=tmp;
		tmp= RNG_F*(tmp^ (tmp >> (RNG_W - 2))) + i*2+2;
	}
}

template<typename T> void RNG<T>::init_array(RNG<T>* rng, unsigned int* seed, const int size)
{
	const int RNG_F = 0x6C078965;
	const int RNG_W = 32;
	const int RNG_H = 312;
	unsigned int tmp[size];
#pragma HLS ARRAY_PARTITION variable=tmp complete dim=1

	loop_set_seed:for(int i=0;i<size;i++)
	{
#pragma HLS UNROLL
		rng[i].index = 0;
		rng[i].seed=seed[i];
		tmp[i]=seed[i];
	}


	loop_seed_init:for (int i = 0; i < RNG_H; i++)
	{
#pragma HLS PIPELINE
		loop_group_init:for(int k=0;k<size;k++)
		{
#pragma HLS UNROLL
			rng[k].mt_e[i]=tmp[k];
			tmp[k]= RNG_F*(tmp[k]^ (tmp[k] >> (RNG_W - 2))) + i*2+1;
			rng[k].mt_o[i]=tmp[k];
			tmp[k]= RNG_F*(tmp[k]^ (tmp[k] >> (RNG_W - 2))) + i*2+2;
		}
	}
}


template<typename T> void RNG<T>::extract_number(unsigned int *num1, unsigned int *num2)
{
#pragma HLS INLINE
	const int RNG_MH = 198;
	const int RNG_MHI = 199;
	const int RNG_U =11;
	const int RNG_A =0x9908B0DF;
	const int RNG_D =0xFFFFFFFF;
	const int RNG_S =7;
	const int RNG_B =0x9D2C5680;
	const int RNG_T =15;
	const int RNG_C =0xEFC60000;
	const int RNG_L =18;
	const int lower_mask = 0x7FFFFFFF;
	const int upper_mask = 0x80000000;
	int id=this->index, id1=increase(1), idm=increase(RNG_MH), idm1=increase(RNG_MHI);

 	unsigned int x = this->seed,x1=this->mt_o[this->index],x2=this->mt_e[id1],
 			xm=this->mt_o[idm],xm1=this->mt_e[idm1];

	x = (x & upper_mask)+(x1 & lower_mask);
	unsigned int xp = x >> 1;
	if ((x & 0x01) != 0)
		xp ^= RNG_A;
	x = xm ^ xp;

	unsigned int y = x;
	y ^= ((y >> RNG_U)&RNG_D);
	y ^= ((y << RNG_S)&RNG_B);
	y ^= ((y << RNG_T)&RNG_C);
	y ^= (y >> RNG_L);
	*num1 = y;
	mt_e[id]=x;

	x1 =( x1 & upper_mask) + (x2 & lower_mask);
	unsigned int xt = x1 >> 1;
	if ((x1 &0x01) != 0)
		xt ^= RNG_A;
	x1 = xm1 ^ xt;

	unsigned int y1 = x1;
	y1 ^= ((y1 >> RNG_U)&RNG_D);
	y1 ^= ((y1 << RNG_S)&RNG_B);
	y1 ^= ((y1 << RNG_T)&RNG_C);
	y1 ^= (y1 >> RNG_L);
	*num2 = y1;
	mt_o[id]=x1;

	this->index=id1;
	this->seed=x2;
}


template<typename T> int RNG<T>::increase(int k)
{
	int tmp= this->index+k;
	return (tmp>=RNG_H)? tmp-RNG_H:tmp;
}


template<typename T> void RNG<T>::BOX_MULLER(T *data1, T *data2)
{
#pragma HLS INLINE
    const T PI = 3.14159265358979323846;
	const T MINI_RND = 2.328306e-10;
	T tp,tmp1,tmp2;
	unsigned int num1,num2;

	extract_number(&num1,&num2);
	tmp1=num1*MINI_RND;
	tmp2=num2*MINI_RND;
	tp=sqrtf(fmaxf(-2*logf(tmp1),0));
	*data1=cosf(2*PI*(tmp2))*tp;
	*data2=sinf(2*PI*(tmp2))*tp;
}


