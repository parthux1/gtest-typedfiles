# gtest-typedfiles

Generate GoogleTest classes from a config file. Targeted for per-file test cases.

Defining parameterized tests for a set of files results into the structure displayed on the left.  
`gtest-typedfiles` allows test generation as seen in the right structure.

```
TestSuite                   TestSuite
    |- File1                    |- Test1
    |    |- Test1               |    |- File1
    |    |- Test2               |    |- ...
    |    |- ...       VS.       |- Test2
    |- Fil2                     |    |- File1
    |    |- Test                |    |- ...
    |- ...                      |- ...

```