// xlllag.cpp - lag n values
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xlltechnical.h"
#include "../fmstechnical/lag.h"

using namespace technical;
using namespace xll;

static AddInX xai_tai_lag(
	FunctionX(XLL_HANDLEX XLL_UNCALCEDX, _T("?xll_tai_lag"), TAI_PREFIX _T("LAG"))
	.Arg(XLL_USHORTX, _T("Count"), _T("is the number of periods to lag. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to the price lag indicator."))
	.Documentation(
	)
);
HANDLEX WINAPI
xll_tai_lag(unsigned short n)
{
#pragma XLLEXPORT
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new lag<>(n)).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}
