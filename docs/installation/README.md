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
