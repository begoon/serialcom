#ifndef _STRUITLS_H
#define _STRUITLS_H

#include <Classes.hpp>
#include <System.hpp>

#pragma hdrstop

AnsiString hexPack(const AnsiString& str);
AnsiString hexDump(const AnsiString& str, const AnsiString& delimiter);
AnsiString smartHexPack(const AnsiString& st );
AnsiString smartHexDump(const AnsiString& str);
AnsiString expandLeft(const AnsiString& str, char ch, int sz);
AnsiString expandRight(const AnsiString& str, char ch, int sz);

#endif
