# Advanced Charging Switch

## Miscellanous

#### Building tips

- If you use Visual Studio Code, update `.vscode/tasks.json` and use key combo
`CTRL + Shift + B` to build ACSwitch without commandline hassle.

- You should discard following files after building ACSwitch:

    - `native/database.cc`
    - `native/module.cc`

- You should commit following files after building ACSwitch:

    - `module/module.prop`

#### Binary tips

- Build version of acs binary can be known by `strings $(which acs) | grep 'BUILD VERSION'`.
