/*
 * numOfProcessors.c
 *
 *  Created on: Oct 24, 2011
 *      Author: Bob Kerr
 */
#ifdef WINDOWS
#include <windows.h>
#elif defined (LINUX)
#include <unistd.h>
#elif defined (MACOS)
#include <sys/param.h>
#include <sys/sysctl.h>
#endif
#include <stdint.h>

uint32_t numOfProcessors()
{
#ifdef WINDOWS
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	return sysinfo.dwNumberOfProcessors;
#elif defined (LINUX)
	return sysconf(_SC_NPROCESSORS_ONLN);
#elif defined (MACOS)
	int nm[2];
	size_t len = 4;
	uint32_t count;

	nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
	sysctl(nm, 2, &count, &len, NULL, 0);

	if(count < 1) {
		nm[1] = HW_NCPU;
		sysctl(nm, 2, &count, &len, NULL, 0);
		if(count < 1) {count = 1;}
	}
	return count;
#endif
}
