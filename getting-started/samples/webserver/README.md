# Webserver Demo

To build and run this demo you will need to follow these additional steps:

1. **Download** the files `mongoose.h` and `mongoose.c` from the official [Mongoose repository](https://github.com/cesanta/mongoose) at the commit used for this demo (`fc551ec2e97b236d25e66538386fa4c03d3795d4`).
   - These files are locked to this commit for reproducibility and compatibility.

   ```sh
   curl -o src/mongoose.h https://raw.githubusercontent.com/cesanta/mongoose/fc551ec2e97b236d25e66538386fa4c03d3795d4/mongoose.h && \
   curl -o src/mongoose.c https://raw.githubusercontent.com/cesanta/mongoose/fc551ec2e97b236d25e66538386fa4c03d3795d4/mongoose.c
   ```

> **Note:** The Mongoose files used in this demo are locked to commit `fc551ec2e97b236d25e66538386fa4c03d3795d4` for reproducibility and compatibility. If you use a different version, the demo may not build or function as expected.

2. **Build** the sample as you would any of the other samples, or according to the instructions found in the main [getting-started](https://github.com/atym-io/getting-started) repository.
