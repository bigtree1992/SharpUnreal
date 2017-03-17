using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnrealEngine
{
    public class SubEntry
    {
        private string _strproperty;
        public string strproperty
        {
            get
            {
                return _strproperty;
            }

            set
            {
                _strproperty = value;
            }
        }

        public void Hello()
        {
            Console.WriteLine("[Test] Hello");
        }
    }

    public class MainEntry
    {

        public MainEntry()
        {
            subEntry = new SubEntry();
            Console.WriteLine("[Test] MainEntry .ctor called!");
        }

        public int intfield;

        private int _intproperty;

        public int intproperty
        {
            get
            {
                return _intproperty;
            }

            set
            {
                _intproperty = value;
            }
        }

        public string strfield;

        private string _strproperty;

        public string strproperty
        {
            get
            {
                return _strproperty;
            }

            set
            {
                _strproperty = value;
            }
        }

        public void Hello()
        {
            Console.WriteLine("[Test] Hello");
        }

        public void HelloWithStr(string info)
        {
            Console.WriteLine("[Test] HelloWithStr : " + info);
        }

        public void HelloWithNum(int num)
        {
            Console.WriteLine("[Test] HelloWithNum num: " + num);
        }

        public int HelloWithReturn()
        {
            return 1;
        }

        public string HelloWithReturnStr()
        {
            return "C++ Return Str!";
        }

        public SubEntry subEntry;
        private IntPtr native_handle;

    }
}
