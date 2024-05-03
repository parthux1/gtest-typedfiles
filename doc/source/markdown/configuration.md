# Configuration

A local strategy on how to generate files can be defined using `.yaml`.  
The following syntax applies:

```yaml
meta:
  res_path: <relative path to resource folder>
  generator_path: <relative path to baseclass folder>
generator:
  - testsuite: <Test Suite Name>
    files:
      - <FilePath relative to res_path>:
        members:
          - <member name>:
              - <member type>
              - <member value>
        properties:
          - <property 1>: custom key value pair
          - <property x>: ...
      - ...
  - testsuite: asd
```

Example configuration files can be found in [res/](../../../res/).