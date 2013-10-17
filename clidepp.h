#pragma once

#include "clidecl.h"

namespace dpcutil {

#ifdef DOXYGEN_PL
/// Klasa służąca do komunikacji z urządzeniem FPGA za pomocą protokołu DEPP.
/// Szczegółowa dokumentacja protokołu znajduje się na stronie producenta:
/// http://www.digilentinc.com/Data/Products/ADEPT/DpimRef%20programmers%20manual.pdf
#else
/// Allow you to communicate with FPGA device using DEPP protocol.
/// More detailed documentation about the protocol can be found on Digilent
/// website:
/// http://www.digilentinc.com/Data/Products/ADEPT/DpimRef%20programmers%20manual.pdf
#endif
public ref class DEPP sealed {
 private:
  static String ^ _version = nullptr;
  Device ^ _dvc;
  bool _enabled;

 public:
  #ifdef DOXYGEN_PL
  /// Tworzy obiekt umożliwiający komunikację za pomocą protokołu DEPP.
  ///
  /// \param dvc Urządzenie, z którym odbędzie się komunikacja
  #else
  /// Constuct the object that allows you to communicate using DEPP protocol.
  ///
  /// \param dvc Device that the object will be communicating with.
  #endif  // ifdef DOXYGEN_PL
  DEPP(Device ^ dvc);
  ~DEPP();

  #ifdef DOXYGEN_PL
  /// Wskazuje, czy transmisja z użyciem protokołu jest włączona.
  #else
  /// Indicate whether the transmission is enabled.
  #endif  // ifdef DOXYGEN_PL
  property bool IsEnabled {
    bool get();
  }

  #ifdef DOXYGEN_PL
  /// Aktywuje transmisję z użyciem protokołu DEPP. Wywołanie tej metody przy
  /// aktywnej transmisji spowoduje rzucenie wyjątku InvalidOperationException.
  #else
  /// Enable the transmission. Calling this method with enabled transmission
  /// throws InvalidOperationException.
  #endif  // ifdef DOXYGEN_PL
  void Enable();

  #ifdef DOXYGEN_PL
  /// Dezaktywuje transmisję z użyciem protokołu DEPP. Wywołanie tej metody przy
  /// nieaktywnej transmisji spowoduje rzucenie wyjątku
  //  InvalidOperationException.
  #else
  /// Disable the transmission. Calling this method with disabled transmission
  /// throws InvalidOperationException.
  #endif  // ifdef DOXYGEN_PL
  void Disable();

  #ifdef DOXYGEN_PL
  /// Zapisuje podaną wartość do rejestru o wskazanym adresie.
  ///
  /// \param addr adres rejestru, do którego ma się odbyć zapis
  /// \param value wartość, która ma zostać zapisana do rejestru
  #else
  /// Put a given value in the registry with given address.
  ///
  /// \param addr address of the registry
  /// \param value value that will be put in a registry
  #endif  // ifdef DOXYGEN_PL
  void PutReg(unsigned char addr, unsigned char value);

  #ifdef DOXYGEN_PL
  /// Odczytuje wartość przechowywaną w rejestrze o wskazanym adresie.
  ///
  /// \param addr adres rejestru, z którego ma zostać odczytana wartość
  /// \returns wartość przechowywana w rejestrze o wskazanym adresie
  #else
  /// Get a value stored in the registry with given address.
  ///
  /// \param addr address of the registry
  /// \returns value stored in the registry
  #endif  // ifdef DOXYGEN_PL
  unsigned char GetReg(unsigned char addr);

  #ifdef DOXYGEN_PL
  /// Zapisuje jednocześnie wiele wartości do wielu różnych rejestrów.
  /// Przekazywane tablice muszą być tej samej długości. Wartość
  /// <tt>values[0]</tt> zostanie zapisana do rejestru o adresie
  /// <tt>addrs[0]</tt>, wartość <tt>values[1]</tt> do rejestru o adresie
  /// <tt>addrs[1]</tt>, itd.
  ///
  /// \param addrs tablica z adresami rejestrów, do których mają zostać zapisane
  ///     wartości
  /// \param values tablica z wartościami, które mają zostać zapisane do
  ///     odpowiednich rejestrów
  #else
  /// Simultaneously puts multiple values to multiple registers.
  /// Passed arrays must have the same length. Value <tt>values[0]</tt> will be
  /// put in the register with address <tt>addrs[0]</tt>, <tt>value[1]</tt> will
  /// be put in register with address <tt>addrs[1]</tt>, and so on.
  ///
  /// \param addrs array containing addresses of the registers the values will
  ///     be put in
  /// \param values array containing values that will be put to corresponding
  ///     registers
  #endif  // ifdef DOXYGEN_PL
  void PutRegs(array<unsigned char> ^ addrs, array<unsigned char> ^ values);

  #ifdef DOXYGEN_PL
  /// Odczytuje jednocześnie wartości przechowywanych w wielu rejestrach.
  ///
  /// \param addrs tablica z adresami rejestrów, z których mają zostać odczytane
  ///     wartości
  /// \returns tablica z wartościami przechowywanymi w podanych adresach
  #else
  /// Simultaneously gets multiple values from multiple registers.
  ///
  /// \param addrs array containing addresses of the registers the values will
  ///     be get from
  /// \returns array containing values stored in given addresses
  #endif  // ifdef DOXYGEN_PL
  array<unsigned char> ^ GetRegs(array<unsigned char> ^ addrs);

  #ifdef DOXYGEN_PL
  /// Wersja protokołu DEPP dostępna w bibliotece \c dpcutil.
  #else
  /// DEPP protocol version retreived from \c dpcutil library.
  #endif  // ifdef DOXYGEN_PL
  static property String ^ Version {
    String ^ get();
  }
};

}  // namespace dpcutil