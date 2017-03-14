using System.Runtime.InteropServices;

namespace UnrealEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector2
    {
        public float X;
        public float Y;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Vector3
    {
        public float X;
        public float Y;
        public float Z;
    }

    // TODO: The FVector4 class is 16-byte aligned, but the mirror FVector4 USTRUCT is not,
    //       which one of those is this struct actually going to correspond to? And does it matter?
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector4
    {
        public float X;
        public float Y;
        public float Z;
        public float W;
    }

    // TODO: Check the alignment is correct
    [StructLayout(LayoutKind.Sequential)]
    public struct Quaternion
    {
        public float X;
        public float Y;
        public float Z;
        public float W;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Transform
    {
        public Quaternion Rotation;
        public Vector3  Position;
        public Vector3  Scale;
    }

    // TODO: Check the alignment is correct
    [StructLayout(LayoutKind.Sequential)]
    public struct Color
    {
        public byte B, G, R, A;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct LinearColor
    {
        public float B, G, R, A;
    }
}
