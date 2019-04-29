# Advanced Charging Switch

## Project Structure

ACSwitch is a small project, I have strived worst to structure it nice enough for
such scale. It forms out of following components:

#### Native source code

    native/
    |
    |--- lib/                                     <--- Prebuilt external libraries
    |    |
    |    |--- libsocket++_arm.a                   <--- libsocket++ for arm architecture
    |    |--- libsocket++_x86.a                   <--- libsocket++ for x86 architecture
    |
    |--- include/                                 <--- Header files
    |    |
	|    |--- socket.h                            <--- libsocket++ header
    |    |--- *.h                                 <--- ACSwitch headers
    |
    |--- *.cc                                     <--- Source files
    |--- **                                       <--- Local documents

#### Module source tree

    module/
    |
    |--- bin/                                     <--- acs binaries
    |    |
    |    |--- acs_arm                             <--- acs binary for arm
    |    |--- acs_x86                             <--- acs binary for x86
    |
    |--- META-INF/com/google/android              <--- Updater stuff for recovery
    |    |
    |    |--- update-binary                       <--- Installer script
    |    |--- updater-script                      <--- Dummy script
    |
    |--- acs.conf                                 <--- Configuration file
    |--- install.sh                               <--- Installer script for Magisk framework
    |--- module.prop                              <--- Metadata file
    |--- README.md                                <--- README file
    |--- service.sh                               <--- Boot script
	|--- **                                       <--- Local documents

#### Build scripts and tools

    root/                                         <--- Root of ACSwitch project folder
    |
    |--- build/                                   <--- Build scripts
    |    |
    |    |--- build.sh                            <--- Internal build script
    |    |--- clean.sh                            <--- Cleaner script
    |    |--- compile.sh                          <--- Compiler script
    |    |--- pack.sh                             <--- Packer script
    |    |--- patch.sh                            <--- Patcher script
    |    |--- switch.db-raw                       <--- Control files database
    |
    |--- tools/                                   <--- Build tools
    |    |
    |    |--- *.sh                                <--- NDK wrapper scripts
    |    |--- zipsigner.jar                       <--- zipsigner.jar binary
    |    |--- **                                  <--- Local documents
    |
    |--- build.sh                                 <--- Build script
    |--- COPYING                                  <--- License text
    |--- NOTICE                                   <--- License notices
    |--- README.md                                <--- README file
    |--- **                                       <--- Miscellanous documents

#### Environmental tools

    .vscode/                                      <--- Visual Studio Code specific files
    |
    |--- c_cpp_properties.json                    <--- C++ language properties
    |--- tasks.json                               <--- Default build task
