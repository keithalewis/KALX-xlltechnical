// xlltechnical.h - commone header for Excel add-in routines
#pragma once
//#define EXCEL12
#include "../xll12/xll/xll.h"

#ifndef CATEGORY
#define CATEGORY _T("Technical")
#endif

#undef _T
#define _T(x) L##x

#ifndef TA_PREFIX
#define TA_PREFIX _T("TA.")
#endif

#ifndef TAI_PREFIX
#define TAI_PREFIX _T("TAI.")
#endif

#ifndef RT_PREFIX
#define RT_PREFIX _T("RT.")
#endif

typedef const WCHAR* xcstr;
typedef _FP12 xfp;
typedef INT32 xword;

template<class F>
inline HANDLEX
xll_tai_()
{
	HANDLEX h;

	try {
		h = handle<indicator_base<>>(new F).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return h;
}
