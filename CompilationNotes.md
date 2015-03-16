# Compilation notes #

Borland C++ Builder 6.0 should be used to compile the project.

Just type `make` (it should be Borland's `make`) to build the project.

Other targets available in the `makefile`:
  * **dist** - build the project, pack the target executable by [UPX](http://upx.sourceforge.net/) and put it to the archive using [7z](http://www.7-zip.org) archiver
  * **release** - pack all sources to the distribution file
  * **clean** - remove junk from the directory

The alternative way to build the project is to open the project file `smartcom.bpr` in the C++ Builder 6.0 IDE. The [ComPort](http://sourceforge.net/projects/comport/) VCL component has to be installed in this case. The `ComPort` 3.1 used in the project can be downloaded from [here](http://serialcom.googlecode.com/files/cport-3.10.zip). If you use newer version of the Borland IDE you would probably need to get the latest version from the [official site](http://sourceforge.net/projects/comport/).

This library has some glitches to be compiled and installed properly and it's documented enough in the readme but there is one more known issue which has to fixed manually.

You have to modify the `ComPort.hpp` file.

Search for the line:
```
   void __fastcall SetPort(const AnsiString Value);
```
and change it to:
```
   #ifdef SetPort
      #undef SetPort
      void __fastcall SetPort(const AnsiString Value);
      #define SetPort SetPortA
   #else
      void __fastcall SetPort(const AnsiString Value);
   #endif
```
Search for the line:
```
      __property AnsiString Port = {read=FPort, write=SetPort};
```
and change it to:
```
   #ifdef SetPort
      #undef SetPort
      __property AnsiString Port = {read=FPort, write=SetPort};
      #define SetPort SetPortA
   #else
      __property AnsiString Port = {read=FPort, write=SetPort};
   #endif 
```