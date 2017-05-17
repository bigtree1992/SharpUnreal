using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class SplineMeshComponent : StaticMeshComponent
    {
        public Vector StartPosition
        {
            get
            {
                return _GetStartPosition(NativeHandler);
            }
            set
            {
                _SetStartPosition(NativeHandler, value);
            }
        }

        public Vector StartTangent
        {
            get
            {
                return _GetStartTangent(NativeHandler);
            }
            set
            {
                _SetStartTangent(NativeHandler, value);
            }
        }

        public Vector EndPosition
        {
            get
            {
                return _GetEndPosition(NativeHandler);
            }
            set
            {
                _SetEndPosition(NativeHandler, value);
            }
        }

        public Vector EndTangent
        {
            get
            {
                return _GetEndTangent(NativeHandler);
            }
            set
            {
                _SetEndTangent(NativeHandler, value);
            }
        }

        public Vector2D StartScale
        {
            get
            {
                return _GetStartScale(NativeHandler);
            }
            set
            {
                _SetStartScale(NativeHandler, value);
            }
        }

        public float StartRoll
        {
            get
            {
                return _GetStartRoll(NativeHandler);
            }
            set
            {
                _SetStartRoll(NativeHandler, value);
            }
        }

        public Vector2D StartOffset
        {
            get
            {
                return _GetStartOffset(NativeHandler);
            }
            set
            {
                _SetStartOffset(NativeHandler, value);
            }
        }

        public Vector2D EndScale
        {
            get
            {
                return _GetEndScale(NativeHandler);
            }
            set
            {
                _SetEndScale(NativeHandler, value);
            }
        }

        public float GetEndRoll
        {
            get
            {
                return _GetEndRoll(NativeHandler);
            }
            set
            {
                _SetEndRoll(NativeHandler, value);
            }
        }

        public Vector2D EndOffset
        {
            get
            {
                return _GetEndOffset(NativeHandler);
            }
            set
            {
                _SetEndOffset(NativeHandler, value);
            }
        }

        public SplineMeshAxis ForwardAxis
        {
            get
            {
                return _GetForwardAxis(NativeHandler);
            }
            set
            {
                _SetForwardAxis(NativeHandler, value);
            }
        }

        public Vector SplineUpDir
        {
            get
            {
                return _GetSplineUpDir(NativeHandler);
            }
            set
            {
                _SetSplineUpDir(NativeHandler, value);
            }
        }

        public float BoundaryMin
        {
            get
            {
                return _GetBoundaryMin(NativeHandler);
            }
            set
            {
                _SetBoundaryMin(NativeHandler, value);
            }
        }

        public float BoundaryMax
        {
            get
            {
                return _GetBoundaryMax(NativeHandler);
            }
            set
            {
                _SetBoundaryMax(NativeHandler, value);
            }
        }

        public void UpdateMesh()
        {
            _UpdateMesh(NativeHandler);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetStartPosition(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetStartPosition(IntPtr handler, Vector StartPosition);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetStartTangent(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetStartTangent(IntPtr handler, Vector StartTangent);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetEndPosition(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetEndPosition(IntPtr handler, Vector EndPosition);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetEndTangent(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetEndTangent(IntPtr handler, Vector EndTangent);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector2D _GetStartScale(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetStartScale(IntPtr handler, Vector2D StartScale);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetStartRoll(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetStartRoll(IntPtr handler, float StartRoll);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector2D _GetStartOffset(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetStartOffset(IntPtr handler, Vector2D StartOffset);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector2D _GetEndScale(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetEndScale(IntPtr handler, Vector2D EndScale);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetEndRoll(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetEndRoll(IntPtr handler, float GetEndRoll);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector2D _GetEndOffset(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetEndOffset(IntPtr handler, Vector2D EndOffset);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static SplineMeshAxis _GetForwardAxis(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetForwardAxis(IntPtr handler, SplineMeshAxis ForwardAxis);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetSplineUpDir(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetSplineUpDir(IntPtr handler, Vector SplineUpDir);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetBoundaryMin(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBoundaryMin(IntPtr handler, float BoundaryMin);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetBoundaryMax(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetBoundaryMax(IntPtr handler, float BoundaryMax);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _UpdateMesh(IntPtr handler);
    }
}
