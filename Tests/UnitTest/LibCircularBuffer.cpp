#include "gtest/gtest.h"
#include "libCircularBuffer/CircularBuffer.h"

TEST(CircularBuffer, TestInitialize)
{
    int32_t status;
    uint8_t buffer[100];
    uint32_t bufferSize = 100;
    CircularBufferInit cbInit;
    CircularBuffer cb;

    cbInit.pBuffer = buffer;
    cbInit.nBufferSize = bufferSize;
    cbInit.pfnMutexInitialize = NULL;
    cbInit.pfnMutexLock = NULL;
    cbInit.pfnMutexRelease = NULL;

    status = circularBufferInitialize(&cb, cbInit);

    EXPECT_EQ(status, 0);

    EXPECT_EQ(cb.init.nBufferSize, bufferSize);
    EXPECT_EQ(cb.init.pBuffer, buffer);
    EXPECT_FALSE(cb.init.pfnMutexInitialize);
    EXPECT_FALSE(cb.pMutex);
}

TEST(CircularBuffer, TestPush)
{
    int32_t status;
    uint8_t buffer[100];
    uint32_t bufferSize = 100;
    CircularBufferInit cbInit;
    CircularBuffer cb;

    cbInit.pBuffer = buffer;
    cbInit.nBufferSize = bufferSize;
    cbInit.pfnMutexInitialize = NULL;
    cbInit.pfnMutexLock = NULL;
    cbInit.pfnMutexRelease = NULL;

    status = circularBufferInitialize(&cb, cbInit);

    EXPECT_EQ(status, 0);

    uint8_t data = 0x55;
    status = circularBufferPush(&cb, &data, 1);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(cb.nCount, 1);
    EXPECT_EQ(cb.nHead, 1);
    EXPECT_EQ(cb.nTail, 0);

    uint8_t compareData = ((uint8_t*)cb.init.pBuffer)[0];
    EXPECT_EQ(compareData, data);
}