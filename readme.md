> ! This project is currently unusable

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

This functionality may be useful if

- lots of tests may be skipped depending on the currently read file
- you want to run tests on a subset of files without modifying the code

## setting up this project

- clone with submodules
- setup vcpkg and install dependencies

> this can be done using the following script

```bash
sh tooling/init_vcpkg.sh
```

### using clion

- include the newly created vcpkg installation into clion (View > Tool Windows > Vcpkg > + > [root]/tooling/vcpkg)
- build using UI as normal

### using cli

Build the project using the provided shell script:

```bash
sh tooling/build.sh
``` 