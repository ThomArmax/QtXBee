# QtXBee
Qt API Library for use with XBee modules from [Digi](http://www.digi.com/products/wireless-wired-embedded-solutions/zigbee-rf-modules/).

Note that this branch is a developping branch, so unstable.
The API may change.

Currently, only XBee serie 1 and XBee serie 1 Pro are supported.

You can checkout the [QtXBee's home page](http://thomarmax.github.io/QtXBee/ "home page") for more information.

#Build
```
$ git clone http://github.com/ThomArmax/QtXBee.git
$ cd ./QtXBee
$ qmake -recursive
$ make
$ sudo make install
```

#Documentation
 - [Online Pre-Alpha Doc](http://thomarmax.github.io/QtXBee/doc/pre_alpha/index.html "Online Pre-Alpha Doc")
 - make the doc
 
   ```
   $ cd doc
   $ doxygen Doxyfile
   $ firefox html/index.html &
   ```
   
