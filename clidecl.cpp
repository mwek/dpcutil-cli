#include "Stdafx.h"

#include "clidecl.h"
#include "helpers.h"

#include "dpcutil/dmgr.h"

using namespace std;
using namespace helpers;
using namespace dpcutil;

Device::Device() {
  _dvc = new ::DVC();
  Name = "";
  Connection = "";
  DTP = None;
  _hif = hifInvalid;
  _busy = false;
}

Device::Device(int id) {
  _dvc = new ::DVC();
  DmgrGetDvc(id, _dvc);
  _name = CharArrayToString(_dvc->szName);
  _connection = CharArrayToString(_dvc->szConn);
  _hif = hifInvalid;
  _busy = false;
}

Device::Device(String^ name, String^ connection, DeviceTransportProtocol dtp) {
  _dvc = new ::DVC();
  Name = name;
  Connection = connection;
  DTP = dtp;
  _hif = hifInvalid;
  _busy = false;
}

String^ Device::Name::get() {
  return _name;
}

void Device::Name::set(String^ value) {
  _name = value;
  CopyStringToCharArray(_name, _dvc->szName, cchDvcNameMax);
}

String^ Device::Connection::get() {
  return _connection;
}

void Device::Connection::set(String^ value) {
  _connection = value;
  CopyStringToCharArray(_connection, _dvc->szConn, MAX_PATH + 1);
}

DeviceTransportProtocol Device::DTP::get() {
  return static_cast<DeviceTransportProtocol>(_dvc->dtp);
}

void Device::DTP::set(DeviceTransportProtocol value) {
  _dvc->dtp = static_cast<unsigned int>(value);
}

bool Device::IsOpened::get() {
  return _hif != hifInvalid;
}

bool Device::IsBusy::get() {
  return _busy;
}

void Device::Lock() {
  System::Threading::Monitor::Enter(this);
  try {
    if (IsBusy) throw gcnew DeviceBusyException();
    _busy = true;
  } finally {
    System::Threading::Monitor::Exit(this);
  }
}

void Device::Release() {
  System::Threading::Monitor::Enter(this);
  try {
    if (!IsBusy) throw gcnew DeviceBusyException();
    _busy = false;
  } finally {
    System::Threading::Monitor::Exit(this);
  }
}

void Device::Open() {
  if (IsOpened)
    throw gcnew InvalidOperationException("Device is already opened!");

  if (IsBusy)
    throw gcnew DeviceBusyException();

  pin_ptr<HIF> hifPtr = &_hif;
  if (DmgrOpen((HIF*) hifPtr, _dvc->szConn) == 0)
    throw gcnew ConnectionException("Failed to connect to the device!");
}

void Device::Close() {
  if (!IsOpened)
    throw gcnew InvalidOperationException("Device is not opened!");

  if (IsBusy)
    throw gcnew DeviceBusyException();

  if (DmgrClose(_hif) == 0)
    throw gcnew ConnectionException("Failed to close the device!");

  _hif = hifInvalid;
}

Device::~Device() {
  if (IsOpened)
    Close();
  delete _dvc;
}
