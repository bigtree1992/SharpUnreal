using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class Property : UObject
    {
        public IntPtr ActorHandler
        {
            get;
            set;
        }
    }

    public class IntProperty : Property
    {
        public int Value
        {
            get
            {
                return _GetValue(ActorHandler, NativeHandler);
            }
            set
            {
                _SetValue(ActorHandler, NativeHandler, value);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static int _GetValue(IntPtr actor, IntPtr property);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetValue(IntPtr actor, IntPtr property,int value);
    }

    public class FloatProperty : Property
    {
        public float Value
        {
            get
            {
                return _GetValue(ActorHandler, NativeHandler);
            }
            set
            {
                _SetValue(ActorHandler, NativeHandler, value);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetValue(IntPtr actor, IntPtr property);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetValue(IntPtr actor, IntPtr property, float value);
    }

    public class StringProperty : Property
    {
        public string Value
        {
            get
            {
                return _GetValue(ActorHandler, NativeHandler);
            }
            set
            {
                _SetValue(ActorHandler, NativeHandler, value);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static string _GetValue(IntPtr actor, IntPtr property);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetValue(IntPtr actor, IntPtr property, string value);
    }

    public class VectorProperty : Property
    {
        public Vector Value
        {
            get
            {
                return _GetValue(ActorHandler, NativeHandler);
            }
            set
            {
                _SetValue(ActorHandler, NativeHandler, value);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetValue(IntPtr actor, IntPtr property);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetValue(IntPtr actor, IntPtr property, Vector value);
    }

    public class QuatProperty : Property
    {
        public Quat Value
        {
            get
            {
                return _GetValue(ActorHandler, NativeHandler);
            }
            set
            {
                _SetValue(ActorHandler, NativeHandler, value);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Quat _GetValue(IntPtr actor, IntPtr property);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetValue(IntPtr actor, IntPtr property, Quat value);
    }

    public class RotatorProperty : Property
    {
        public Rotator Value
        {
            get
            {
                return _GetValue(ActorHandler, NativeHandler);
            }
            set
            {
                _SetValue(ActorHandler, NativeHandler, value);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Rotator _GetValue(IntPtr actor, IntPtr property);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetValue(IntPtr actor, IntPtr property, Rotator value);
    }

    public class TransformProperty : Property
    {
        public Transform Value
        {
            get
            {
                return _GetValue(ActorHandler, NativeHandler);
            }
            set
            {
                _SetValue(ActorHandler, NativeHandler, value);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Transform _GetValue(IntPtr actor, IntPtr property);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetValue(IntPtr actor, IntPtr property, Transform value);
    }
}
