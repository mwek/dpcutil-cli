#pragma once

#include "clidecl.h"

using namespace System;

namespace dpcutil {

#ifdef DOXYGEN_PL
/// Klasa służąca do zarządzania dostępnymi urządzeniami.
#else
///
#endif  // ifdef DOXYGEN_PL
public ref class DeviceManager sealed
{
 private:
  static String^ _version = nullptr;

 public:
  #ifdef DOXYGEN_PL
  /// Wykorzystywana wersja biblioteki \c dpcutil.
  #else
  ///
  #endif  // ifdef DOXYGEN_PL
  static property String ^ Version {
    String ^ get();
  }

  #ifdef DOXYGEN_PL
  /// Pobiera informacje na temat aktualnie podłączonych urządzeń.
  ///
  /// \return tablica zawierająca podłączone urządzenia
  #else
  ///
  #endif  // ifdef DOXYGEN_PL
  static array<Device^>^ Enumerate();
};

}
