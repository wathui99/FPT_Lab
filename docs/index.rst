.. AtomThreadsPortingSTM8LDISCOVERY documentation master file, created by
   sphinx-quickstart on Tue Jul 23 15:35:20 2019.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to AtomThreadsPortingSTM8LDISCOVERY's documentation!
============================================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:



Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

# Atom Threads porting on STM8L Discovery

This our purpose is make a sample project that run 2 thread with Atom Threads RTOS on STM8L Discovery 
[![Build Status](https://travis-ci.org/wathui99/FPT_Lab.svg?branch=master)](https://travis-ci.org/wathui99/FPT_Lab)

Getting Started
==================
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

Prerequisites
==================
What things you need to install the software and how to install them
1. STM8L Discovery Board
  Ofcourse, we can't run our code in the air, if you're in VietNam, this board is sold at [hshop][Buy STM8L Discovery]
  However, theoretically, you can use any chip what supported by Atom Threads (can see at [Atom Threads homepage][Atom Threads homepage]
2. IAR Complier
3. Atom Threads RTOS 

**Optional**

These are not really nescessary but they make it easier:

* Document of STM8L: [Datasheet](https://www.st.com/resource/en/datasheet/stm8l151m8.pdf), [User manual](https://www.st.com/content/ccc/resource/technical/document/reference_manual/2e/3b/8c/8f/60/af/4b/2c/CD00218714.pdf/files/CD00218714.pdf/jcr:content/translations/en.CD00218714.pdf)
* Logic Analyzer to measure exacly the quantumn time, it not a big deal but use a quantumn timer without handle it is not a good way to do.
```
Give examples
```

Installing (must be clean but chưa có gì để viết)
==================
A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

Running the tests (merge còn chưa xong chạy con mẹ gì)
==================
Explain how to run the automated tests for this system

Break down into end to end tests
==================
Explain what these tests test and why

```
Give an example
```

And coding style tests
==================

This sample follow [Linux kernel convention](https://www.kernel.org/doc/html/v4.10/process/coding-style.html) 
You can see the following at the top of each header file, that the way we sign.

```
/**
  ******************************************************************************
  * @author  NguyenLuongDuyKhanh
  * @date    June-2019
  * @course  FGA-UIT training course
  ******************************************************************************
  * @attention
  * I wrote this libary to use in course only.
  * Any problem, please contact me at:
  *        https://github.com/NguyenLuongDuyKhanh
  ******************************************************************************
  */ 
```
Deployment
==================

It has 2 mode: DEBUG and RELEASE, the way to switch is define or undefine macro '''Tụi bây chưa đưa tao cái Macro này''' at the '''test-main.c'''
By using RELEASE mode, all functions use LCD, Uart,... to debug will be disable, it make CPU recovery resource to perform.

Built With
==================
* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds
 

Authors
==================
* **Billie Thompson** - *Initial work* - [Contact](https://github.com/PurpleBooth)
* **Trần Quang Diệu** - *Work on GPIO STM8L* - [Contact](https://github.com/PurpleBooth)
* **Nguyễn Trần Kha** - *Work on clock general* - [Contact](https://github.com/PurpleBooth)
* **Nguyễn Lương Duy Khánh** *Làm màu nhất nhóm* - [Contact](https://github.com/NguyenLuongDuyKhanh)
* **Lê Hoàng Phúc** - *Work on Atom Threads* - [Contact](https://github.com/PurpleBooth)
* **Lê Trọng Thức** - *Work on Atom Threads* - [Contact](https://github.com/wathui99)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

License
==================
This project is licensed under the BSD License (cause the AtomThreads project has it) - see the [LICENSE.md](LICENSE.md) file for details

Acknowledgments
==================
* The honest thanks to Kelvin Lawson with his Atom Threads RTOS, we've learning a lot of news about how an operating system work. We pleasure to become Atom's contributors with this sample porting.
* Thank our trainers at FPT Golbal Automotive - UIT LAB. Thank to Mr.KietDD, Mr.DanhDC1, Mr.VuCH1, Mr.NguyenTD3, Mr.TraHT, Ms.HueVTT and special, Mr.KhoaHVD with his RTOS lession.
* Thank to Ngô Lan Hương with [Ngô Lan Hương Offical](https://www.youtube.com/channel/UC6wjclMOHQJwOHrvqVRi5Jw), Hương's channel help us to relax affter work-day.
* Thank to Faculty of Computer Engineering, we got our backgound at computer and semiconductor technology at here

[Buy STM8L Discovery](https://hshop.vn/products/kit-stm8l-discovery)
[Atom Threads homepage] (http://atomthreads.com/)
