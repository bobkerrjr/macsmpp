/*
 * endianSwap.h
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#ifndef ENDIANSWAP_H_
#define ENDIANSWAP_H_
#include <stdint.h>

#if defined (WINDOWS) || defined (MACOS)
    void endianSwap(uint16_t &);
    void endianSwap(uint32_t &);
    void endianSwap(uint64_t &);
#elif defined LINUX
    //TODO: Use cpu_to_be32
#endif


#endif /* ENDIANSWAP_H_ */
