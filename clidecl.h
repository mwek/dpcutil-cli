#pragma once

#include "dpcutil/dpcdecl.h"

using namespace System;

namespace dpcutil {

public enum class ErrorCodes {
  NoErc = ercNoErc,
  NotSupported = ercNotSupported,
  TransferCancelled = ercTransferCancelled,
  CapabilityConflict = ercCapabilityConflict,
  CapabilityNotEnabled = ercCapabilityNotEnabled,
  EppAddressTimeout = ercEppAddressTimeout,
  EppDataTimeout = ercEppDataTimeout,
  DataSndLess = ercDataSndLess,
  DataRcvLess = ercDataRcvLess,
  DataRcvMore = ercDataRcvMore,
  DataSndLessRcvLess = ercDataSndLessRcvLess,
  DataSndLessRcvMore = ercDataSndLessRcvMore,
  InvalidPort = ercInvalidPort,
  BadParameter = ercBadParameter,
  AciFifoFull = ercAciFifoFull,
  TwiBadBatchCmd = ercTwiBadBatchCmd,
  TwiBusBusy = ercTwiBusBusy,
  TwiAdrNak = ercTwiAdrNak,
  TwiDataNak = ercTwiDataNak,
  TwiSmbPecError = ercTwiSmbPecError,
  AlreadyOpened = ercAlreadyOpened,
  InvalidHif = ercInvalidHif,
  InvalidParameter = ercInvalidParameter,
  TransferPending = ercTransferPending,
  ApiLockTimeout = ercApiLockTimeout,
  PortConflict = ercPortConflict,
  ConnectionFailed = ercConnectionFailed,
  ControlTransferFailed = ercControlTransferFailed,
  CmdSendFailed = ercCmdSendFailed,
  StsReceiveFailed = ercStsReceiveFailed,
  InsufficientResources = ercInsufficientResources,
  InvalidTFP = ercInvalidTFP,
  InternalError = ercInternalError,
  TooManyOpenedDevices = ercTooManyOpenedDevices,
  ConfigFileError = ercConfigFileError,
  DeviceNotConnected = ercDeviceNotConnected,
  EnumNotFree = ercEnumNotFree,
  EnumFreeFail = ercEnumFreeFail,
  InvalidDevice = ercInvalidDevice,
  DeviceBusy = ercDeviceBusy,
};

public enum DeviceTransportProtocol {
  USB = dtpUSB,
  Ethernet = dtpEthernet,
  Parallel = dtpParallel,
  Serial = dtpSerial,

  None = dtpNone,
  All = dtpAll,
};

#ifdef DOXYGEN_PL
/// Klasa reprezentująca pojedyncze podłączone urządzenie.
#else
///
#endif  // ifdef DOXYGEN_PL
public ref class Device sealed {
 internal:
  Device(int id);
  Device();
  Device(String^ name, String^ connection, DeviceTransportProtocol dtp);

 public:
  ~Device();

  #ifdef DOXYGEN_PL
  /// Nazwa identyfikująca urządzenie.
  #else
  ///
  #endif  // ifdef DOXYGEN_PL
  property String^ Name {
    String^ get();
   internal:
    void set(String^ value);
  }

  #ifdef DOXYGEN_PL
  /// Adres podłączonego urządzenia.
  #else
  ///
  #endif  // ifdef DOXYGEN_PL
  property String^ Connection {
    String^ get();
   internal:
    void set(String^ value);
  }

  #ifdef DOXYGEN_PL
  /// Rodzaj portu do którego podłączone jest urządzenie.
  #else
  ///
  #endif  // ifdef DOXYGEN_PL
  property DeviceTransportProtocol DTP {
    DeviceTransportProtocol get();
   internal:
    void set(DeviceTransportProtocol value);
  }

  #ifdef DOXYGEN_PL
  /// Wskazuje, czy z urządzeniem zostało nawiązane połączenie
  #else
  ///
  #endif  // ifdef DOXYGEN_PL
  property bool IsOpened {
    bool get();
  }

  #ifdef DOXYGEN_PL
  /// Wskazuje, czy urządzenie jest zajęte
  #else
  ///
  #endif  // ifdef DOXYGEN_PL
  property bool IsBusy {
    bool get();
  }

  #ifdef DOXYGEN_PL
  /// Nawiązuje połączenie z urządzeniem. W przypadku wywołania gdy istnieje
  /// aktywne połączenie z urządzeniem, metoda rzuca wyjątek
  /// \c InvalidOperationException.
  #else
  ///
  #endif  // ifdef DOXYGEN_PL
  void Open();

  #ifdef DOXYGEN_PL
  /// Zamyka aktywne połączenie z urządzeniem. W przypadku wywołania gdy
  /// urządzenie nie jest połączone, metoda rzuca wyjątek
  /// \c InvalidOperationException.
  #else
  ///
  #endif  // ifdef DOXYGEN_PL
  void Close();

 internal:
  void Lock();
  void Release();

 private:
  String^ _name;
  String^ _connection;
  bool _busy;

 internal:
  HIF _hif;
  ::DVC* _dvc;
};

#ifdef DOXYGEN_PL
/// Wyjątek rzucany w momencie pojawienia się błędu połączenia z urządzeniem
/// FPGA.
#else
/// Exception thrown on connection error with FPGA device
#endif
[Serializable]
public ref class ConnectionException sealed : public Exception {
 public:
  ConnectionException() : Exception() {}


  ConnectionException(String^ message) : Exception(message) {}
  ConnectionException(String^ message, Exception^ inner)
      : Exception(message, inner) {}
};

#ifdef DOXYGEN_PL
/// Wyjątek rzucany, podczas próby wykonania operacji, gdy urządzenie FPGA jest
/// zajęte. Najczęściej oznacza to równoczesny dostęp do obiektu klasy Device
/// przez wiele wątków.
#else
/// Exception thrown when an operation is tried to be done while device is busy.
/// In most cases it's caused by concurrent access to Device object.
#endif
[Serializable]
public ref class DeviceBusyException sealed : public Exception {
 public:
  DeviceBusyException() : Exception() {}
  DeviceBusyException(String^ message) : Exception(message) {}
  DeviceBusyException(String^ message, Exception^ inner)
      : Exception(message, inner) {}
};

} // namespace dpcutil