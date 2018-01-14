// xllmacd.cpp - Moving Average Convergence Divergence
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "../fmstechnical/macd.h"
#include "xlltechnical.h"

using namespace technical;
using namespace xll;

static AddInX xai_tai_macd(
	FunctionX(XLL_HANDLE, _T("?xll_tai_macd"), TAI_PREFIX _T("MACD"))
	.Arg(XLL_DOUBLE, _T("Weight1"), _T("is the weight used to decay the minuend."))
	.Arg(XLL_DOUBLE, _T("Weight2"), _T("is the weight used to decay the subtrahend. "))
	.Uncalced()
    .Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to the difference of exponentially weighted moving averages of prices."))
	.Documentation(
		_T("The parameters of this indicator are the weights to be used in the difference of the ")
		_T("exponentially weighted moving averages and the state is the ") 
		_T("last values of each exponentially weighted moving average. ")
		_T("The <newTerm>moving average convergence divergence</newTerm> is the difference of ")
		_T("two exponentially weighted moving averages. ")
		_T("If a weight is greater than 1 it is converted to <math>(w - 1)/(w + 1)</math>, just like Bloomberg.")
	)
);
HANDLEX WINAPI
xll_tai_macd(double w0, double w1)
{
#pragma XLLEXPORT
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new macd<>(w0, w1)).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}

