# Circular Buffer Library

This is a circular buffer library written in C. It is a generic library that can be used to store any type of data. It is a thread safe library that can be used in a multi-threaded environment.

## Unit Tests

```
[==========] Running 9 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 9 tests from CircularBuffer
[ RUN      ] CircularBuffer.TestInitialize
[       OK ] CircularBuffer.TestInitialize (0 ms)
[ RUN      ] CircularBuffer.TestPushSingleItem
[       OK ] CircularBuffer.TestPushSingleItem (0 ms)
[ RUN      ] CircularBuffer.TestPushMultipleItem
[       OK ] CircularBuffer.TestPushMultipleItem (0 ms)
[ RUN      ] CircularBuffer.TestFillBufferCompletely
[       OK ] CircularBuffer.TestFillBufferCompletely (0 ms)
[ RUN      ] CircularBuffer.TestBufferOverflow
[       OK ] CircularBuffer.TestBufferOverflow (0 ms)
[ RUN      ] CircularBuffer.TestPopSingleItem
[       OK ] CircularBuffer.TestPopSingleItem (0 ms)
[ RUN      ] CircularBuffer.TestPopMultipleItem
[       OK ] CircularBuffer.TestPopMultipleItem (0 ms)
[ RUN      ] CircularBuffer.TestPopBufferCompletely
[       OK ] CircularBuffer.TestPopBufferCompletely (0 ms)
[ RUN      ] CircularBuffer.TestPopEmptyBuffer
[       OK ] CircularBuffer.TestPopEmptyBuffer (0 ms)
[----------] 9 tests from CircularBuffer (0 ms total)

[----------] Global test environment tear-down
[==========] 9 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 9 tests.
```
