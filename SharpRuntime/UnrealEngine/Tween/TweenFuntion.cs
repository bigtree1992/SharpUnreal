using System;

namespace UnrealEngine
{
    internal static class TweenFunction
    {
        internal static Func<float, float, float, float, float> GetTweenFuncByType(EaseType type)
        {
            switch (type)
            {
                case EaseType.Linear:
                    return TweenFunction.LinearEaseNone;
                case EaseType.SineIn:
                    return TweenFunction.SinEaseIn;
                case EaseType.SineOut:
                    return TweenFunction.SinEaseOut;
                case EaseType.SineInOut:
                    return TweenFunction.SinEaseInOut;
                case EaseType.QuadIn:
                    return TweenFunction.QuadEaseIn;
                case EaseType.QuadOut:
                    return TweenFunction.QuadEaseOut;
                case EaseType.QuadInOut:
                    return TweenFunction.QuadEaseInOut;
                case EaseType.CubicIn:
                    return TweenFunction.CubicEaseIn;
                case EaseType.CubicOut:
                    return TweenFunction.CubicEaseOut;
                case EaseType.CubicInOut:
                    return TweenFunction.CubicEaseInOut;
                case EaseType.QuartIn:
                    return TweenFunction.QuartEaseIn;
                case EaseType.QuartOut:
                    return TweenFunction.QuartEaseOut;
                case EaseType.QuartInOut:
                    return TweenFunction.QuartEaseInOut;
                case EaseType.QuintIn:
                    return TweenFunction.QuintEaseIn;
                case EaseType.QuintOut:
                    return TweenFunction.QuintEaseOut;
                case EaseType.QuintInOut:
                    return TweenFunction.QuintEaseInOut;
                case EaseType.ExpoIn:
                    return TweenFunction.ExpEaseIn;
                case EaseType.ExpoOut:
                    return TweenFunction.ExpEaseOut;
                case EaseType.ExpoInOut:
                    return TweenFunction.ExpEaseInOut;
                case EaseType.CircIn:
                    return TweenFunction.CircularEaseIn;
                case EaseType.CircOut:
                    return TweenFunction.CircularEaseOut;
                case EaseType.CircInOut:
                    return TweenFunction.CircularEaseInOut;
                case EaseType.ElasticIn:
                    return TweenFunction.ElasticEaseIn;
                case EaseType.ElasticOut:
                    return TweenFunction.ElasticEaseOut;
                case EaseType.ElasticInOut:
                    return TweenFunction.ElasticEaseInOut;
                case EaseType.Punch:
                    return TweenFunction.Punch;
                case EaseType.BackIn:
                    return TweenFunction.BackEaseIn;
                case EaseType.BackOut:
                    return TweenFunction.BackEaseOut;
                case EaseType.BackInOut:
                    return TweenFunction.BackEaseInOut;
                case EaseType.BounceIn:
                    return TweenFunction.BounceEaseIn;
                case EaseType.BounceOut:
                    return TweenFunction.BounceEaseOut;
                case EaseType.BounceInOut:
                    return TweenFunction.BounceEaseInOut;
            }

            return TweenFunction.LinearEaseNone;
            
        }

        internal static float LinearEaseNone(float t, float b, float c, float d)
        {
            return c * t / d + b;
        }

        internal static float SinEaseIn(float t, float b, float c, float d)
        {
            return -c * (float)System.Math.Cos(t / d * (System.Math.PI / 2)) + c + b;
        }

        internal static float SinEaseOut(float t, float b, float c, float d)
        {
            return c * (float)System.Math.Sin(t / d * (System.Math.PI / 2)) + b;
        }

        internal static float SinEaseInOut(float t, float b, float c, float d)
        {
            return -c / 2 * ((float)System.Math.Cos(System.Math.PI * t / d) - 1) + b;
        }

        internal static float QuadEaseIn(float t, float b, float c, float d)
        {
            return c * (t /= d) * t + b;
        }

        internal static float QuadEaseOut(float t, float b, float c, float d)
        {
            return -c * (t /= d) * (t - 2) + b;
        }

        internal static float QuadEaseInOut(float t, float b, float c, float d)
        {
            if ((t /= d / 2) < 1)
            {
                return c / 2 * t * t + b;
            }
            return -c / 2 * ((--t) * (t - 2) - 1) + b;
        }

        internal static float CubicEaseIn(float t, float b, float c, float d)
        {
            return c * (t /= d) * t * t + b;
        }

        internal static float CubicEaseOut(float t, float b, float c, float d)
        {
            return c * ((t = t / d - 1) * t * t + 1) + b;
        }

        internal static float CubicEaseInOut(float t, float b, float c, float d)
        {
            if ((t /= d / 2) < 1)
            {
                return c / 2 * t * t * t + b;
            }
            return c / 2 * ((t -= 2) * t * t + 2) + b;
        }

        internal static float QuartEaseIn(float t, float b, float c, float d)
        {
            return c * (t /= d) * t * t * t + b;
        }

        internal static float QuartEaseOut(float t, float b, float c, float d)
        {
            return -c * ((t = t / d - 1) * t * t * t - 1) + b;
        }

        internal static float QuartEaseInOut(float t, float b, float c, float d)
        {
            if ((t /= d / 2) < 1)
            {
                return c / 2 * t * t * t * t + b;
            }
            return -c / 2 * ((t -= 2) * t * t * t - 2) + b;
        }

        internal static float QuintEaseIn(float t, float b, float c, float d)
        {
            return c * (t /= d) * t * t * t * t + b;
        }

        internal static float QuintEaseOut(float t, float b, float c, float d)
        {
            return c * ((t = t / d - 1) * t * t * t * t + 1) + b;
        }

        internal static float QuintEaseInOut(float t, float b, float c, float d)
        {
            if ((t /= d / 2) < 1)
            {
                return c / 2 * t * t * t * t * t + b;
            }
            return c / 2 * ((t -= 2) * t * t * t * t + 2) + b;
        }

        internal static float ExpEaseIn(float t, float b, float c, float d)
        {
            return (t == 0) ? b : c * (float)System.Math.Pow(2, 10 * (t / d - 1)) + b;
        }

        internal static float ExpEaseOut(float t, float b, float c, float d)
        {
            return (t == d) ? b + c : c * (float)(-System.Math.Pow(2, -10 * t / d) + 1) + b;
        }

        internal static float ExpEaseInOut(float t, float b, float c, float d)
        {
            if (t == 0)
            {
                return b;
            }
            if (t == d)
            {
                return b + c;
            }
            if ((t /= d / 2) < 1)
            {
                return c / 2 * (float)System.Math.Pow(2, 10 * (t - 1)) + b;
            }
            return c / 2 * (float)(-System.Math.Pow(2, -10 * --t) + 2) + b;
        }

        internal static float CircularEaseIn(float t, float b, float c, float d)
        {
            return -c * ((float)System.Math.Sqrt(1 - (t /= d) * t) - 1) + b;
        }

        internal static float CircularEaseOut(float t, float b, float c, float d)
        {
            return c * (float)System.Math.Sqrt(1 - (t = t / d - 1) * t) + b;
        }

        internal static float CircularEaseInOut(float t, float b, float c, float d)
        {
            if ((t /= d / 2) < 1)
            {
                return -c / 2 * ((float)System.Math.Sqrt(1 - t * t) - 1) + b;
            }
            return c / 2 * ((float)System.Math.Sqrt(1 - (t -= 2) * t) + 1) + b;
        }

        internal static float ElasticEaseIn(float t, float b, float c, float d)
        {
            if (t == 0)
            {
                return b;
            }
            if ((t /= d) == 1)
            {
                return b + c;
            }
            float p = d * .3f;
            float s = p / 4;
            return -(float)(c * System.Math.Pow(2, 10 * (t -= 1)) * System.Math.Sin((t * d - s) * (2 * System.Math.PI) / p)) + b;
        }

        internal static float ElasticEaseOut(float t, float b, float c, float d)
        {
            if (t == 0)
            {
                return b;
            }
            if ((t /= d) == 1)
            {
                return b + c;
            }
            float p = d * .3f;
            float s = p / 4;
            return (float)(c * System.Math.Pow(2, -10 * t) * System.Math.Sin((t * d - s) * (2 * System.Math.PI) / p) + c + b);
        }

        internal static float ElasticEaseInOut(float t, float b, float c, float d)
        {
            if (t == 0)
            {
                return b;
            }
            if ((t /= d / 2) == 2)
            {
                return b + c;
            }
            float p = d * (.3f * 1.5f);
            float a = c;
            float s = p / 4;
            if (t < 1)
            {
                return -.5f * (float)(a * System.Math.Pow(2, 10 * (t -= 1)) * System.Math.Sin((t * d - s) * (2 * System.Math.PI) / p)) + b;
            }
            return (float)(a * System.Math.Pow(2, -10 * (t -= 1)) * System.Math.Sin((t * d - s) * (2 * System.Math.PI) / p) * .5 + c + b);
        }

        internal static float Punch(float t, float b, float c, float d)
        {
            if (t == 0)
                return 0;

            if ((t /= d) == 1)
                return 0;

            const float p = 0.3f;
            return (float)(c * System.Math.Pow(2, -10 * t) * System.Math.Sin(t * (2 * System.Math.PI) / p));
        }

        internal static float BackEaseIn(float t, float b, float c, float d)
        {
            return c * (t /= d) * t * ((1.70158f + 1) * t - 1.70158f) + b;
        }

        internal static float BackEaseOut(float t, float b, float c, float d)
        {
            return c * ((t = t / d - 1) * t * ((1.70158f + 1) * t + 1.70158f) + 1) + b;
        }

        internal static float BackEaseInOut(float t, float b, float c, float d)
        {
            float s = 1.70158f;
            if ((t /= d / 2) < 1)
            {
                return c / 2 * (t * t * (((s *= (1.525f)) + 1) * t - s)) + b;
            }
            return c / 2 * ((t -= 2) * t * (((s *= (1.525f)) + 1) * t + s) + 2) + b;
        }

        internal static float BounceEaseIn(float t, float b, float c, float d)
        {
            return c - BounceEaseOut(d - t, 0, c, d) + b;
        }

        internal static float BounceEaseOut(float t, float b, float c, float d)
        {
            if ((t /= d) < (1 / 2.75))
            {
                return c * (7.5625f * t * t) + b;
            }
            else if (t < (2 / 2.75))
            {
                return c * (7.5625f * (t -= (1.5f / 2.75f)) * t + .75f) + b;
            }
            else if (t < (2.5 / 2.75))
            {
                return c * (7.5625f * (t -= (2.25f / 2.75f)) * t + .9375f) + b;
            }
            else
            {
                return c * (7.5625f * (t -= (2.625f / 2.75f)) * t + .984375f) + b;
            }
        }

        internal static float BounceEaseInOut(float t, float b, float c, float d)
        {
            if (t < d / 2)
                return BounceEaseIn(t * 2, 0, c, d) * 0.5f + b;
            else
                return BounceEaseOut(t * 2 - d, 0, c, d) * .5f + c * 0.5f + b;
        }


    }

}
