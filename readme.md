# <project_name>

<project_description>

## Initial setup

- this project is generated using https://github.com/parthux1/project_preset
- run `./scripts/init_project.sh` in project root to define common project variables using the following flags
  - `-p` project name
  - `-d` project description
  - see [scripts/init_project.sh](scripts/init_project_preset.sh) for more information

## Documentation

You can generate a documentation using doxygen.
This will include files from `src/` and `doc/source/`.  
Documentation will be written to `doc/out/`. 
```bash
# run in project root
doxygen doc/DoxyFile

# open the documentation
start doc/out/html/index.html
```
