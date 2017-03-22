using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class DynamicMaterial : MaterialInstance
    {
        public DynamicMaterial(IntPtr handler) : base(handler)
        {
        }

        public static DynamicMaterial Create(MaterialInstance instance,UObject outer)
        {
            return null;
        }

        public float GetScalarParameter(string name)
        {
            return 0.0f;
        }

        public void SetScalarParameter(string name,float value)
        {

        }

        public LinearColor GetVectorParameter(string name)
        {
            return LinearColor.Black;
        }

        public void SetVectorParameter(string name, LinearColor value)
        {

        }
    }
}
