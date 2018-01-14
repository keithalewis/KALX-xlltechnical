// technical.cpp - technical analysis tools
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma warning(disable: 4996)
#include <algorithm>
#include "../fmstechnical/technical.h"
#include "xlltechnical.h"

#pragma warning(disable: 4389)

using namespace std;
using namespace xll;
using namespace technical;
/*
static AddInX xai_technical(
	DocumentX(CATEGORY)
	.Documentation(
		xml::Conceptual(
			_T("Various functions for performing calculations related to Technical Analysis. ")
		)
		.section(_T("Introduction")
			,
			_T("In finance, technical analysis is security analysis discipline for forecasting the direction ")
			_T("of prices through the study of past market data, primarily price and volume. ")
			_T("While fundamental analysts examine earnings, dividends, new products, research and the like, ")
			_T("technical analysts examine what investors fear or think about those developments and whether ")
			_T("or not investors have the wherewithal to back up their opinions; these two concepts are called ")
			_T("psych (psychology) and supply/demand. Technicians employ many techniques, one of which is the use ")
			_T("of charts. Using charts, technical analysts seek to identify price patterns and market trends in ")
			_T("financial markets and attempt to exploit those patterns.")
		)
		.section(_T("Overview")
			,
			_T("Technical <newTerm>indicators</newTerm> typically have parameters associated with them. For example, ")
			_T("a moving average specifies a period of time over which the average is computed. ")
			_T("Each indicator also has a <newTerm>state</newTerm> that contains information about prior calculations. ")
			_T("The indicator operates on data such as price and/or volume to produce numeric values. ")
			_T("</para><para>")
			_T("Functions starting with <codeInline>TAI.*</codeInline> create handles to indicators. The arguments ")
			_T("to these functions are the parameters associated with the indicator. ")
			_T("</para><para>")
			_T("The function <codeInline>TA.INDICATOR</codeInline> applies an indicator to static data in an array ")
			_T("The first argument is a handle to an indicator returned by a <codeInline>TAI.*</codeInline> function, ")
			_T("the second argument is an array of prices, and the third argument is the initial state of the indicator. ")
			_T("</para><para>")
			_T("The function <codeInline>TA.REALTIME</codeInline> applies the indicator to real-time data coming into the spreadsheet. ")
			_T("The first argument is a handle to an indicator returned by a <codeInline>TAI.*</codeInline> function, ")
			_T("the second argument is a reference to a cell being updated with real-time prices, and the third argument ")
			_T("resets the state of the indicator if it is not the empty array. Typically this argument takes the form ")
			_T("<codeInline>IF(condition, state, ARRAY.MAKE())</codeInline>. (The function <codeInline>ARRAY.MAKE()</codeInline> ")
			_T("returns an empty array.) ")
		)
	)
);
*/
//static Require(_T("xllarray"));

static AddInX xai_ta_indicator(
	FunctionX(XLL_FP, _T("?xll_ta_indicator"), TA_PREFIX _T("INDICATOR"))
	.Arg(XLL_HANDLE, _T("Handle"), _T("is a handle to the technical indicator to be calculated."))
	.Arg(XLL_FP, _T("Prices"), _T("is an array of price data."))
	.Arg(XLL_FP, _T("State"), _T("is the intial state of the indicator. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Applies the indicator to prices."))
	.Documentation(
		_T("The Handle must be returned by a <codeInline>TAI.*</codeInline> function. ")
		_T("The returned array has the same number of rows as the size of the <codeInline>Prices</codeInline> and ")
		_T("contains successive indicator values determined by previous values. ") 
		_T("If an indicator returns more than one value they are returned as columns. ")
	)
);
xfp* WINAPI
xll_ta_indicator(HANDLEX h, xfp* px, xfp* ps)
{
#pragma XLLEXPORT
	static xll::FP12 x;

	try {
		handle<indicator_base<>> h_(h);

		ensure (h_);
		ensure (h_->isize() == px->columns);

		if (size(*ps) && (size(*ps) == h_->size()))
			h_->state(ps->array);

		x.resize(px->rows, static_cast<xword>(h_->osize()));
		for (xword i = 0; i < px->rows; ++i) {
			double* py = h_->next(px->array + i*px->columns);
			std::copy(py, py + x.columns(), x.begin() + i*x.columns());
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return x.get();
}

static AddInX xai_ta_realtime(
	FunctionX(XLL_FP, _T("?xll_ta_realtime"), TA_PREFIX _T("REALTIME"))
	.Arg(XLL_HANDLE, _T("Handle"), _T("is a handle to the technical indicator to be calculated."))
	.Arg(XLL_FP, _T("Data"), _T("is a reference to real-time data."))
	.Arg(XLL_FP, _T("State"), _T("is the state of the indicator or the empty array. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Applies the indicator to Data."))
	.Documentation(
		_T("The Handle must be returned by a <codeInline>TAI.*</codeInline> function. ")
		_T("The indicator is updated in real-time as new Data arrives. ")
	)
);
xfp* WINAPI
xll_ta_realtime(HANDLEX h, xfp* px, xfp* ps)
{
#pragma XLLEXPORT
	static xll::FP12 x;

	try {
		handle<indicator_base<>> h_(h);

		ensure (h_);
		ensure (size(*px) == h_->isize());

		if (size(*ps) && size(*ps) == h_->size())
			h_->state(ps->array);

		double* y = h_->next(px->array);

		if (px->columns == 1)
			x.resize(static_cast<xword>(h_->osize()), 1);
		else
			x.resize(1, static_cast<xword>(h_->osize()));

		std::copy(y, y + x.size(), x.begin());
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return x.get();
}

#ifdef _DEBUG
#include <array>
#include "../fmstechnical/change.h"
#if 0
##include "../fmstechnical/tick.h"
#include "../fmstechnical/ewma.h"
#include "../fmstechnical/macd.h"
#include "../fmstechnical/relative_strength.h"
#endif
using namespace technical;

void
xll_test_change(void)
{
	std::array<double, 3> x = {1, 2, 3}, y;

	std::transform(x.begin(), x.end(), y.begin(), change<>());
}

#if 0
void
xll_test_tick(void)
{
	std::array<double,4> x = {0, 1, 1, 0}, y;

	std::transform(x.begin(), x.end(), y.begin(), tick_up<>());
	ensure (y[0] == 0);
	ensure (y[1] == 1);
	ensure (y[2] == 0);
	ensure (y[3] == 0);

	double x0 = 1.23;
	std::transform(x.begin(), x.end(), y.begin(), tick_down<>().state(&x0));
	ensure (y[0] == 1.23);
	ensure (y[1] == 0);
	ensure (y[2] == 0);
	ensure (y[3] == 1);
}

void
xll_test_ewma(void)
{
	std::array<double,3> x = {1, 2, 3}, y;
	double w = .5;

	std::transform(x.begin(), x.end(), y.begin(), ewma<>(w).state(&x[0]));
	ensure (y[0] == x[0]);
	ensure (y[1] == w*x[1] + (1 - w)*y[0]);
	ensure (y[2] == w*x[2] + (1 - w)*y[1]); 

}

void
xll_test_macd(void)
{
	std::array<double,3> x = {1, 2, 3}, y, y0, y1;
	double w0 = 0.9, w1 = 0.5;

	ewma<> a0(w0); a0.state(&x[0]);
	ewma<> a1(w1); a1.state(&x[0]);

	std::transform(x.begin(), x.end(), y.begin(), [&a0, &a1](double x) { return a0(x) - a1(x); } );
	std::transform(x.begin(), x.end(), y0.begin(), ewma<>(w0).state(&x[0]));
	std::transform(x.begin(), x.end(), y1.begin(), ewma<>(w1).state(&x[0]));

	for (size_t i = 0; i < x.size(); ++i)
		ensure (y[i] == y0[i] - y1[i]);

	macd<> d(w0, w1);
	d.state(x[0], x[0]);
	std::transform(x.begin(), x.end(), y0.begin(), d);
	for (size_t i = 0; i < x.size(); ++i)
		ensure (y[i] == y0[i]);
}
#endif
static_assert (sizeof(double) == sizeof(std::array<double,1>), "std::array is not well implemented");
int
xll_test_indicator(void)
{
	try {
		xll_test_change();
//		xll_test_tick();
//		xll_test_ewma();
//		xll_test_macd();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}
static Auto<Open> xao_test_indicator(xll_test_indicator);

#endif // _DEBUG