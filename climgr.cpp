#include "Stdafx.h"
#include "climgr.h"
#include "helpers.h"

#include "dpcutil/dpcdecl.h"
#include "dpcutil/dmgr.h"

using namespace helpers;
using namespace dpcutil;

String^ DeviceManager::Version::get() {
	if (_version == nullptr) {
		char* versionChars = new char[cchVersionMax];
		if (DmgrGetVersion(versionChars) == 0)
			_version = nullptr;
		else
			_version = CharArrayToString(versionChars);
		delete[] versionChars;
	}
	return _version;
}

array<Device^>^ DeviceManager::Enumerate() {
	int dvcs;
	DmgrFreeDvcEnum();
	if (DmgrEnumDevices(&dvcs) == 0)
		return nullptr;

	array<Device^>^ devices = gcnew array<Device^>(dvcs);

	for (int i = 0; i < dvcs; ++i)
		devices[i] = gcnew Device(i);

	return devices;
}
