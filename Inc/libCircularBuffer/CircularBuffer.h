#ifndef INCLUDED_LIBCIRCULARBUFFER_H
#define INCLUDED_LIBCIRCULARBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define LIBCB_SUCCESS           0
#define LIBCB_INVALIDPARAM      -1
#define LIBCB_BUFFERFULL        -2
#define LIBCB_BUFFEREMPTY       -3
#define LIBCB_BUFFEROVERFLOW    -4
#define LIBCB_BUFFERUNDERFLOW   -5
#define LIBCB_MUTEXERROR        -6

/// @brief this struct defines the initialization parameters
typedef struct 
{
    void *pBuffer;           // Pointer to the buffer
    uint32_t nBufferSize;    // Maximum bytes of the buffer
    int32_t(*pfnMutexInitialize)(uint32_t **pMutex); // Pointer to the mutex create function
    int32_t(*pfnMutexLock)(uint32_t *pMutex);   // Pointer to the mutex lock function
    int32_t(*pfnMutexRelease)(uint32_t *pMutex); // Pointer to the mutex unlock function
} CircularBufferInit;

/// @brief this structure defines the circular buffer
typedef struct
{
    CircularBufferInit init; // Initialization parameters
    uint32_t *pMutex;
    uint32_t nCount;   // Number of bytes in the buffer
    uint32_t nHead;    // Index of the first byte in the buffer
    uint32_t nTail;    // Index of the last byte in the buffer
} CircularBuffer;

/// @brief this function initializes the circular buffer
/// @param self pointer to the circular buffer
/// @param init initialize parameter of the circular buffer
/// @return 
int32_t circularBufferInitialize(CircularBuffer *self, CircularBufferInit init);

/// @brief this function removes all data from the circular buffer
/// @param self pointer to the circular buffer
/// @return 
int32_t circularBufferFlush(CircularBuffer *self);

/// @brief this function copy the data from the source to the circular buffer
/// @param self 
/// @param pSource 
/// @param nSourceSize 
/// @return 
int32_t circularBufferPush(CircularBuffer *self, void *pSource, uint32_t nSourceSize);

/// @brief this function copy the data from the circular buffer to the destination
/// @param self 
/// @param pDestination 
/// @param nDestinationSize 
/// @return 
int32_t circularBufferPop(CircularBuffer *self, void *pDestination, uint32_t nDestinationSize);

/// @brief this function checks if the circular buffer is empty
/// @param self
/// @return 
int32_t circularBufferIsEmpty(CircularBuffer *self);

/// @brief this function checks if the circular buffer is full
/// @param self
/// @return
int32_t circularBufferIsFull(CircularBuffer *self);

/// @brief this function returns the maximum number of bytes that can be stored in the circular buffer
/// @param self
/// @return
int32_t circularBufferGetCapacity(CircularBuffer *self);

/// @brief this function returns the number of bytes that are currently stored in the circular buffer
/// @param self
/// @return
int32_t circularBufferGetCount(CircularBuffer *self);

#ifdef __cplusplus
}
#endif

#endif // INCLUDED_LIBCIRCULARBUFFER_H