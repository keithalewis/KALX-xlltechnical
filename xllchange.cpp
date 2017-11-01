// xllchange.cpp - change from previous value
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "../fmstechnical/change.h"
#include "xlltechnical.h"

using namespace technical;
using namespace xll;

static AddInX xai_tai_change(
	FunctionX(XLL_HANDLEX XLL_UNCALCEDX, _T("?xll_tai_change"), TAI_PREFIX _T("CHANGE"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to the price change indicator."))
	.Documentation(
		_T("This indicator has no parameters and the state is the last price. ")
		_T("The <newTerm>change</newTerm> is the difference between the current price and the last price. ")
	)
);
HANDLEX WINAPI
xll_tai_change()
{
#pragma XLLEXPORT
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new change<>()).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}

static AddInX xai_tai_change_relative(
	FunctionX(XLL_HANDLEX XLL_UNCALCEDX, _T("?xll_tai_change_relative"), TAI_PREFIX _T("CHANGE.RELATIVE"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the relative change in Price."))
	.Documentation(
		_T("The <newTerm>relative change</newTerm> is the difference between the current price and the last price divided by the last price. ")
	)
);
HANDLEX WINAPI
xll_tai_change_relative()
{
#pragma XLLEXPORT
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new change_relative<>()).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}

static AddInX xai_tai_change_logarithmic(
	FunctionX(XLL_HANDLEX XLL_UNCALCEDX, _T("?xll_tai_change_logarithmic"), TAI_PREFIX _T("CHANGE.LOGARITHMIC"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the change in natuaral logarithm of Price."))
	.Documentation(
		_T("The <newTerm>logarithmic change</newTerm> is the difference between the logarithm of the current price and the logarithm of the last price. ")
	)
);
HANDLEX WINAPI
xll_tai_change_logarithmic()
{
#pragma XLLEXPORT
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new change_logarithmic<>()).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}
