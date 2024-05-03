# gtest-typedfiles

Generate GoogleTest classes from a config file. Targeted for per-file test cases.

Defining parameterized tests for a set of files results into the structure displayed on the right.  
`gtest-typedfiles` allows test generation as seen in the left structure.

```
TestSuite                   TestSuite
    |- File1                    |- Test1
    |    |- Test1               |    |- File1
    |    |- Test2               |    |- ...
    |    |- ...       VS.       |- Test2
    |- File2                    |    |- File1
    |    |- Test                |    |- ...
    |- ...                      |- ...

```

This functionality becomes useful if

- lots of tests may be skipped depending on the currently read file
- you want to run tests on a subset of files without modifying the code