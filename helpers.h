#pragma once

using namespace System;

namespace helpers {

void CopyStringToCharArray(String ^ s, char* arr, int length);
String ^ CharArrayToString(char* arr);
String ^ CharArrayToString(char* arr, int length);

}
