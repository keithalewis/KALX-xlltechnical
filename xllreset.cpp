// xllreset.cpp - Helper function for TA.REALTIME.
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xlltechnical.h"

using namespace xll;

static AddInX xai_tai_reset(
	FunctionX(XLL_FP, _T("?xll_tai_reset"), TAI_PREFIX _T("RESET"))
	.Arg(XLL_BOOL, _T("Condition"), _T("is a boolean indicating when reset a technical indicator."))
	.Arg(XLL_FP, _T("State"), _T("is the state array of the indicator to be reset. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Guard State based on Condition."))
	.Documentation(_T("This is equivalent to <codeInline>IF(Condition, Reset, ARRAY.MAKE())</codeInline>. "))
);
xfp* WINAPI
xll_tai_reset(BOOL b, xfp* reset)
{
#pragma XLLEXPORT
	static xll::FP12 empty;

	return b ? reset : empty.get();
}