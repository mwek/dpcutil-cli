using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using dpcutil;

namespace dpcutil.test
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(DeviceManager.Version);
            Device[] dvcs = DeviceManager.Enumerate();
            if (dvcs != null)
                Console.WriteLine(dvcs.Length);
            foreach (Device d in dvcs)
                Console.WriteLine(d.Name + " " + d.Connection + " " + d.DTP);
            Console.WriteLine(dvcs[0].IsOpened);
            dvcs[0].Open();
            Console.WriteLine(dvcs[0].IsOpened);
            DEPP depp = new DEPP(dvcs[0]);
            Console.WriteLine(dvcs[0].IsBusy);
            depp.Enable();
            Console.WriteLine(dvcs[0].IsBusy);
            for (int i = 0; i < 16; ++i)
                Console.WriteLine(i + ": " + depp.GetReg((byte) i));

            for (int i = 1; i < 5; ++i)
                depp.PutReg((byte)i, 255);

            byte[] addrs = new byte[16];
            for (int i = 0; i < addrs.Length; ++i)
                addrs[i] = (byte)i;
            byte[] vals = depp.GetRegs(addrs);

            for (int i = 0; i < addrs.Length; ++i)
            {
                byte single = depp.GetReg((byte)i);
                if (single != vals[i])
                    Console.WriteLine("Differs at " + i + ": " + single + " vs " + vals[i]);
            }

            for (int i = 0; i < 16; ++i)
                Console.WriteLine(i + ": " + depp.GetReg((byte)i));

            depp.Disable();
            Console.WriteLine(dvcs[0].IsBusy);
            dvcs[0].Close();
            Console.WriteLine(dvcs[0].IsOpened);
            Console.ReadKey();
        }
    }
}
