// xllmoments.cpp - moments from previous value
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "../fmstechnical/moments.h"
#include "xlltechnical.h"

using namespace technical;
using namespace xll;

static AddInX xai_tai_moments(
	FunctionX(XLL_HANDLEX XLL_UNCALCEDX, _T("?xll_tai_moments"), TAI_PREFIX _T("MOMENTS"))
	.Arg(XLL_WORDX, _T("Order"), _T("is the highest degree moment to compute. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to the moments indicator."))
	.Documentation(
		_T("This indicator has one parameter, the highest degree moment to calculate, <math>k</math>, ")
		_T("and the state is the number of terms computed and the running moments: ")
		_T("<math>n</math>, <math>") ENT_Sigma _T("<subscript>i</subscript> x<subscript>i</subscript>/n</math>, ")
		_T("<math>") ENT_Sigma _T("<subscript>i</subscript> x<subscript>i</subscript><superscript>2</superscript>/n</math>,..., ")
		_T("<math>") ENT_Sigma _T("<subscript>i</subscript> x<subscript>i</subscript><superscript>k</superscript>/n</math>. ")
	)
);
HANDLEX WINAPI
xll_tai_moments(WORD n)
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<indicator_base<>> h_(new moments<>(n));
		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}


static AddInX xai_tai_moments_central(
	FunctionX(XLL_FPX, _T("?xll_tai_moments_central"), TAI_PREFIX _T("MOMENTS.CENTRAL"))
	.Arg(XLL_FPX, _T("Moments"), _T("the non central moments of a distribution. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the corresponding central moments."))
	.Documentation(
		_T("Note this does not take the output of <codeInline>") TAI_PREFIX _T("MOMENTS</codeInline>. ")
		_T("Drop the first value containing the count before calling this function. ")
	)
);
xfp* WINAPI
xll_tai_moments_central(xfp* px)
{
#pragma XLLEXPORT
	static FPX x;

	x.reshape(px->rows, px->columns);
	central(size(*px), px->array, x.begin());

	return x.get();
}
