// xlltick.cpp - up and down ticks
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "../fmstechnical/tick.h"
#include "xlltechnical.h"

using namespace technical;
using namespace xll;

static AddInX xai_ta_tick_up(
	FunctionX(XLL_HANDLE, _T("?xll_tai_tick_up"), TAI_PREFIX _T("TICK.UP"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to the up-tick indicator."))
	.Documentation(
		_T("This indicator has no parameters and the state is the last price. ")
		_T("The <newTerm>up-tick</newTerm> is the maximum of the difference between the current price and the last price if positive, otherwise zero. ")
	)
);
HANDLEX WINAPI
xll_tai_tick_up()
{
#pragma XLLEXPORT
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new tick_up<>()).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}

static AddInX xai_tai_tick_down(
	FunctionX(XLL_HANDLE, _T("?xll_tai_tick_down"), TAI_PREFIX _T("TICK.DOWN"))
	.Uncalced()
    .Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to the down-tick indicator."))
	.Documentation(
		_T("This indicator has no parameters and the state is the last price. ")
		_T("The <newTerm>down-tick</newTerm> is the maximum of the difference between the last price and the current price if positive, otherwise zero. ")
	)
);
HANDLEX WINAPI
xll_tai_tick_down()
{
#pragma XLLEXPORT
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new tick_down<>()).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}
