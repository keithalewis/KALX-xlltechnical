// xllminmax.cpp - running minimum and maximum values
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "../fmstechnical/minmax.h"
#include "xlltechnical.h"

using namespace technical;
using namespace xll;

static AddInX xai_tai_min(
	FunctionX(XLL_HANDLEX XLL_UNCALCEDX, _T("?xll_tai_min"), TAI_PREFIX _T("MIN"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to the running minimum indicator."))
	.Documentation(
		_T("This indicator has no parameters and the state is the running minimum. ")
	)
);
HANDLEX WINAPI
xll_tai_min()
{
#pragma XLLEXPORT
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new minimum<>()).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}

static AddInX xai_tai_max(
	FunctionX(XLL_HANDLEX XLL_UNCALCEDX, _T("?xll_tai_max"), TAI_PREFIX _T("MAX"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to the running maximum indicator."))
	.Documentation(
		_T("This indicator has no parameters and the state is the running maximum. ")
	)
);
HANDLEX WINAPI
xll_tai_max()
{
#pragma XLLEXPORT
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new maximum<>()).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}
