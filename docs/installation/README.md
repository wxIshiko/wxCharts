# wxCharts Installation

At the moment we do not provide pre-built binaries for wxCharts. Any installation must be made by rebuilding the code
from source.

- [Ubuntu](#ubuntu)
- [Windows with Visual Studio](#windows-with-visual-studio) 

## Ubuntu

### Install wxWidgets

wxCharts depends on the wxWidgets framework. How to install wxWidgets is beyond the scope of this document but
installing with APT should work.

Regardless of what installation method you choose, the following CMake command used by the wxCharts build files must be
able to find the wxWidgets installation correctly.
```
find_package(wxWidgets REQUIRED COMPONENTS core base)
```

For on instance on Ubuntu 22.04.4 LTS the following works:
```
sudo apt install libwxgtk3.0-gtk3-dev
``` 

### Build wxCharts

Once wxWidgets is installed clone the wxCharts repository and build the wxCharts library with CMake.
```
git clone git@github.com:wxIshiko/wxCharts.git
cd wxCharts
mkdir build
cd build
cmake ..
make
```
At the end of these steps you should have the file `libwxcharts.a` in the `build/bin` directory.

You can now install the wxCharts header file and libraries to /usr/local.
```
sudo make install
```

### Test the installation

You can now verify the correct installation by building and running one of the samples.

```
cd ..
cd samples/linechart
cmake .
make
```

This should have successfully built the `linechart` executable. Running it with
```
./linechart
```
should display a windows with a line chart.

## Windows with Visual Studio

### Install wxWidgets

wxCharts depends on the wxWidgets framework. There are several ways to install wxWidgets on Windows but we are going to
recommend a specific procedure because installation on Windows can be hard to get right and issues are difficult to
troubleshoot. Also refer to the official instructions found at https://docs.wxwidgets.org/latest/plat_msw_install.html.

Regardless of what installation method you choose, the following CMake command used by the wxCharts build files must be
able to find the wxWidgets installation correctly.
```
find_package(wxWidgets REQUIRED COMPONENTS core base)
```

We recommend the following installation procedure.

Download the ZIP archive for the latest source code (3.2.6 at the
time of writing) from https://www.wxwidgets.org/downloads/ and extract it. We'll refer to the location where the source
code has been installed as &lt;wxwidgets_source_root&gt;.

Now define a new environment variable `WXWIN` that points to &lt;wxwidgets_source_root&gt;. This environment
variable is required because it is used by the wxCharts build to find the location of xWidgets. While there are other
ways to locate the wxWidgets installation this is a fairly simple and robust way to do so.

Now navigate to the %WXWIN%\build\msw directory. In that directory you will find a series of `wx_vcXY.sln` build files
for different versions of Visual Studio and also a `makefile.vc` file. You can build wxWidgets by opening one of the
`wx_vcXY.sln` and doing a build or by using `nmake` with the `makefile.vc` file as explained in
https://docs.wxwidgets.org/latest/plat_msw_install.html.

For a first try I strongly recommend building wxWidgets as a static library and not a shared library just to limit the
number of things that can go wrong. What is also very important is to build both a `Debug` and `Release` version of the
library. If you don't do that it's possible that your application will try to build against the wrong version and
you'll end up with linking errors. Alternatively make sure you stick to building everything in `Release` or everything
in `Debug` mode. But in general developers tend to need both.

For instance if building with `nmake` the following steps should work. You need to run this from a [Visual Studio 
command prompt](https://learn.microsoft.com/en-us/visualstudio/ide/reference/command-prompt-powershell?view=vs-2022).
```
cd %WXWIN%\build\msw
nmake /f makefile.vc BUILD=debug
nmake /f makefile.vc BUILD=release
```
After performing these steps you should have a series of libraries in `%WXWIN%\lib\vc_x64_lib`.

We can now build wxCharts itself.

While on Linux it is common to install software in `/usr/local`, there isn't a well defined equivalent on Windows. By
default CMake uses `C:\Program Files` but I don't find this very appropriate. So the following instructions will assume
you do want to install the wxCharts libraries somewhere else and show you how to do so. The first step is to choose a 
directory where we want to install the wxCharts libraries, we will assume that location has been saved in the `WXCHARTS`
environment variable.

Now we can clone the wxCharts repository (in a directory different than `WXCHARTS`) and build the wxCharts library with
CMake. The following commands should work. They assume you use Visual Studio 2022 but other versions should work too,
just use the appropriate generator for the version of Visual Studio you are using. The list of generators can be found
here: https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html.

```
git clone git@github.com:wxIshiko/wxCharts.git
cd wxCharts
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX=%WXCHARTS% ..
cmake --build . --config Debug
cmake --build . --config Release
cmake --install . --config Debug
cmake --install . --config Release
```
At the end of these steps you should have the header files in `%WXCHARTS%\include\wxcharts` and the libraries in
`%WXCHARTS%\lib`. wxCharts follows the wxWidgets convention of appending a 'd' suffix to the Debug versions so there
should be a `wxcharts.lib` file and a `wxchartsd.lib` file.