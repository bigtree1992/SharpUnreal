﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class Log
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void Debug(string content);
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void Warning(string content);        
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void Error(string content);

    }
}
