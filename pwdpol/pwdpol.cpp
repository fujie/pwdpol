#include "stdafx.h"
#include <ntsecapi.h>
#include <regex>

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#endif

using namespace std;

// initialize
BOOLEAN NTAPI InitializeChangeNotify(void) {
	return TRUE;
}

// evaluate filter
BOOLEAN NTAPI PasswordFilter(
	PUNICODE_STRING AccountName,
	PUNICODE_STRING FullName,
	PUNICODE_STRING Password,
	BOOLEAN SetOperation) {

	BOOLEAN ret;

	// filter in regular expression
	const wchar_t* pattern = LR"([\"\',])";

	// convert PUNICODE_STRING to wstring
	std::wstring pwd(Password->Buffer, Password->Length / sizeof(WCHAR));
	
	// search filtered charactors
	regex_search(pwd, wregex(pattern)) ? ret = FALSE : ret = TRUE;

	// clear buffer
	SecureZeroMemory((PVOID)pwd.c_str(), pwd.size());

	return ret;
}

// notify change
NTSTATUS NTAPI PasswordChangeNotify(
	PUNICODE_STRING UserName,
	ULONG RelativeId,
	PUNICODE_STRING NewPassword) {

	// nop
	return STATUS_SUCCESS;
}