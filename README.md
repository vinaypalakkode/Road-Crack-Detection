

![RI Logo](http://www-preview.ri.cmu.edu/images/site_images/ri_header_right.png)



# Vision for Road Monitoring

_Vinay Palakkode <vinaypalakode@cmu.edu>_

**Publications**

[**Project Wiki**](https://github.com/vinaypalakkode/Road-Crack-Detection/wiki)
 
  For detailed documentation on the codebase and canonical examples for each module, kindly refer the [project wiki](https://github.com/vinaypalakkode/Road-Crack-Detection/wiki).

**Dependencies**

1. [**Clang**](http://clang.llvm.org/)   : If working with linux, kindly install clang as the prefered C/C++ compiler for this project is clang.
  
    `sudo apt-get install clang`

    You may have to update the default compiler from gcc to clang in case you wish you keep poth gcc and clang-llvm toolchains  on your system. Or you may play around with honors variables in your CMake settings. 
   
    Refer: [link]( http://stackoverflow.com/questions/7031126/switching-between-gcc-and-clang-llvm-using-cmake)

2. [**CMake**](http://www.cmake.org/) : To ensure portability we use cmake to generate the Makefiles. Kindly install cmake version >= **2.6**

3. [**OpenCV**](http://opencv.org/) : We rely heavily on OpenCV libs for this project. Opencv 3.0 (beta)

4. [**Boost**](http://www.boost.org/) : We would soon replace the stl containers with boost containers pretty soon for better portability and robustness.

5. [**libSVM**](http://www.csie.ntu.edu.tw/~cjlin/libsvm/) : A simple and handy library for support vector machines.

 



Copyright (C) Carnegie Mellon University 2015 
