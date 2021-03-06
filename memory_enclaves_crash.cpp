/*
FOR EDUCATIONAL PURPOSE ONLY

author: @7eRoM
*/

#include "pch.h"
#include <windows.h>
#include <iostream>
#include <memory>
#include <processthreadsapi.h>
#include <enclaveapi.h>

int main()
{
	if (!IsEnclaveTypeSupported(ENCLAVE_TYPE_VBS)) {
		std::cout << "ENCLAVE_TYPE_VBS is not supported." << std::endl;
		getchar();
		return 1;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());

	ENCLAVE_CREATE_INFO_VBS enclave_create_info_vbs = { 0 };
	enclave_create_info_vbs.Flags = ENCLAVE_VBS_FLAG_DEBUG;
	LPVOID lpAddress = CreateEnclave(GetCurrentProcess(), nullptr, 2097152, 0, ENCLAVE_TYPE_VBS, &enclave_create_info_vbs, sizeof(ENCLAVE_CREATE_INFO_VBS), nullptr);
	if (lpAddress == nullptr) {
		std::cout << "CreateEnclave failed: " << GetLastError() << std::endl;
		getchar();
		return 1;
	}

	// Would be crashed after this call
	bool init = InitializeEnclave(hProcess, lpAddress, &enclave_create_info_vbs, sizeof(ENCLAVE_CREATE_INFO_VBS), nullptr);
	if (!init) {
		std::cout << "InitializeEnclave failed: " << GetLastError() << std::endl;
		getchar();
		return 1;
	}

	// Some other code

	return 0;
}