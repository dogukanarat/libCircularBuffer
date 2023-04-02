#include "gtest/gtest.h"
#include "libCircularBuffer/CircularBufferExt.h"

TEST(CircularBufferExt, TestRead)
{
    // create an circular buffer and push a single item to it
    // check if the push operation is successful and the buffer is not empty
    // read the data from the circular buffer and check if the data is correct
    // check if the buffer is not empty after the read operation

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

    uint8_t readData;
    status = circularBufferRead(&cb, &readData, 1, 0, 1);

    EXPECT_EQ(status, LIBCB_SUCCESS);
    EXPECT_EQ(readData, data);
    EXPECT_EQ(cb.nCount, 1);
    EXPECT_EQ(cb.nHead, 0);
    EXPECT_EQ(cb.nTail, 1);


}