using System.Runtime.InteropServices;

namespace UnrealEngine
{
    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public partial struct Color
    {
        [FieldOffset(0)]
        public byte B;
        [FieldOffset(1)]
        public byte G;
        [FieldOffset(2)]
        public byte R;
        [FieldOffset(3)]
        public byte A;

    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public partial struct LinearColor
    {
        [FieldOffset(0)]
        public float R;
        [FieldOffset(4)]
        public float G;
        [FieldOffset(8)]
        public float B;
        [FieldOffset(12)]
        public float A;

    }

    [StructLayout(LayoutKind.Explicit, Size = 64)]
    public partial struct Matrix
    {
        [FieldOffset(0)]
        public Plane XPlane;
        [FieldOffset(16)]
        public Plane YPlane;
        [FieldOffset(32)]
        public Plane ZPlane;
        [FieldOffset(48)]
        public Plane WPlane;

    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public partial struct Plane
    {
        [FieldOffset(12)]
        public float W;
        [FieldOffset(0)]
        public float X;
        [FieldOffset(4)]
        public float Y;
        [FieldOffset(8)]
        public float Z;

    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public partial struct Quat
    {
        [FieldOffset(0)]
        public float X;
        [FieldOffset(4)]
        public float Y;
        [FieldOffset(8)]
        public float Z;
        [FieldOffset(12)]
        public float W;

    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public partial struct Rotator
    {
        [FieldOffset(0)]
        public float Pitch;
        [FieldOffset(4)]
        public float Yaw;
        [FieldOffset(8)]
        public float Roll;

    }

    [StructLayout(LayoutKind.Explicit, Size = 48)]
    public partial struct Transform
    {
        [FieldOffset(0)]
        public Quat Rotation;
        [FieldOffset(16)]
        public Vector Translation;
        [FieldOffset(32)]
        public Vector Scale3D;

    }
    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public partial struct Vector
    {
        [FieldOffset(0)]
        public float X;
        [FieldOffset(4)]
        public float Y;
        [FieldOffset(8)]
        public float Z;
    }
    [StructLayout(LayoutKind.Explicit, Size = 8)]
    public partial struct Vector2D
    {
        [FieldOffset(0)]
        public float X;
        [FieldOffset(4)]
        public float Y;

    }

    [StructLayout(LayoutKind.Explicit, Size = 16)]
    public partial struct Vector4D
    {
        [FieldOffset(0)]
        public float X;
        [FieldOffset(4)]
        public float Y;
        [FieldOffset(8)]
        public float Z;
        [FieldOffset(12)]
        public float W;

    }
}
