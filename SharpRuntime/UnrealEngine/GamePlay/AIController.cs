using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class AIController : Controller
    {
        public PathFollowingStatus MoveStatus
        {
            get
            {
                return _GetMoveStatus(NativeHandler);
            }
        }

        public bool HasPartialPath
        {
            get
            {
                return _GetHasPartialPath(NativeHandler);
            }
        }

        public Vector ImmediateMoveDestination
        {
            get
            {
                return _GetImmediateMoveDestination(NativeHandler);
            }
        }

        public Vector FocalPoint
        {
            get
            {
                return _GetFocalPoint(NativeHandler);
            }
            set
            {
                _SetFocalPoint(NativeHandler, value);
            }
        }

        public Actor FocusActor
        {
            get
            {
                var handle = _GetFocusActor(NativeHandler);
                if (handle.ToInt64() != 0)
                {
                    var actor = new Actor();
                    actor.NativeHandler = handle;
                    return actor;
                }
                else { return null; }
            }
            set
            {
                _SetFocusActor(NativeHandler, value.NativeHandler);
            }
        }

        public PathFollowingReqResult MoveToActor(Actor actor, float accepanceRadius, bool stopOnOverlap, bool usePathfinding, bool bCanStrafe, bool allowPartialPath)
        {
            return _MoveToActor(NativeHandler, actor.NativeHandler, accepanceRadius, stopOnOverlap, usePathfinding, bCanStrafe, allowPartialPath);
        }

        public PathFollowingReqResult MoveToLocation(Vector actor, float accepanceRadius, bool stopOnOverlap, bool usePathfinding, bool bProjectDestinationToNavigation, bool bCanStrafe, bool allowPartialPath)
        {
            return _MoveToLocation(NativeHandler, actor, accepanceRadius, stopOnOverlap, usePathfinding, bProjectDestinationToNavigation, bCanStrafe, allowPartialPath);
        }

        public Vector GetFocalPointOnActor(Actor actor)
        {
            return _GetFocalPointOnActor(NativeHandler, actor.NativeHandler);
        }

        public void SetMoveBlockDetection(bool value)
        {
            _SetMoveBlockDetection(NativeHandler, value);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static PathFollowingStatus _GetMoveStatus(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _GetHasPartialPath(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetImmediateMoveDestination(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetFocalPoint(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetFocalPoint(IntPtr handler, Vector FocalPoint);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static IntPtr _GetFocusActor(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetFocusActor(IntPtr handler, IntPtr FocusActor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static PathFollowingReqResult _MoveToActor(IntPtr handler, IntPtr actor, float accepanceRadius, bool stopOnOverlap, bool usePathfinding, bool bCanStrafe, bool allowPartialPath);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static PathFollowingReqResult _MoveToLocation(IntPtr handler, Vector actor, float accepanceRadius, bool stopOnOverlap, bool usePathfinding, bool bProjectDestinationToNavigation, bool bCanStrafe, bool allowPartialPath);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetFocalPointOnActor(IntPtr handler, IntPtr actor);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _SetMoveBlockDetection(IntPtr handler, bool value);
    }
}
