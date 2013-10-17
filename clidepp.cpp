#include "Stdafx.h"
#include "clidepp.h"
#include "helpers.h"

#include "dpcutil/dpcdecl.h"
#include "dpcutil/depp.h"

using namespace helpers;
using namespace dpcutil;

String^ DEPP::Version::get() {
  if (_version == nullptr) {
    char* versionChars = new char[cchVersionMax];
    if (DeppGetVersion(versionChars) == 0)
      _version = nullptr;
    else
      _version = CharArrayToString(versionChars);
    delete[] versionChars;
  }
  return _version;
}

DEPP::DEPP(Device^ dvc) {
  _dvc = dvc;
  _enabled = false;
}

DEPP::~DEPP() {
  if (IsEnabled)
    Disable();
}

bool DEPP::IsEnabled::get() {
  return _enabled;
}

void DEPP::Enable() {
  if (IsEnabled)
    throw gcnew InvalidOperationException("DEPP is already enabled!");

  if (!_dvc->IsOpened) _dvc->Open();

  _dvc->Lock();

  if (DeppEnable(_dvc->_hif) == 0) {
    _dvc->Release();
    throw gcnew ConnectionException("Failed to enable DEPP!");
  }

  _enabled = true;
}

void DEPP::Disable() {
  if (!IsEnabled)
    throw gcnew InvalidOperationException("DEPP isn't enabled!");

  if (DeppDisable(_dvc->_hif) == 0)
    throw gcnew ConnectionException("Failed to disable DEPP!");

  _dvc->Release();
  _enabled = false;
}

void DEPP::PutReg(unsigned char addr, unsigned char value) {
  if (!IsEnabled)
    throw gcnew InvalidOperationException("DEPP isn't enabled!");

  if (DeppPutReg(_dvc->_hif, addr, value, false) == 0)
    throw gcnew ConnectionException("Failed to write register data!");
}

unsigned char DEPP::GetReg(unsigned char addr) {
  if (!IsEnabled)
    throw gcnew InvalidOperationException("DEPP isn't enabled!");

  unsigned char value;

  if (DeppGetReg(_dvc->_hif, addr, &value, false) == 0)
    throw gcnew ConnectionException("Failed to read register data!");

  return value;
}

void DEPP::PutRegs(array<unsigned char>^ addrs, array<unsigned char>^ values) {
  if (!IsEnabled)
    throw gcnew InvalidOperationException("DEPP isn't enabled!");

  if (addrs->Length != values->Length)
    throw gcnew ArgumentException(
      "Address and value arrays have different lengths!");

  unsigned char* avPairs = new unsigned char[addrs->Length * 2];
  for (int i = 0; i < addrs->Length; ++i) {
    avPairs[2 * i] = addrs[i];
    avPairs[2 * i + 1] = values[i];
  }

  int ret = DeppPutRegSet(_dvc->_hif, avPairs, addrs->Length, false);
  delete[] avPairs;

  if (ret == 0)
    throw gcnew ConnectionException("Failed to write register data!");
}

array<unsigned char>^ DEPP::GetRegs(array<unsigned char>^ addrs) {
  if (!IsEnabled)
    throw gcnew InvalidOperationException("DEPP isn't enabled!");

  array<unsigned char>^ values = gcnew array<unsigned char>(addrs->Length);

  pin_ptr<unsigned char> pinnedAddrs = &addrs[0];
  pin_ptr<unsigned char> pinnedValues = &values[0];
  int ret = DeppGetRegSet(_dvc->_hif, (unsigned char*) pinnedAddrs,
                          (unsigned char*) pinnedValues, addrs->Length, false);

  if (ret == 0)
    throw gcnew ConnectionException("Failed to read register data!");

  return values;
}
