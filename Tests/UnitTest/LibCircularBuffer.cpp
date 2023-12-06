#include "gtest/gtest.h"
#include "libCircularBuffer/CircularBuffer.h"

TEST(CircularBuffer, TestInitialize)
{
    // create an circular buffer and check if the initialization is correct

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

    EXPECT_EQ(status, LIBCB_SUCCESS);

    EXPECT_EQ(cb.init.nBufferSize, bufferSize);
    EXPECT_EQ(cb.init.pBuffer, buffer);
    EXPECT_FALSE(cb.init.pfnMutexInitialize);
    EXPECT_FALSE(cb.pMutex);
}

TEST(CircularBuffer, TestPushSingleItem)
{
    // create an circular buffer and push a single item to it
    // check if the push operation is successful and the buffer is not empty

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

    EXPECT_EQ(status, LIBCB_SUCCESS);

    uint8_t data = 0x55;
    status = circularBufferPush(&cb, &data, 1);

    EXPECT_EQ(status, LIBCB_SUCCESS);
    EXPECT_EQ(cb.nCount, 1);
    EXPECT_EQ(cb.nHead, 0);
    EXPECT_EQ(cb.nTail, 1);

    uint8_t compareData = ((uint8_t *)cb.init.pBuffer)[0];
    EXPECT_EQ(compareData, data);
}

TEST(CircularBuffer, TestPushMultipleItem)
{
    // create an circular buffer and push multiple items to it
    // check if the push operation is successful and the buffer is not empty

    uint8_t data, compareData;
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

    EXPECT_EQ(status, LIBCB_SUCCESS);

    data = 0x55;
    status = circularBufferPush(&cb, &data, 1);

    EXPECT_EQ(status, LIBCB_SUCCESS);
    EXPECT_EQ(cb.nCount, 1);
    EXPECT_EQ(cb.nHead, 0);
    EXPECT_EQ(cb.nTail, 1);

    compareData = ((uint8_t *)cb.init.pBuffer)[0];
    EXPECT_EQ(compareData, data);

    data = 0x66;
    status = circularBufferPush(&cb, &data, 1);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(cb.nCount, 2);
    EXPECT_EQ(cb.nHead, 0);
    EXPECT_EQ(cb.nTail, 2);

    compareData = ((uint8_t *)cb.init.pBuffer)[1];
    EXPECT_EQ(compareData, data);
}

TEST(CircularBuffer, TestFillBufferCompletely)
{
    // create an circular buffer and push the data with the size of the buffer
    // the buffer should be full after the push

    int32_t status;
    uint8_t buffer[100], dataToPush[100], dataToCompare;
    uint32_t bufferSize = 100, dataToPushSize = 100;
    CircularBufferInit cbInit;
    CircularBuffer cb;

    cbInit.pBuffer = buffer;
    cbInit.nBufferSize = bufferSize;
    cbInit.pfnMutexInitialize = NULL;
    cbInit.pfnMutexLock = NULL;
    cbInit.pfnMutexRelease = NULL;

    status = circularBufferInitialize(&cb, cbInit);

    EXPECT_EQ(status, LIBCB_SUCCESS);

    // fill dataToPush with indexes

    for (uint32_t i = 0; i < dataToPushSize; i++)
    {
        dataToPush[i] = i;
    }

    status = circularBufferPush(&cb, dataToPush, dataToPushSize);

    EXPECT_EQ(status, LIBCB_SUCCESS);
    EXPECT_EQ(cb.nCount, dataToPushSize);
    EXPECT_EQ(cb.nHead, 0);
    EXPECT_EQ(cb.nTail, dataToPushSize);

    // pop the data from the buffer and compare it one by one

    for (uint32_t i = 0; i < dataToPushSize; i++)
    {
        status = circularBufferPop(&cb, &dataToCompare, 1);
        EXPECT_EQ(status, 0);
        EXPECT_EQ(dataToCompare, dataToPush[i]);
    }
}

TEST(CircularBuffer, TestBufferOverflow)
{
    // create an circular buffer and try to push more data than the buffer can hold
    // the operation should fail and the buffer should be empty after operation

    int32_t status;
    uint8_t buffer[100], dataToPush[101];
    uint32_t bufferSize = 100, dataToPushSize = 101;
    CircularBufferInit cbInit;
    CircularBuffer cb;

    cbInit.pBuffer = buffer;
    cbInit.nBufferSize = bufferSize;
    cbInit.pfnMutexInitialize = NULL;
    cbInit.pfnMutexLock = NULL;
    cbInit.pfnMutexRelease = NULL;

    status = circularBufferInitialize(&cb, cbInit);

    EXPECT_EQ(status, LIBCB_SUCCESS);

    // fill dataToPush with indexes

    for (uint32_t i = 0; i < dataToPushSize; i++)
    {
        dataToPush[i] = i;
    }

    status = circularBufferPush(&cb, dataToPush, dataToPushSize);

    EXPECT_EQ(status, LIBCB_BUFFEROVERFLOW);

    EXPECT_EQ(cb.nCount, 0);
    EXPECT_EQ(cb.nHead, 0);
    EXPECT_EQ(cb.nTail, 0);
}

TEST(CircularBuffer, TestPopSingleItem)
{
    // create an circular buffer and push a single item
    // pop the item and check if the buffer is empty
    // the buffer should be empty after the pop

    int32_t status;
    uint8_t buffer[100], dataToPush, dataToCompare;
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

    dataToPush = 0x55;
    status = circularBufferPush(&cb, &dataToPush, 1);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(cb.nCount, 1);
    EXPECT_EQ(cb.nHead, 0);
    EXPECT_EQ(cb.nTail, 1);

    status = circularBufferPop(&cb, &dataToCompare, 1);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(dataToCompare, dataToPush);

    EXPECT_EQ(cb.nCount, 0);
    EXPECT_EQ(cb.nHead, 1);
    EXPECT_EQ(cb.nTail, 1);
}

TEST(CircularBuffer, TestPopMultipleItem)
{
    // create an circular buffer and push multiple items
    // pop the items and check if the buffer is empty
    // the buffer should be empty after the pop

    int32_t status;
    uint8_t buffer[100], dataToPush[2], dataToCompare[2];
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

    dataToPush[0] = 0x55;
    dataToPush[1] = 0x66;
    status = circularBufferPush(&cb, dataToPush, 2);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(cb.nCount, 2);
    EXPECT_EQ(cb.nHead, 0);
    EXPECT_EQ(cb.nTail, 2);

    status = circularBufferPop(&cb, dataToCompare, 2);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(dataToCompare[0], dataToPush[0]);
    EXPECT_EQ(dataToCompare[1], dataToPush[1]);

    EXPECT_EQ(cb.nCount, 0);
    EXPECT_EQ(cb.nHead, 2);
    EXPECT_EQ(cb.nTail, 2);
}

TEST(CircularBuffer, TestPopBufferCompletely)
{
    // create an circular buffer and push the data with the size of the buffer
    // the buffer should be full after the push
    // pop the data from the buffer and check if the buffer is empty
    // the buffer should be empty after the pop

    int32_t status;
    uint8_t buffer[100], dataToPush[100], dataToCompare[100];
    uint32_t bufferSize = 100, dataToPushSize = 100;
    CircularBufferInit cbInit;
    CircularBuffer cb;

    cbInit.pBuffer = buffer;
    cbInit.nBufferSize = bufferSize;
    cbInit.pfnMutexInitialize = NULL;
    cbInit.pfnMutexLock = NULL;
    cbInit.pfnMutexRelease = NULL;

    status = circularBufferInitialize(&cb, cbInit);

    EXPECT_EQ(status, LIBCB_SUCCESS);

    // fill dataToPush with indexes

    for (uint32_t i = 0; i < dataToPushSize; i++)
    {
        dataToPush[i] = i;
    }

    status = circularBufferPush(&cb, dataToPush, dataToPushSize);

    EXPECT_EQ(status, LIBCB_SUCCESS);
    EXPECT_EQ(cb.nCount, dataToPushSize);
    EXPECT_EQ(cb.nHead, 0);
    EXPECT_EQ(cb.nTail, dataToPushSize);

    // pop the data from the buffer and compare it one by one

    status = circularBufferPop(&cb, dataToCompare, dataToPushSize);

    EXPECT_EQ(status, 0);

    for (uint32_t i = 0; i < dataToPushSize; i++)
    {
        EXPECT_EQ(dataToCompare[i], dataToPush[i]);
    }

    EXPECT_EQ(cb.nCount, LIBCB_SUCCESS);
    EXPECT_EQ(cb.nHead, dataToPushSize);
    EXPECT_EQ(cb.nTail, dataToPushSize);
}

TEST(CircularBuffer, TestPopEmptyBuffer)
{
    // create an circular buffer and try to pop data from it
    // the operation should fail and the buffer should be empty after operation

    int32_t status;
    uint8_t buffer[100], dataToCompare[100];
    uint32_t bufferSize = 100, dataToPopSize = 100;
    CircularBufferInit cbInit;
    CircularBuffer cb;

    cbInit.pBuffer = buffer;
    cbInit.nBufferSize = bufferSize;
    cbInit.pfnMutexInitialize = NULL;
    cbInit.pfnMutexLock = NULL;
    cbInit.pfnMutexRelease = NULL;

    status = circularBufferInitialize(&cb, cbInit);

    EXPECT_EQ(status, LIBCB_SUCCESS);

    status = circularBufferPop(&cb, dataToCompare, dataToPopSize);

    EXPECT_EQ(status, LIBCB_BUFFEREMPTY);

    EXPECT_EQ(cb.nCount, 0);
    EXPECT_EQ(cb.nHead, 0);
    EXPECT_EQ(cb.nTail, 0);
}