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
./src/tests/Google_Tests_run --gtest_filter=ShMem.singleThr\
eadCorrectBytesReceived:ShMem/*.singleThreadCorrectBytesReceived:*/ShMem.singleThreadCorrectBytesReceived/*:*/ShMem/*.\
singleThreadCorrectBytesReceived:ShMem.resultsAreCreated:ShMem/*.resultsAreCreated:*/ShMem.resultsAreCreated/*:*/ShMe\
m/*.resultsAreCreated:ShMem.kasia:ShMem/*.kasia:*/ShMem.kasia/*:*/ShMem/*.kasia:ShMem.CHILD_PARENT_PROCESSES_CORRECTE\
D_TEXT_RECEIVED:ShMem/*.CHILD_PARENT_PROCESSES_CORRECTED_TEXT_RECEIVED:*/ShMem.CHILD_PARENT_PROCESSES_CORRECTED_TEXT_R\
ECEIVED/*:*/ShMem/*.CHILD_PARENT_PROCESSES_CORRECTED_TEXT_RECEIVED:MessageQueue.CHILD_PARENT_PROCESSES_CORRECTED_TEXT_R\
ECEIVED:MessageQueue/*.CHILD_PARENT_PROCESSES_CORRECTED_TEXT_RECEIVED:*/MessageQueue.CHILD_PARENT_PROCESSES_CORRECTED_\
TEXT_RECEIVED/*:*/MessageQueue/*.CHILD_PARENT_PROCESSES_CORRECTED_TEXT_RECEIVED:Sych.NOTIFICATION_WORKS:Sych/*.NOTIFICA\
TION_WORKS:*/Sych.NOTIFICATION_WORKS/*:*/Sych/*.NOTIFICATION_WORKS:MainTests.test_6:MainTests/*.test_6:*/MainTests.tes\
t_6/*:*/MainTests/*.test_6 --gtest_color=no
```

- Note: test results are located in the _build/src/tests/_

## Run the producer and consumer applications

- terminal 1 (inside the build directory)

    ```shell script
    # We need sudo to set the scheduling policy
    sudo ./Producer-app
    ```

- terminal 2 (inside the build directory)

    ```shell script
    # We need sudo to set the scheduling policy
    sudo ./Consumer-app
    ```