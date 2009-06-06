#include "strutils.h"

AnsiString hexPack(const AnsiString& str)
{
   AnsiString raw;
   for (int i = 1; i <= str.Length(); ++i)
      if (isxdigit(str[i]))
        raw += str[i];

   int sz = raw.Length() / 2;
   char* result = new char[ sz + 1 ];
   HexToBin(raw.LowerCase().c_str(), result, sz);
   AnsiString _result = AnsiString(result, sz);
   delete[] result;
   return _result;
}

AnsiString smartHexPack(const AnsiString& str)
{
   AnsiString _str(str);
   AnsiString result = "";

   while (_str.Length()) {
      int start = _str.Pos("<");
      int end = _str.Pos(">");

      if (!start || !end || start > end || (end - start - 1)&1) {
         result += _str;
         break;
      }

      result += _str.SubString(1, start-1) + hexPack(_str.SubString(start+1, end-start-1));
      _str.Delete(1, end);
   }

   return result;
}

AnsiString hexDump(const AnsiString& str, const AnsiString& delimiter = "")
{
   AnsiString result = "";

   for (int i = 1; i <= str.Length(); ++i)
      result += IntToHex((int)(unsigned char)str[ i ], 2) + delimiter;

   return result;
}

AnsiString smartHexDump(const AnsiString& str)
{
   AnsiString result = "";

   enum {
      shdChar, shdDump
   };
   
   int mode = shdChar;

   for (int i = 1; i <= str.Length(); ++i) {
      switch (mode) {
         case shdChar:
            if (!isprint(str[i]) || str[i]=='<' || str[i]=='>') {
               result += AnsiString("<") + hexDump(str[i]);
               mode = shdDump;
            } else
               result += str[i];
            break;
         case shdDump:
            if (!isprint(str[i]) || str[i]=='<' || str[i]=='>')
               result += hexDump(str[i]);
            else {
               result += AnsiString(">") + str[i];
               mode = shdChar;
            }
      }
   }

   if (mode == shdDump)
      result += ">";

   return result;
}

AnsiString expandLeft(const AnsiString& str, char ch, int sz)
{
   return str.Length() < sz ? AnsiString::StringOfChar(ch, sz - str.Length()) + str : str;
}

AnsiString expandRight(const AnsiString& str, char ch, int sz)
{
   return str.Length() < sz ? str + AnsiString::StringOfChar(ch, sz - str.Length()) : str;
}
