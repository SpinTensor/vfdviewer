[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](http://www.gnu.org/licenses/lgpl-3.0)
[![Version](https://img.shields.io/badge/version-0.0.1-red.svg)](https://github.com/SpinTensor/vfdviewer)

# vfdviewer

## About
vfdviewer is a GTK3 based visualizing tool for sampling output files of the vftrace profiling library (https://github.com/SX-Aurora/Vftrace).
It allows for:
 - a collapsable call tree visualization
 - a timeline of the call stack
 - a communication matrix for visualizing message sizes, bandwidth, ... of mpi-processes
 - plotting of hardware counter information, defined by the vftrace scenario, as well as custom combination of hardware counter information on the fly.

## Download
You can clone an experimental version of the vfdviewer from github.
The third party tools are included in the git repository as submodules, for your convinience.
```bash
git clone --recursive https://github.com/SpinTensor/vfdviewer.git
```

## Installation
vfdviewer utilizes GNU autotools to build. Make sure `automake`, `autoconf`, and `libtool` are installed on your system. The submodules are integrated in the build process. First the cloned repository needs to be prepared for configuration and compilation
```bash
cd vfdviewer
autoreconf -i
```
Autoconf and make will take care of the rest. 
Since vfdviewer requires the gtk3-devel library, you should ensure that it is available on your system. Your gtk installation will be tested by the configure script.
```bash
./configure --prefix=<path_to_intallation>
make && make install
```
Note that during the compilation some paths to required resources are set within the code, thus moving the installation directories after installation will lead to failures during program execution

## Usage
Simply execute the vfdviewer binary, optionally supply vfd-files as command line arguments
```bash
<path_to_intallation>/bin/vfdviewer [<list-of-vfd-files>]
```

## Authors
The main authors are:
 - Felix Uhl (Felix.uhl@emea.nec.com)

## Third Party Tools
vfdviewer utilizes the following open-source third party tools:
 - Lewis van Winkle's "tinyexpr" (https://github.com/codeplea/tinyexpr). It is used to parse the formula strings which define hardware observables.
 - "slope" (https://github.com/bytebrew/slope). It is used for the plotting of the hardware counter graphs.

## Licensing
vfdviewer is licensed under The GNU general public license (GPL), which means that you are free to copy and modify the source code under the condition that you keep the license.

## How to Contribute
You are free to clone or fork this repository as you like. If you wish to make a contribution, please open up a pull request. If you find a bug in vfdviewer or have an idea for an improvement, please submit an issue on github.
