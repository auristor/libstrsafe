/*
 * Copyright (c) 2010, Jonas Sundberg <jsund@jsund.com>
 *
 * This software has been released under the terms of the ISC license. For
 * details, see the LICENSE file.
 */

/**
 * @file strsafe.h
 *
 * Provides the public interface to the libstrsafe functions.
 *
 * For more information on libstrsafe, see the README file.
 */

#ifndef STRSAFE_H
#define STRSAFE_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/* Enable both versions of the UNICODE macro. */

#ifdef _UNICODE
	#ifndef UNICODE
		#define UNICODE
	#endif
#endif

#ifdef UNICODE
	#ifndef _UNICODE
		#define _UNICODE
	#endif
#endif

/**
 * The result of a function call. All function calls in libstrsafe returns
 * an HRESULT, a value representing the result of the function call.
 * This can later be checked with the SUCCEEDED or FAILED macros.
 */
#define HRESULT uint32_t

/*
 * Bits set in a HRESULT correspond to various error messages.
 */
#define S_OK (uint32_t)0x00000000
#define STRSAFE_E_END_OF_FILE (uint32_t)0x00000001
#define STRSAFE_E_INVALID_PARAMETER (uint32_t)0x00000002
#define STRSAFE_E_INSUFFICIENT_BUFFER (uint32_t)0x00000004

/*
 * Flags to set in parameters to the extended functions.
 */
#define STRSAFE_IGNORE_NULLS (uint32_t)0x00000100
#define STRSAFE_FILL_BEHIND_NULL (uint32_t)0x00000200
#define STRSAFE_FILL_ON_FAILURE (uint32_t)0x00000400
#define STRSAFE_NULL_ON_FAILURE (uint32_t)0x00000800
#define STRSAFE_NO_TRUNCATION (uint32_t)0x00001000

/*
 * The maximum number of characters allowed.
 */
#define STRSAFE_MAX_CCH 0x7fffffff /* 2^31 - 1 or 2,147,483,647 */

/**
 * Checks that the previous call succeeded. This is implemented as a macro
 * that checks the data returned by a previous function call.
 *
 * @param result The result to check.
 *
 * @return True if the result contained no errors and false otherwise.
 */
#define SUCCEEDED(result) ((result) == S_OK)

/**
 * Checks that the previous call failed. This is implemented as a macro
 * that checks the data returned by a previous function call. 
 *
 * @param result The result to check.
 *
 * @return True if the result contained errors and false otherwise.
 */
#define FAILED(result) ((result) != S_OK)

/*
 * __out, __in and __inout marks whether a parameter to a function call
 * is used for output, input or both input and output, respectively.
 */
#define __out
#define __in
#define __inout

/*
 * A DWORD is used to set various arguments to extended versions of
 * functions.
 */
#define DWORD uint32_t

/**
 * A single character.
 */
#ifdef UNICODE
	#define TCHAR wchar_t
#else
	#define TCHAR char
#endif

/**
 * A pointer to a string buffer.
 */
#define LPTSTR TCHAR *
#define LPWSTR wchar_t *
#define LPSTR char *

/**
 * A pointer to an immutable string buffer.
 */
#define LPCTSTR const TCHAR *
#define LPCWSTR const wchar_t *
#define LPCSTR const char *

/**
 * A macro that converts string literals to either C strings or Unicode
 * strings depending on whether UNICODE is set or not.
 */
#ifdef UNICODE
	#define TEXT(string) L##string
#else
	#define TEXT(string) string
#endif

/**
 * Concatenates the strings in pszDest and pszSrc and stores the result
 * in pszDest. If the concatenated string does not fit into pszDest, the
 * string is truncated and null terminated.
 *
 * Running time is linear in the length of the strings pszSrc and pszDest
 * or the value of cchDest, whichever is lower.
 *
 * @param pszDest The first part of the concatenated string as well as the
 *                destination of the concatenated string.
 * @param cchDest Capacity of pszDest in number of characters.
 * @param pszSrc The second part of the concatenated string that is to be
 *               appended to pszDest.
 *
 * @return A HRESULT that should be checked with the SUCCEEDED or FAILED
 *         macros after use.
 *
 *         Returns S_OK if the concatenation was successful.
 *
 *         Returns STRSAFE_E_INVALID_PARAMETER if the capacity cbDest
 *         is zero, larger than the maximum capacity allowed or if
 *         a null termination is not found in pszDest.
 *
 *         Returns STRSAFE_E_INSUFFICIENT_BUFFER if the data in pszSrc
 *         did not fint into the remaining part of pszDst. The data from
 *         pszSrc has been truncated to fit in the remaining part of
 *         pszDst and this truncated data has been null terminated and
 *         written after the current data in pszDst.
 */
#ifdef UNICODE
	#define StringCchCat StringCchCatW
#else
	#define StringCchCat StringCchCatA
#endif
HRESULT StringCchCatA(
	__inout	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszSrc
);
HRESULT StringCchCatW(
	__inout LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszSrc
);

/* TODO: Documentation of StringCchCatEx. */
#ifdef UNICODE
	#define StringCchCatEx StringCchCatExW
#else
	#define StringCchCatEx StringCchCatExA
#endif
HRESULT StringCchCatExA(
	__inout	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszSrc,
	__out	LPSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags
);
HRESULT StringCchCatExW(
	__inout	LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszSrc,
	__out	LPWSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags
);

/* TODO: Documentation of StringCchCatN. */
#ifdef UNICODE
	#define StringCchCatN StringCchCatNW
#else
	#define StringCchCatN StringCchCatNA
#endif
HRESULT StringCchCatNA(
	__inout	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszSrc,
	__in	size_t cchMaxAppend
);
HRESULT StringCchCatNW(
	__inout LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszSrc,
	__in	size_t cchMaxAppend
);

/* TODO: Documentation of StringCchCatNEx. */
#ifdef UNICODE
	#define StringCchCatNEx StringCchCatNExW
#else
	#define StringCchCatNEx StringCchCatNExA
#endif
HRESULT StringCchCatNExA(
	__inout	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszSrc,
	__in	size_t cchMaxAppend,
	__out	LPSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags
);
HRESULT StringCchCatNExW(
	__inout	LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszSrc,
	__in	size_t cchMaxAppend,
	__out	LPWSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags
);

/**
 * Copies the content of pszSrc into pszDest until a null character is
 * found. StringCchCopy assures that the string is null terminated.
 * If the data in pszSrc does not fit into pszDest, the string is
 * truncated and null terminated.
 *
 * Running time is linear in the length of pszSrc or the value of cchDest,
 * whichever is lower.
 *
 * @param pszDest The destination of the copy.
 * @param cchDest Capacity of pszDest in number of characters.
 * @param pszSrc The source to copy data from.
 *
 * @return A HRESULT that should be checked with the SUCCEEDED or FAILED
 *         macros after use.
 *
 *         Returns S_OK if the copy was successful.
 *
 *         Returns STRSAFE_E_INVALID_PARAMETER if the capacity cchDest
 *         is zero or larger than the maximum capacity allowed.
 *
 *         Returns STRSAFE_E_INSUFFICIENT_BUFFER if the data in pszSrc did
 *         not fit into pszDst. The data from pszSrc has been truncated
 *         to fit in pszDst and this truncated data has been null terminated
 *         and written into pszDst.
 */
#ifdef UNICODE
	#define StringCchCopy StringCchCopyW
#else
	#define StringCchCopy StringCchCopyA
#endif
HRESULT StringCchCopyA(
	__out	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszSrc
);
HRESULT StringCchCopyW(
	__out	LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszSrc
);

/* TODO: Documentation of StringCchCopyEx. */
#ifdef UNICODE
	#define StringCchCopyEx StringCchCopyExW
#else
	#define StringCchCopyEx StringCchCopyExA
#endif
HRESULT StringCchCopyExA(
	__inout	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszSrc,
	__out	LPSTR *ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags
);
HRESULT StringCchCopyExW(
	__inout	LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszSrc,
	__out	LPWSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags
);

/* TODO: Documentation of StringCchCopyN. */
#ifdef UNICODE
	#define StringCchCopyN StringCchCopyNW
#else
	#define StringCchCopyN StringCchCopyNA
#endif
HRESULT StringCchCopyNA(
	__inout	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszSrc,
	__in	size_t cchSrc
);
HRESULT StringCchCopyNW(
	__inout LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszSrc,
	__in	size_t cchSrc
);

/* TODO: Documentation of StringCchCopyNEx. */
#ifdef UNICODE
	#define StringCchCopyNEx StringCchCopyNExW
#else
	#define StringCchCopyNEx StringCchCopyNExA
#endif
HRESULT StringCchCopyNExA(
	__inout	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszSrc,
	__in	size_t cchSrc,
	__out	LPSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags
);
HRESULT StringCchCopyNExW(
	__inout	LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszSrc,
	__in	size_t cchSrc,
	__out	LPWSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags
);

/* TODO: Documentation of StringCchGets. */
#ifdef UNICODE
	#define StringCchGets StringCchGetsW
#else
	#define StringCchGets StringCchGetsA
#endif
HRESULT StringCchGetsA(
	__out	LPSTR pszDest,
	__in	size_t cchDest
);
HRESULT StringCchGetsW(
	__out	LPWSTR pszDest,
	__in	size_t cchDest
);

/* TODO: Documentation of StringCchGetsEx. */
#ifdef UNICODE
	#define StringCchGetsEx StringCchGetsExW
#else
	#define StringCchGetsEx StringCchGetsExA
#endif
HRESULT StringCchGetsExA(
	__out	LPSTR pszDest,
	__in	size_t cchDest,
	__out 	LPSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags
);
HRESULT StringCchGetsExW(
	__out	LPWSTR pszDest,
	__in	size_t cchDest,
	__out 	LPWSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags
);

/* TODO: Documentation of StringCchPrintf. */
#ifdef UNICODE
	#define StringCchPrintf StringCchPrintfW
#else
	#define StringCchPrintf StringCchPrintfA
#endif
HRESULT StringCchPrintfA(
	__out	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszFormat,
	__in	...
);
HRESULT StringCchPrintfW(
	__out	LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszFormat,
	__in	...
);

/* TODO: Documentation of StringCchPrintfEx. */
#ifdef UNICODE
	#define StringCchPrintfEx StringCchPrintfExW
#else
	#define StringCchPrintfEx StringCchPrintfExA
#endif
HRESULT StringCchPrintfExA(
	__out	LPSTR pszDest,
	__in	size_t cchDest,
	__out	LPSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags,
	__in	LPCSTR pszFormat,
	__in	...
);
HRESULT StringCchPrintfExW(
	__out	LPWSTR pszDest,
	__in	size_t cchDest,
	__out	LPWSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags,
	__in	LPCWSTR pszFormat,
	__in	...
);

/* TODO: Documentation of StringCchVPrintf. */
#ifdef UNICODE
	#define StringCchVPrintf StringCchVPrintfW
#else
	#define StringCchVPrintf StringCchVPrintfA
#endif
HRESULT StringCchVPrintfA(
	__out	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszFormat,
	__in	va_list argList
);
HRESULT StringCchVPrintfW(
	__out	LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszFormat,
	__in	va_list argList
);

/* TODO: Documentation of StringCchVPrintfEx. */
#ifdef UNICODE
	#define StringCchPrintExf StringCchVPrintfExW
#else
	#define StringCchPrintExf StringCchVPrintfExA
#endif
HRESULT StringCchVPrintfExA(
	__out	LPSTR pszDest,
	__in	size_t cchDest,
	__out	LPSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags,
	__in	LPCSTR pszFormat,
	__in	va_list argList
);
HRESULT StringCchVPrintfExW(
	__out	LPWSTR pszDest,
	__in	size_t cchDest,
	__out	LPWSTR * ppszDestEnd,
	__out	size_t * pcchRemaining,
	__in	DWORD dwFlags,
	__in	LPCWSTR pszFormat,
	__in	va_list argList
);

/**
 * Calculates the length of psz by iterating over it until a null character
 * is reached. The null character is not counted as part of the string.
 *
 * Running time is linear in the length of the string.
 *
 * @param psz The string to calculate the length for.
 * @param cchMax Capacity of psz in number of characters.
 * @param pcch The calculated length. The calculated value is undefined if
 *             the function failed.
 *
 * @return A HRESULT that should be checked with the SUCCEEDED or FAILED
 *         macros after use.
 *
 *         Returns S_OK if the length was calculated correctly.
 *
 *         Returns STRSAFE_E_INVALID_PARAMETER if the capacity cbMax
 *         is larger than the maximum capacity allowed or if a null
 *         termination is not found in psz.
 */
#ifdef UNICODE
	#define StringCchLength StringCchLengthW
#else
	#define StringCchLength StringCchLengthA
#endif
HRESULT StringCchLengthA(
	__in	LPCSTR psz,
	__in	size_t cchMax,
	__out	size_t * pcch
);
HRESULT StringCchLengthW(
	__in	LPCWSTR psz,
	__in	size_t cchMax,
	__out	size_t * pcch
);

/**
 * Concatenates the strings in pszDest and pszSrc and stores the result
 * in pszDest. If the concatenated string does not fit into pszDest, the
 * string is truncated and null terminated.
 *
 * Running time is linear in the length of the strings pszSrc and pszDest
 * or the value of cbDest, whichever is lower.
 *
 * @param pszDest The first part of the concatenated string as well as the
 *                destination of the concatenated string.
 * @param cbDest Capacity of pszDest in bytes.
 * @param pszSrc The second part of the concatenated string that is to be
 *               appended to pszDest.
 *
 * @return A HRESULT that should be checked with the SUCCEEDED or FAILED
 *         macros after use.
 *
 *         Returns S_OK if the concatenation was successful.
 *
 *         Returns STRSAFE_E_INVALID_PARAMETER if the capacity cbDest
 *         is zero, larger than the maximum capacity allowed or if
 *         a null termination is not found in pszDest.
 *
 *         Returns STRSAFE_E_INSUFFICIENT_BUFFER if the data in pszSrc
 *         did not fint into the remaining part of pszDst. The data from
 *         pszSrc has been truncated to fit in the remaining part of
 *         pszDst and this truncated data has been null terminated and
 *         written after the current data in pszDst.
 */
#ifdef UNICODE
	#define StringCbCat StringCbCatW
#else
	#define StringCbCat StringCbCatA
#endif
HRESULT StringCbCatA(
	__inout	LPSTR pszDest,
	__in	size_t cbDest,
	__in	LPCSTR pszSrc
);
HRESULT StringCbCatW(
	__inout	LPWSTR pszDest,
	__in	size_t cbDest,
	__in	LPCWSTR pszSrc
);

/* TODO: Documentation of StringCbCatEx. */
#ifdef UNICODE
	#define StringCbCatEx StringCbCatExW
#else
	#define StringCbCatEx StringCbCatExA
#endif
HRESULT StringCbCatExA(
	__inout	LPSTR pszDest,
	__in	size_t cbDest,
	__in	LPCSTR pszSrc,
	__out	LPSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags
);
HRESULT StringCbCatExW(
	__inout	LPWSTR pszDest,
	__in	size_t cbDest,
	__in	LPCWSTR pszSrc,
	__out	LPWSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags
);

/* TODO: Documentation of StringCbCatN. */
#ifdef UNICODE
	#define StringCbCatN StringCbCatNW
#else
	#define StringCbCatN StringCbCatNA
#endif
HRESULT StringCbCatNA(
	__inout	LPSTR pszDest,
	__in	size_t cbDest,
	__in	LPCSTR pszSrc,
	__in	size_t cbMaxAppend
);
HRESULT StringCbCatNW(
	__inout LPWSTR pszDest,
	__in	size_t cbDest,
	__in	LPCWSTR pszSrc,
	__in	size_t cbMaxAppend
);

/* TODO: Documentation of StringCbCatNEx. */
#ifdef UNICODE
	#define StringCbCatNEx StringCbCatNExW
#else
	#define StringCbCatNEx StringCbCatNExA
#endif
HRESULT StringCbCatNExA(
	__inout	LPSTR pszDest,
	__in	size_t cbDest,
	__in	LPCSTR pszSrc,
	__in	size_t cbMaxAppend,
	__out	LPSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags
);
HRESULT StringCbCatNExW(
	__inout	LPWSTR pszDest,
	__in	size_t cbDest,
	__in	LPCWSTR pszSrc,
	__in	size_t cbMaxAppend,
	__out	LPWSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags
);

/**
 * Copies the content of pszSrc into pszDest until a null byte is found.
 * StringCbCopy assures that the string is null terminated. If the data in
 * pszSrc does not fit into pszDest, the string is truncated and null
 * terminated.
 *
 * Running time is linear in the length of pszSrc or the value of cbDest,
 * whichever is lower.
 *
 * @param pszDest The destination of the copy.
 * @param cbDest Capacity of pszDest in bytes.
 * @param pszSrc The source to copy data from.
 *
 * @return A HRESULT that should be checked with the SUCCEEDED or FAILED
 *         macros after use.
 *
 *         Returns S_OK if the copy was successful.
 *
 *         Returns STRSAFE_E_INVALID_PARAMETER if the capacity cbDest
 *         is zero or larger than the maximum capacity allowed.
 *
 *         Returns STRSAFE_E_INSUFFICIENT_BUFFER if the data in pszSrc did
 *         not fit into pszDst. The data from pszSrc has been truncated
 *         to fit in pszDst and this truncated data has been null terminated
 *         and written into pszDst.
 */
#ifdef UNICODE
	#define StringCbCopy StringCbCopyW
#else
	#define StringCbCopy StringCbCopyA
#endif
HRESULT StringCbCopyA(
	__out	LPSTR pszDest,
	__in	size_t cbDest,
	__in	LPCSTR pszSrc
);
HRESULT StringCbCopyW(
	__out	LPWSTR pszDest,
	__in	size_t cbDest,
	__in	LPCWSTR pszSrc
);

/* TODO: Documentation of StringCbCopyEx. */
#ifdef UNICODE
	#define StringCbCopyEx StringCbCopyExW
#else
	#define StringCbCopyEx StringCbCopyExA
#endif
HRESULT StringCbCopyExA(
	__inout	LPSTR pszDest,
	__in	size_t cbDest,
	__in	LPCSTR pszSrc,
	__out	LPSTR *ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags
);
HRESULT StringCbCopyExW(
	__inout	LPWSTR pszDest,
	__in	size_t cbDest,
	__in	LPCWSTR pszSrc,
	__out	LPWSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags
);

/* TODO: Documentation of StringCbCopyN. */
#ifdef UNICODE
	#define StringCbCopyN StringCbCopyNW
#else
	#define StringCbCopyN StringCbCopyNA
#endif
HRESULT StringCbCopyNA(
	__inout	LPSTR pszDest,
	__in	size_t cbDest,
	__in	LPCSTR pszSrc,
	__in	size_t cbSrc
);
HRESULT StringCbCopyNW(
	__inout LPWSTR pszDest,
	__in	size_t cbDest,
	__in	LPCWSTR pszSrc,
	__in	size_t cbSrc
);

/* TODO: Documentation of StringCbCopyNEx. */
#ifdef UNICODE
	#define StringCbCopyNEx StringCbCopyNExW
#else
	#define StringCbCopyNEx StringCbCopyNExA
#endif
HRESULT StringCbCopyNExA(
	__inout	LPSTR pszDest,
	__in	size_t cbDest,
	__in	LPCSTR pszSrc,
	__in	size_t cbSrc,
	__out	LPSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags
);
HRESULT StringCbCopyNExW(
	__inout	LPWSTR pszDest,
	__in	size_t cbDest,
	__in	LPCWSTR pszSrc,
	__in	size_t cbSrc,
	__out	LPWSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags
);

/* TODO: Documentation of StringCbGets. */
#ifdef UNICODE
	#define StringCbGets StringCbGetsW
#else
	#define StringCbGets StringCbGetsA
#endif
HRESULT StringCbGetsA(
	__out	LPSTR pszDest,
	__in	size_t cbDest
);
HRESULT StringCbGetsW(
	__out	LPWSTR pszDest,
	__in	size_t cbDest
);

/* TODO: Documentation of StringCbGetsEx. */
#ifdef UNICODE
	#define StringCbGetsEx StringCbGetsExW
#else
	#define StringCbGetsEx StringCbGetsExA
#endif
HRESULT StringCbGetsExA(
	__out	LPSTR pszDest,
	__in	size_t cbDest,
	__out 	LPSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags
);
HRESULT StringCbGetsExW(
	__out	LPWSTR pszDest,
	__in	size_t cbDest,
	__out 	LPWSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags
);

/* TODO: Documentation of StringCbPrintf. */
#ifdef UNICODE
	#define StringCbPrintf StringCbPrintfW
#else
	#define StringCbPrintf StringCbPrintfA
#endif
HRESULT StringCbPrintfA(
	__out	LPSTR pszDest,
	__in	size_t cbDest,
	__in	LPCSTR pszFormat,
	__in	...
);
HRESULT StringCbPrintfW(
	__out	LPWSTR pszDest,
	__in	size_t cbDest,
	__in	LPCWSTR pszFormat,
	__in	...
);

/* TODO: Documentation of StringCbPrintfEx. */
#ifdef UNICODE
	#define StringCbPrintfEx StringCbPrintfExW
#else
	#define StringCbPrintfEx StringCbPrintfExA
#endif
HRESULT StringCbPrintfExA(
	__out	LPSTR pszDest,
	__in	size_t cbDest,
	__out	LPSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags,
	__in	LPCSTR pszFormat,
	__in	...
);
HRESULT StringCbPrintfExW(
	__out	LPWSTR pszDest,
	__in	size_t cbDest,
	__out	LPWSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags,
	__in	LPCWSTR pszFormat,
	__in	...
);

/* TODO: Documentation of StringCbVPrintf. */
#ifdef UNICODE
	#define StringCbVPrintf StringCbVPrintfW
#else
	#define StringCbVPrintf StringCbVPrintfA
#endif
HRESULT StringCbVPrintfA(
	__out	LPSTR pszDest,
	__in	size_t cbDest,
	__in	LPCSTR pszFormat,
	__in	va_list argList
);
HRESULT StringCbVPrintfW(
	__out	LPWSTR pszDest,
	__in	size_t cbDest,
	__in	LPCWSTR pszFormat,
	__in	va_list argList
);

/* TODO: Documentation of StringCbVPrintfEx. */
#ifdef UNICODE
	#define StringCbPrintExf StringCbVPrintfExW
#else
	#define StringCbPrintExf StringCbVPrintfExA
#endif
HRESULT StringCbVPrintfExA(
	__out	LPSTR pszDest,
	__in	size_t cbDest,
	__out	LPSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags,
	__in	LPCSTR pszFormat,
	__in	va_list argList
);
HRESULT StringCbVPrintfExW(
	__out	LPWSTR pszDest,
	__in	size_t cbDest,
	__out	LPWSTR * ppszDestEnd,
	__out	size_t * pcbRemaining,
	__in	DWORD dwFlags,
	__in	LPCWSTR pszFormat,
	__in	va_list argList
);

/**
 * Calculates the length of psz by iterating over it until a null character
 * is reached. The null character is not counted as part of the string.
 *
 * Running time is linear in the length of the string.
 *
 * @param psz The string to calculate the length for.
 * @param cbMax Capacity of psz in bytes.
 * @param pcb The calculated length. The calculated value is undefined if
 *            the function failed.
 *
 * @return A HRESULT that should be checked with the SUCCEEDED or FAILED
 *         macros after use.
 *
 *         Returns S_OK if the length was calculated correctly.
 *
 *         Returns STRSAFE_E_INVALID_PARAMETER if the capacity cbMax
 *         is larger than the maximum capacity allowed or if a null
 *         termination is not found in psz.
 */
#ifdef UNICODE
	#define StringCbLength StringCbLengthW
#else
	#define StringCbLength StringCbLengthA
#endif
HRESULT StringCbLengthA(
	__in	LPCSTR psz,
	__in	size_t cbMax,
	__out	size_t *pcb
);
HRESULT StringCbLengthW(
	__in	LPCWSTR psz,
	__in	size_t cbMax,
	__out	size_t *pcb
);

#endif /* STRSAFE_H */
