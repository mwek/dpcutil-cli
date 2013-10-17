#include "Stdafx.h"
#include "helpers.h"
#include <string>

using namespace std;

namespace helpers {

void CopyStringToCharArray(String^ s, char* arr, int length) {
  array<unsigned char>^ chars = System::Text::Encoding::ASCII->GetBytes(s);
  pin_ptr<unsigned char> pinned = &chars[0];
  strcpy_s(arr, min(length, chars->Length), (char*)pinned);
}

String^ CharArrayToString(char* arr) {
  return gcnew String(arr);
}

String^ CharArrayToString(char* arr, int length) {
  return gcnew String(arr, 0, length);
}

}
