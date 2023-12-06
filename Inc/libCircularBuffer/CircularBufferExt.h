#ifndef INCLUDED_LIBCIRCULARBUFFEREXT_H
#define INCLUDED_LIBCIRCULARBUFFEREXT_H

#include "CircularBuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief this function reads data with the count of nCount 
///        from the circular buffer starting from the specified 
///        offset nStartOffset
/// @param self pointer to the circular buffer
/// @param pBuffer pointer to the buffer
/// @param pDestination pointer to the destination buffer
/// @param nDestinationSize size of the destination buffer
/// @param nStartOffset offset of the start position
/// @param nCount number of bytes to read
/// @return
int32_t circularBufferRead(
    CircularBuffer *self,
    void *pDestination,
    uint32_t nDestinationSize,
    uint32_t nStartOffset,
    uint32_t nCount
);

#ifdef __cplusplus
}
#endif

#endif