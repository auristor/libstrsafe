/*
 * Copyright (c) 2010, Jonas Sundberg <jsund@jsund.com>
 *
 * This software has been released under the terms of the ISC license. For
 * details, see the LICENSE file.
 */

#include "strsafe.h"
#include "../config.h"
#ifdef HAVE_STDIO_H
	#include <stdio.h>
#endif
#ifdef HAVE_STRING_H
	#include <string.h>
#endif
#ifdef HAVE_WCHAR_H
	#include <wchar.h>
#endif

HRESULT StringCchPrintfA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszFormat,
		__in	...){
	va_list argList;
	HRESULT result;
	
	va_start(argList, pszFormat);
	result = StringCchVPrintfA(pszDest, cchDest, pszFormat, argList);
	va_end(argList);

	return result;
}

HRESULT StringCchPrintfW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszFormat,
		__in	...){
	va_list argList;
	HRESULT result;

	va_start(argList, pszFormat);
	result = StringCchVPrintfW(pszDest, cchDest, pszFormat, argList);
	va_end(argList);

	return result;
}

HRESULT StringCchPrintfExA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__out	LPSTR * ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags,
		__in	LPCSTR pszFormat,
		__in	...){
	va_list argList;
	HRESULT result;

	va_start(argList, pszFormat);
	result = StringCchVPrintfExA(pszDest, cchDest, ppszDestEnd,
			pcchRemaining, dwFlags, pszFormat, argList);
	va_end(argList);

	return result;
}


HRESULT StringCchPrintfExW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__out	LPWSTR * ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags,
		__in	LPCWSTR pszFormat,
		__in	...){
	va_list argList;
	HRESULT result;

	va_start(argList, pszFormat);
	result = StringCchVPrintfExW(pszDest, cchDest, ppszDestEnd,
			pcchRemaining, dwFlags, pszFormat, argList);
	va_end(argList);

	return result;
}

HRESULT StringCbPrintfA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszFormat,
		__in	...){
	va_list argList;
	HRESULT result;
	
	va_start(argList, pszFormat);
	result = StringCbVPrintfA(pszDest, cbDest, pszFormat, argList);
	va_end(argList);

	return result;
}

HRESULT StringCbPrintfW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszFormat,
		__in	...){
	va_list argList;
	HRESULT result;

	va_start(argList, pszFormat);
	result = StringCbVPrintfW(pszDest, cbDest, pszFormat, argList);
	va_end(argList);

	return result;
}

HRESULT StringCbPrintfExA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__out	LPSTR * ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags,
		__in	LPCSTR pszFormat,
		__in	...){
	va_list argList;
	HRESULT result;

	va_start(argList, pszFormat);
	result = StringCbVPrintfExA(pszDest, cbDest, ppszDestEnd,
			pcbRemaining, dwFlags, pszFormat, argList);
	va_end(argList);

	return result;
}

HRESULT StringCbPrintfExW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__out	LPWSTR * ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags,
		__in	LPCWSTR pszFormat,
		__in	...){
	va_list argList;
	HRESULT result;

	va_start(argList, pszFormat);
	result = StringCbVPrintfExW(pszDest, cbDest, ppszDestEnd,
			pcbRemaining, dwFlags, pszFormat, argList);
	va_end(argList);

	return result;
}
