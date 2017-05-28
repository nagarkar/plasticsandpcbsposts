About The QP-MSP430 Port
========================
This directory contains the QP/C++ port to the MSP430 processor family
with the preemptive QK kernel using the TI CCS-430 compiler.


Using the Port in CCS
=====================
To use this QP-MSP430 port in CCS, it is recommended that you build the QP
framework from sources as part of your CCS project.

The recommended procedure, as illustrated in the provided CCS example projects
in the qpcpp/examples/msp430/ directory, is to create a folder for QP source
and another for QP_port. To do so, right-click on your project and choose 
the New->Folder option.

It is important to create the QP and QP_port folders as "Linked folders",
by expanding the "Advanced" folder option and selecting the "Linked to
alternate location (Linked Folder)" radio button.

The QP folder should be linked to qpcpp/source

The QP_port folder should be linked to qpcpp/ports/msp430/qk/ccs

Once the folders are added to your project, it is very important to exclude
several source files in the QP folder from the specific build configurations.

Here is the list of QP/C++ source files that need to be EXCLUDED from the
bulid configurations:

QK kernel, Debug/Release configuration excludes:
qs_*.cpp
qv.cpp

QK kernel, Spy configuration excludes:
qv.cpp

Finally, to build QP framework from sources, the following directories should
be present in the compiler "Include Options":
 
<qpcpp>\include
<qpcpp>\source
<qpcpp>\ports\msp430\qk\ccs

Where, <qpcpp> is either relative or absolute path to the QP/C++ framework
folder on your machine.
