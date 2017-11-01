// xllrelative_strength.cpp - Moving Average Convergence Divergence
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "../fmstechnical/relative_strength.h"
#include "xlltechnical.h"

using namespace technical;
using namespace xll;

static AddInX xai_tai_relative_strength(
	FunctionX(XLL_HANDLEX XLL_UNCALCEDX, _T("?xll_tai_relative_strength"), TAI_PREFIX _T("RELATIVE.STRENGTH"))
	.Arg(XLL_DOUBLEX, _T("Weight"), _T("is the weight used to decay the data. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to the difference of exponentially weighted moving averages of prices."))
	.Documentation(
		_T("The parameter of this indicator is the <codeInline>Weight</codeInline> and the state is determined ")
		_T("by the last price, the last value of the exponentially weighted moving average of the up-ticks, ")
		_T("the last price, and the last value of the exponentially weighted moving average of the down-ticks. ")
		_T("(Yes, the last price occurs twice.) ")
		_T("The <newTerm>relative strength</newTerm> is the ratio of ")
		_T("the exponentially weighted moving averages of the up-ticks ")
		_T("and the exponentially weighted moving averages of the down-ticks. ")
		_T("If <codeInline>Weight</codeInline> is greater than 1 it is converted to <math>(w - 1)/(w + 1)</math>, just like Bloomberg.")
	)
);
HANDLEX WINAPI
xll_tai_relative_strength(double w)
{
#pragma XLLEXPORT
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new relative_strength<>(w)).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}

static AddInX xai_tai_relative_strength_index(
	FunctionX(XLL_DOUBLEX, _T("?xll_tai_relative_strength_index"), TAI_PREFIX _T("RELATIVE.STRENGTH.INDEX"))
	.Arg(XLL_DOUBLEX, _T("RS"), _T("is the relative strength. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the relative strength index as a number between 0 and 1. "))
	.Documentation(
		_T("The <newTerm>relative strength index</newTerm> is <math>1 - 1/(1 + rs)</math>, where ")
		_T("<math>rs</math> is the relative strength. ")
	)
);
double WINAPI
xll_tai_relative_strength_index(double rs)
{
#pragma XLLEXPORT

	return relative_strength<>::index(rs);
}

