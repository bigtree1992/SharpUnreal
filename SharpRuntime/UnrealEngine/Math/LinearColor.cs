namespace UnrealEngine
{
    public partial struct LinearColor
    {
        // Common colors.	
        static public readonly LinearColor White = new LinearColor(1.0f, 1.0f, 1.0f);
        static public readonly LinearColor Gray = new LinearColor(0.5f, 0.5f, 0.5f);
        static public readonly LinearColor Black = new LinearColor(0, 0, 0);
        static public readonly LinearColor Transparent = new LinearColor(0, 0, 0, 0);
        static public readonly LinearColor Red = new LinearColor(1.0f, 0, 0);
        static public readonly LinearColor Green = new LinearColor(0, 1.0f, 0);
        static public readonly LinearColor Blue = new LinearColor(0, 0, 1.0f);
        static public readonly LinearColor Yellow = new LinearColor(1.0f, 1.0f, 0);

        public LinearColor(float InR, float InG, float InB, float InA = 1.0f)
        {
            R = (InR);
            G = (InG);
            B = (InB);
            A = (InA);
        }
        public LinearColor(Color Color)
        {
            R = Color.R / 255.0f;
            G = Color.G / 255.0f;
            B = Color.B / 255.0f;
            A = Color.A / 255.0f;
        }

        public static implicit operator Color(LinearColor Color)
        {
            return Color.ToFColor();
        }
        public static implicit operator LinearColor(Color Color)
        {
            return new LinearColor(Color);
        }

        public Color ToFColor()
        {
            return new Color((byte)(R * 255), (byte)(G * 255), (byte)(B * 255), (byte)(A * 255));
        }

        public static LinearColor operator +(LinearColor ColorA, LinearColor ColorB)
        {
            return new LinearColor(
                 ColorA.R + ColorB.R,
                 ColorA.G + ColorB.G,
                 ColorA.B + ColorB.B,
                 ColorA.A + ColorB.A
                );
        }


        public static LinearColor operator -(LinearColor ColorA, LinearColor ColorB)
        {
            return new LinearColor(
                ColorA.R - ColorB.R,
                ColorA.G - ColorB.G,
                ColorA.B - ColorB.B,
                ColorA.A - ColorB.A
                );
        }

        public static LinearColor operator *(LinearColor ColorA, LinearColor ColorB)
        {
            return new LinearColor(
                ColorA.R * ColorB.R,
                ColorA.G * ColorB.G,
                ColorA.B * ColorB.B,
                ColorA.A * ColorB.A
                );
        }

        public static LinearColor operator *(LinearColor ColorA, float Scalar)
        {
            return new LinearColor(
                ColorA.R * Scalar,
                ColorA.G * Scalar,
                ColorA.B * Scalar,
                ColorA.A * Scalar
                );
        }


        public static LinearColor operator /(LinearColor ColorA, LinearColor ColorB)
        {
            return new LinearColor(
                ColorA.R / ColorB.R,
                ColorA.G / ColorB.G,
                ColorA.B / ColorB.B,
                ColorA.A / ColorB.A
                );
        }

        public static LinearColor operator /(LinearColor ColorA, float Scalar)
        {
            float InvScalar = 1.0f / Scalar;
            return new LinearColor(
                ColorA.R * InvScalar,
                ColorA.G * InvScalar,
                ColorA.B * InvScalar,
                ColorA.A * InvScalar
                );
        }
    }
}
