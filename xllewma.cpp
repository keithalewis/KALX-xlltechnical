// xllewma.cpp - Exponentially Weighted Moving Average
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "../fmstechnical/ewma.h"
#include "xlltechnical.h"

using namespace technical;
using namespace xll;

static AddInX xai_ta_ewma(
	FunctionX(XLL_HANDLEX XLL_UNCALCEDX, _T("?xll_ta_ewma"), TAI_PREFIX _T("EWMA"))
	.Arg(XLL_DOUBLEX, _T("Weight"), _T("is the weight used to decay the data. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the exponentially weighted moving average of prices."))
	.Documentation(
		_T("The parameter for this indicator is the <codeInline>Weight</codeInline> and the state is the ")
		_T("last value of the exponentially weighted moving average. ")
		_T("The <newTerm>exponentially weighted moving average</newTerm> is determined by ")
		_T("<math>y<subscript>j</subscript> = (1 - w) x<subscript>j</subscript> + w y<subscript>j - 1</subscript></math>, ")
		_T("where <math>w</math> is the Weight, <math>x<subscript>j</subscript></math> are the Series values, and <math>y<subscript>0</subscript></math> ")
		_T("is the initial state. ")
		_T("If Weight is greater than 1 it is converted to <math>(w - 1)/(w + 1)</math>, just like Bloomberg.")
	)
);
HANDLEX WINAPI
xll_ta_ewma(double w)
{
#pragma XLLEXPORT
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new ewma<>(w)).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}

