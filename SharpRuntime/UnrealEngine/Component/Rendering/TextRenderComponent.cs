using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class TextRenderComponent : PrimitiveComponent
    {
        public string Text
        {
            get;
            set;
        }

        public Color Color
        {
            get;
            set;
        }

        public float XScale
        {
            get;
            set;
        }

        public float YScale
        {
            get;
            set;
        }

        public float WorldSize
        {
            get;
            set;
        }

        public Material Material
        {
            get;
            set;
        }
    }
}
