namespace UnrealEngine
{
    public partial struct Color
    {
        /** Some pre-inited colors, useful for debug code */
        static public readonly Color White = new Color(255,255,255);
        static public readonly Color Black = new Color(0, 0, 0);
        static public readonly Color Transparent = new Color(0, 0, 0, 0);
        static public readonly Color Red = new Color(255, 0, 0);
        static public readonly Color Green = new Color(0, 255, 0);
        static public readonly Color Blue = new Color(0, 0, 255);
        static public readonly Color Yellow = new Color(255, 255, 0);
        static public readonly Color Cyan = new Color(0, 255, 255);
        static public readonly Color Magenta = new Color(255, 0, 255);
        static public readonly Color Orange = new Color(243, 156, 18);
        static public readonly Color Purple = new Color(169, 7, 228);
        static public readonly Color Turquoise = new Color(26, 188, 156);
        static public readonly Color Silver = new Color(189, 195, 199);
        static public readonly Color Emerald = new Color(46, 204, 113);

        public Color(byte r, byte g, byte b,byte a=255) { this.R = r; G = g; B = b; A = a; }
    }
}
