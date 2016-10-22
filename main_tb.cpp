/*----------------------------------------------------------------------------
*
* Author:   Liang Ma (liang-ma@polito.it)
*
*----------------------------------------------------------------------------
*/
#include "defTypes.h"
#include <iostream>
#include "../common/stockData.h"
#include "../common/volatilityData.h"
#include "../common/barrierData.h"
#include "hestonBarrier.h"
using namespace std;

int main(int argc, char ** argv)
{

	data_t call,put,acc=0.01;
	const data_t timeT=1.0, Rate=0.0, Vol=0.04,
						Stock=100,Strike=100;
	const data_t upB=110,lowB=90;
	const data_t expect=0.04,kappa=0.5,variance=1,col=0;
	hestonEuroBarrier(&call,&put,expect,				// theta
		 kappa,				// kappa
		 variance,			// xi
		 col,			// rho
		 timeT,				// time period of options
		 Rate,			// interest rate of the riskless asset
		 Vol,			// volatility of the risky asset
		 Stock,			// stock price at time 0
		 Strike,			// strike price
		 upB,				// up barrier
		 lowB);
	cout<<"call:"<<call<<'\t'
			<<"put:"<<put<<endl;
	return 0;
}
