/*
 * endianSwap.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#include "endianSwap.h"

#if defined (WINDOWS) || defined (MACOS)
    void endianSwap(uint16_t  & number) {
    	number = (number >> 8) |
    			(number << 8);
    }
    void endianSwap(uint32_t & number) {
    	number = (number >> 24) |
    			((number << 8) & 0x00FF0000) |
    			((number >> 8) & 0x0000FF00) |
    			(number << 24);
    }
    void endianSwap(uint64_t  & number) {
    	number = (number >> 56) |
    			((number << 40) & 0x00FF000000000000) |
    			((number << 24) & 0x0000FF0000000000) |
    			((number << 8) & 0x000000FF00000000) |
    			((number >> 8) & 0x00000000FF000000) |
    			((number >> 24) & 0x0000000000FF0000) |
    			((number >> 40) & 0x000000000000FF00) |
    			(number << 56);
    }
#elif defined LINUX
    //TODO: Use cpu_to_be32
#endif
