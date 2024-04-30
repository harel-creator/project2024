FROM gcc:latest

WORKDIR /usr/src/ex1

COPY ./src/ .

RUN g++ -o server ./TCP_Server/TCPEchoServer.cpp \
    ./BloomFilter.cpp \
    ./BloomFilterApp.cpp \
    ./HashFunc.cpp \
    ./HelpFunctions.cpp \
    ./NumHashFunc.cpp \
    ./VectorBlacklist.cpp \
    ./SetupParser.cpp

CMD ["./server"]
