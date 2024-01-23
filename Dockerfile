FROM gcc:latest

WORKDIR /usr/src/ex1

COPY ./src/ .

RUN g++ -o BloomFilterApplication ./main.cpp ./BloomFilter.cpp ./BloomFilterApp.cpp ./HashFunc.cpp ./HelpFunctions.cpp ./NumHashFunc.cpp ./VectorBlacklist.cpp ./src/SetupParser.cpp

CMD ["./BloomFilterApplication"]
