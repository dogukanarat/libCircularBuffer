#include <string.h>
#include "libCircularBuffer/CircularBuffer.h"

// Lock the mutex
static int32_t Lock(CircularBuffer *self);

// Release the mutex
static int32_t Release(CircularBuffer *self);

int32_t circularBufferInitialize(CircularBuffer *self, CircularBufferInit init)
{
    int32_t status = LIBCB_SUCCESS;

    for (;;)
    {
        if (self == NULL || init.nBufferSize == 0 || init.pBuffer == NULL)
        {
            status = LIBCB_INVALIDPARAM;
            break;
        }

        self->init = init;
        self->nCount = 0;
        self->nHead = 0;
        self->nTail = 0;
        self->pMutex = NULL;

        if (init.pfnMutexInitialize != NULL)
        {
            init.pfnMutexInitialize(&self->pMutex);
        }

        break;
    }

    return status;
}

int32_t circularBufferFlush(CircularBuffer *self)
{
    int32_t status = LIBCB_SUCCESS;

    for (;;)
    {
        if (self == NULL)
        {
            status = LIBCB_INVALIDPARAM;
            break;
        }

        self->nCount = 0;
        self->nHead = 0;
        self->nTail = 0;

        break;
    }

    return status;
}

int32_t circularBufferPush(CircularBuffer *self, void *pSource, uint32_t nSourceSize)
{
    int32_t status = LIBCB_SUCCESS;

    for (;;)
    {
        if (
            self == NULL || pSource == NULL ||
            nSourceSize == 0 || self->init.pBuffer == NULL ||
            self->init.nBufferSize == 0
            )
        {
            status = LIBCB_INVALIDPARAM;
            break;
        }

        if (self->init.nBufferSize < nSourceSize)
        {
            status = LIBCB_BUFFEROVERFLOW;
            break;
        }

        Lock(self);

        if (self->init.nBufferSize < (self->nCount + nSourceSize))
        {
            Release(self);
            status = LIBCB_BUFFEROVERFLOW;
            break;
        }

        if (self->nTail + nSourceSize > self->init.nBufferSize)
        {
            uint32_t nFirstCopySize = self->init.nBufferSize - self->nTail;
            uint32_t nSecondCopySize = nSourceSize - nFirstCopySize;

            memcpy((uint8_t *)self->init.pBuffer + self->nTail, pSource, nFirstCopySize);
            memcpy(self->init.pBuffer, (uint8_t *)pSource + nFirstCopySize, nSecondCopySize);
            self->nTail = nSecondCopySize;
        }
        else
        {
            memcpy((uint8_t *)self->init.pBuffer + self->nTail, pSource, nSourceSize);
            self->nTail += nSourceSize;
        }

        self->nCount += nSourceSize;

        Release(self);

        break;
    }

    return status;
}

int32_t circularBufferPop(CircularBuffer *self, void *pDestination, uint32_t nDestinationSize)
{
    int32_t status = LIBCB_SUCCESS;

    for (;;)
    {
        if (self == NULL || pDestination == NULL || nDestinationSize == 0)
        {
            status = LIBCB_INVALIDPARAM;
            break;
        }

        if (self->nCount == 0)
        {
            status = LIBCB_BUFFEREMPTY;
            break;
        }

        Lock(self);

        if (self->nCount < nDestinationSize)
        {
            Release(self);
            status = LIBCB_BUFFERUNDERFLOW;
            break;
        }

        if (self->nHead + nDestinationSize > self->init.nBufferSize)
        {
            uint32_t nFirstCopySize = self->init.nBufferSize - self->nHead;
            uint32_t nSecondCopySize = nDestinationSize - nFirstCopySize;

            memcpy(pDestination, (uint8_t *)self->init.pBuffer + self->nHead, nFirstCopySize);
            memcpy((uint8_t *)pDestination + nFirstCopySize, self->init.pBuffer, nSecondCopySize);
            self->nHead = nSecondCopySize;
        }
        else
        {
            memcpy(pDestination, (uint8_t *)self->init.pBuffer + self->nHead, nDestinationSize);
            self->nHead += nDestinationSize;
        }

        self->nCount -= nDestinationSize;

        Release(self);

        break;
    }

    return status;
}

int32_t Lock(CircularBuffer *self)
{
    int32_t status = LIBCB_SUCCESS;

    for (;;)
    {
        if (self == NULL)
        {
            status = LIBCB_INVALIDPARAM;
            break;
        }

        if (self->init.pfnMutexLock != NULL)
        {
            self->init.pfnMutexLock(self->pMutex);
        }

        break;
    }

    return status;
}

int32_t Release(CircularBuffer *self)
{
    int32_t status = LIBCB_SUCCESS;

    for (;;)
    {
        if (self == NULL)
        {
            status = LIBCB_INVALIDPARAM;
            break;
        }

        if (self->init.pfnMutexRelease != NULL)
        {
            self->init.pfnMutexRelease(self->pMutex);
        }

        break;
    }

    return status;
}

int32_t circularBufferIsEmpty(CircularBuffer *self)
{
    int32_t status = LIBCB_SUCCESS;

    for (;;)
    {
        if (self == NULL)
        {
            status = LIBCB_INVALIDPARAM;
            break;
        }

        if (self->nCount == 0)
        {
            status = TRUE;
            break;
        }

        status = FALSE;

        break;
    }

    return status;
}

int32_t circularBufferIsFull(CircularBuffer *self)
{
    int32_t status = LIBCB_SUCCESS;

    for (;;)
    {
        if (self == NULL)
        {
            status = LIBCB_INVALIDPARAM;
            break;
        }

        if (self->nCount == self->init.nBufferSize)
        {
            status = TRUE;
            break;
        }

        status = FALSE;

        break;
    }

    return status;
}

int32_t circularBufferGetCapacity(CircularBuffer *self)
{
    int32_t status = LIBCB_SUCCESS;

    for (;;)
    {
        if (self == NULL)
        {
            status = LIBCB_INVALIDPARAM;
            break;
        }

        status = self->init.nBufferSize;

        break;
    }

    return status;
}

int32_t circularBufferGetCount(CircularBuffer *self)
{
    int32_t status = LIBCB_SUCCESS;

    for (;;)
    {
        if (self == NULL)
        {
            status = LIBCB_INVALIDPARAM;
            break;
        }

        status = self->nCount;

        break;
    }

    return status;
}