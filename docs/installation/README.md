# wxCharts Installation

At the moment we do not provide pre-built binaries for wxCharts. Any installation must be made by rebuilding the code
from source.

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

cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX=c:\wxcharts ..

To select the config: cmake --build . --config Release|Debug (note that it needs to be after the . weirdly enough).


cmake --install . (this installs Release by default)
