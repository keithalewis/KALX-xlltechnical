// true_range.cpp - True Range
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xlltechnical.h"
#include "../fmstechnical/true_range.h"

using technical::indicator_base;
using technical::true_range;
using namespace xll;

static AddInX xai_true_range(
	FunctionX(XLL_HANDLE, _T("?xll_true_range"), TAI_PREFIX _T("TRUE.RANGE"))
	.Uncalced()
    .Category(CATEGORY)
	.FunctionHelp(_T("Returns a handle to the true range indicator: the maximum of the High and previous Close minus the minimum of the Low and previous Close."))
	.Documentation(
		_T("The idea of ranges is that they show the commitment or enthusiasm of traders. ")
		_T("Note true range does not change when historical prices are backadjusted by adding or subtracting a constant to every price. ")
	)
);
HANDLEX WINAPI
xll_true_range()
{
#pragma XLLEXPORT
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new true_range<>()).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}
