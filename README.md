# Our Bloom Filter
Welcome to our Bloom Filter repository!

The first assignment of the course asked us to create a Bloom Filter, which is a probabilistic data structure, while working in TDD.

* In the **src** folder you can see the source files of the bloom filter.

* In the **tests** folder you can see the tests we created while developing the bloom filter.
The tests run automatically when trying to do a pull request to the main branch.

* In the **workflows** folder you can find the code that handles running the tests automatically,  and handles uploading to dockerhub on every release.


## The workflow
We started by creating a new JIRA project using SCRUM. We wrote all the steps we could think of as tasks, including but not limited to, creating a github project, adding more edge cases, adding the CI CI workflows, and more. 

Once we finished that, we created a github repository, and uploaded the calc app specified in the assignment to it- including the tests for it, to check that Google Tests works on each of our setups. 

Once we got it all working, we started the real work: we decided to split the steps to 3 main tasks: the basic tests and a basic bloom filter that passes it, 
then more refined tests which test all the edge cases and the more advanced features of the bloom filter (like multiple functions and multiple blacklists support), and lastly the CI CD parts. 

Each of us did one of this main tasks, and after each one we looked through it, refactored what we thought was necessary and added more documentation along the way.

## How to compile it for yourself
Use the following command in the project folder after downloading it:

g++ -o ./build/ex1 ./src/main.cpp ./src/BloomFilter.cpp ./src/BloomFilterApp.cpp ./src/HashFunc.cpp ./src/HelpFunctions.cpp ./src/NumHashFunc.cpp ./src/VectorBlacklist.cpp ./src/SetupParser.cpp

* Note: you can change where the resulting executable is saved and the name it gets by changing ./build/ex1 to ./NEW_LOCATION/NEW_NAME

## How to use the Bloom Filter Application
After downloading and compiling with the command above, enter ./build/ex1 to start the filter.

In order to complete the setup part of the application, you will need to enter 2 things:
1. The size of the bloom filter- larger size means the filter will have to check its blacklist less often (which is better)
2. Which hashing functions to use (we currently support only natural number hash types):

   nhash function- hashes the input url once, and hashes the result the number of times needed to reach n hashes.

In the same line enter both a **size and the functions to use** (no extra characters like ',' between each word).
If you made a mistake, like choosing a negative size or trying to use a different function than natural number, nothing will happen.
The program will wait for you to enter a line again, which will hopefully be proper.
For the functions just type their type (1, 2, 3 and so on). Using the same function multiple times is meaningless.


<ins>After setup is done: </ins>

In order to add a url to the blacklist enter:
1 url (swap url with the url you want' make sure there are no spaces!)

In order to check if a certain url is blacklisted enter:
2 url (swap url for the url you want, make sure there are no spaces!).

If the bloom filter is certain that the url is not blacklisted, it will output **false**.
If the url is potentially blacklisted it will first output **true**, and **another true** if it checked and the url is blacklisted, or **false** otherwise (a false positive).


