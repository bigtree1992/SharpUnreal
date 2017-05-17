using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class SplineComponent : PrimitiveComponent
    {
        public float Duration
        {
            get
            {
                return _GetDuration(NativeHandler);
            }
            set
            {
                _SetDuration(NativeHandler, value);
            }
        }

        public bool DrawDebug
        {
            get
            {
                return _GetDrawDebug(NativeHandler);
            }
            set
            {
                _SetDrawDebug(NativeHandler, value);
            }
        }

        public Vector DefaultUpVector
        {
            get
            {
                return _GetDefaultUpVector(NativeHandler);
            }
            set
            {
                _SetDefaultUpVector(NativeHandler, value);
            }
        }

        public LinearColor UnselectedSplineSegmentColor
        {
            set
            {
                _SetUnselectedSplineSegmentColor(NativeHandler, value);
            }
        }

        public LinearColor SelectedSplineSegmentColor
        {
            set
            {
                _SetSelectedSplineSegmentColor(NativeHandler, value);
            }
        }

        public bool ClosedLoop
        {
            get
            {
                return _GetClosedLoop(NativeHandler);
            }
            set
            {
                _SetClosedLoop(NativeHandler, value);
            }
        }

        public int NumberOfSplinePoints
        {
            get
            {
                return _GetNumberOfSplinePoints(NativeHandler);
            }
        }

        public float SplineLength
        {
            get
            {
                return _GetSplineLength(NativeHandler);
            }
        }

        public void UpdateSpline()
        {
            _UpdateSpline(NativeHandler);
        }

        public void SetLocationAtSplinePoint(int PointIndex, Vector InLocation, SplineCoordinateSpace CoordinateSpace, bool bUpdateSpline)
        {
            _SetLocationAtSplinePoint(NativeHandler, PointIndex, InLocation, CoordinateSpace, bUpdateSpline);
        }

        public Transform GetTransformAtSplinePoint(int PointIndex, SplineCoordinateSpace CoordinateSpace, bool bUseScale)
        {
            return _GetTransformAtSplinePoint(NativeHandler, PointIndex, CoordinateSpace, bUseScale);
        }

        public float GetDistanceAlongSplineAtSplinePoint(int PointIndex)
        {
            return _GetDistanceAlongSplineAtSplinePoint(NativeHandler, PointIndex);
        }

        public Transform GetTransformAtDistanceAlongSpline(float Distance, SplineCoordinateSpace CoordinateSpace, bool bUseScale)
        {
            return _GetTransformAtDistanceAlongSpline(NativeHandler, Distance, CoordinateSpace, bUseScale);
        }

        public Transform GetTransformAtTime(float Time, SplineCoordinateSpace CoordinateSpace, bool bUseConstantVelocity, bool bUseScale)
        {
            return _GetTransformAtTime(NativeHandler, Time, CoordinateSpace, bUseConstantVelocity, bUseScale);
        }

        public Transform FindTransformClosestToWorldLocation(Vector WorldLocation, SplineCoordinateSpace CoordinateSpace, bool bUseScale)
        {
            return _FindTransformClosestToWorldLocation(NativeHandler, WorldLocation, CoordinateSpace, bUseScale);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetDuration(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetDuration(IntPtr handler, float Duration);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetDrawDebug(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetDrawDebug(IntPtr handler, bool DrawDebug);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetDefaultUpVector(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetDefaultUpVector(IntPtr handler, Vector DefaultUpVector);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetUnselectedSplineSegmentColor(IntPtr handler, LinearColor UnselectedSplineSegmentColor);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetSelectedSplineSegmentColor(IntPtr handler, LinearColor SelectedSplineSegmentColor);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetClosedLoop(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetClosedLoop(IntPtr handler, bool ClosedLoop);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static int _GetNumberOfSplinePoints(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetSplineLength(IntPtr handler);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _UpdateSpline(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetLocationAtSplinePoint(IntPtr handler, int PointIndex, Vector InLocation, SplineCoordinateSpace CoordinateSpace, bool bUpdateSpline);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Transform _GetTransformAtSplinePoint(IntPtr handler, int PointIndex, SplineCoordinateSpace CoordinateSpace, bool bUseScale);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static float _GetDistanceAlongSplineAtSplinePoint(IntPtr handler, int PointIndex);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Transform _GetTransformAtDistanceAlongSpline(IntPtr handler, float Distance, SplineCoordinateSpace CoordinateSpace, bool bUseScale);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Transform _GetTransformAtTime(IntPtr handler, float Time, SplineCoordinateSpace CoordinateSpace, bool bUseConstantVelocity, bool bUseScale);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Transform _FindTransformClosestToWorldLocation(IntPtr handler, Vector WorldLocation, SplineCoordinateSpace CoordinateSpace, bool bUseScale);
    }
}
