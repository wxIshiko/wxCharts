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
