Getting Started with Atym
==========================
This repository contains materials and sample code for building applications with the Atym Platform, including the Atym toolchain for C/C++ via a **[dev container](https://code.visualstudio.com/docs/remote/containers-tutorial)**, which can also be run in VSCode or interactively.

## Getting Started

First, clone this repository with submodules:
```bash
git clone --recursive https://github.com/atym-io/getting-started.git
```
Or if you already cloned without submodules:
```bash
git submodule update --init --recursive
```

**Why submodules?** This repository includes the [ATYM SDK](https://github.com/atym-io/atym-sdk) as a submodule, which provides the C API definitions (like GPIO, sensors, timers, and messaging) needed to build Atym applications. The `--recursive` flag ensures you get both this repository and the SDK headers.

## Using the SDK in Samples
Sample applications can include the ATYM SDK headers:
```c
#include "atym-sdk/ocre_api.h"
```

---

### Development with Visual Studio Code
To develop with the Atym dev container using VS Code follow these steps:
1. Install [Docker Desktop](https://www.docker.com/products/docker-desktop/), [Visual Studio Code](https://code.visualstudio.com/), and the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) Extension in VSCode.
2. Start VS Code
3. Run the `Dev Containers: Open Folder in Container...` from the Command Palette (`Cmd + Shift + P` for Mac, or `Ctrl + Shift + P` for Windows).
4. Select the folder containing the cloned repository.

The VS Code window will then reload, but since the container does not exist yet, VS Code will create one and clone the sample repository into an isolated container volume. This will take some time and progress will be displayed in the lower right corner of the VS Code window. This step only needs to be done once.

Opening a terminal will give you console access to the container environment. From there, the samples can be built. 

---

### Interactive Development
The toolchain container can also be launched and used *interactively* as follows, without the need for VS Code.
1. Install [Docker Desktop](https://www.docker.com/products/docker-desktop/)
2. Run the following commands from within the newly cloned `getting-started` repo.
```
cd samples
docker run --rm -it -v $(pwd):/home/atym ghcr.io/atym-io/atym-c-toolchain:latest
```

## Building the Samples
Each of the sample applications has a CMake file and can be built as follows:
```
cd samples/sample_name
mkdir build && cd build
cmake ..
make
```
**Note:** This step results in the creation of a file named `sample_name.wasm`, which will be used by the Atym CLI to create an Atym container in the next step.

Next, jump up out of the *build* directory and back to the sample root.
```
cd ..
```
Then build the container using the Atym CLI (provided in the Dev Container)
```
atym build -v
```
You should now see a new `.atym` directory in your home directory (`~/.atym`) that contains the container name (as specified in `build.yml`), as well as all of the container contents.

## What's Next?
Now that you've built your first Atym container, it's time to deploy it to your device! 

Visit our [Quickstart Guide](https://docs.prod.atym.io/quickstart) to learn how to set up the Atym Runtime on your board, register your device with the Atym Hub, and deploy your first containerized application. 
