# Realtime systems project

## How it works

Producer sends the data using any of available communication methods the consumer. Then the consumer runs some calculations and stores the data locally.

## Compilation on linux

- It's better to import a project into a CLion
- Otherwise compile it using the terminal 

    ```shell script
    sudo apt-get install libsqlite3-dev
    mkdir build && cd build
    cmake ..
    cmake --build . --target all
    ```  
  
## Run tests

```shell script
# inside the build directory
./src/tests/Google_Tests_run --gtest_filter=ShMem.singleThreadCorrectBytesReceived:ShMem/*.singleThreadCorrectBytesRec\
eived:*/ShMem.singleThreadCorrectBytesReceived/*:*/ShMem/*.singleThreadCorrectBytesReceived:ShMem.CHILD_PARENT_PROCESS\
ES_CORRECTED_TEXT_RECEIVED:ShMem/*.CHILD_PARENT_PROCESSES_CORRECTED_TEXT_RECEIVED:*/ShMem.CHILD_PARENT_PROCESSES_CORRE\
CTED_TEXT_RECEIVED/*:*/ShMem/*.CHILD_PARENT_PROCESSES_CORRECTED_TEXT_RECEIVED:MessageQueue.CHILD_PARENT_PROCESSES_CORR\
ECTED_TEXT_RECEIVED:MessageQueue/*.CHILD_PARENT_PROCESSES_CORRECTED_TEXT_RECEIVED:*/MessageQueue.CHILD_PARENT_PROCESSE\
S_CORRECTED_TEXT_RECEIVED/*:*/MessageQueue/*.CHILD_PARENT_PROCESSES_CORRECTED_TEXT_RECEIVED:Sych.NOTIFICATION_WORKS:Sy\
ch/*.NOTIFICATION_WORKS:*/Sych.NOTIFICATION_WORKS/*:*/Sych/*.NOTIFICATION_WORKS
```

- Note: test results are located in the _build/src/tests/_

## Run the producer and consumer applications

- terminal 1 (inside the build directory)

    ```shell script
    # We need sudo to set the scheduling policy
    sudo ./Producer-app
    ```

- terminal 1 (inside the build directory)

    ```shell script
    # We need sudo to set the scheduling policy
    sudo ./Consumer-app
    ```