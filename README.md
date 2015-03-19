# project
How to compile the graphical user interface.
1 qt -project
2  add LIBS += -lcln -lginac -lcycle -lfigure -L./ into your .pro file
   add qmake_cxxflags = -std=gnu++11 into your .pro file
3 qmake
4 make
5 ./"filename"

