using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class SkinnedMeshComponent : MeshComponent
    {
        public int GetBoneIndex(string BoneName)
        {
            return _GetBoneIndex(NativeHandler,BoneName);
        }
      
        public string GetBoneName(int BoneIndex)
        {
            return _GetBoneName(NativeHandler,BoneIndex);
        }
        
        public string GetSocketBoneName(string InSocketName)
        {
            return _GetSocketBoneName(NativeHandler,InSocketName);
        }
       
        public string GetParentBone(string BoneName)
        {
            return _GetParentBone(NativeHandler,BoneName);
        }
        
        public Matrix GetBoneMatrix(int BoneIndex)
        {
            return _GetBoneMatrix(NativeHandler,BoneIndex);
        }
        
        public Transform GetBoneTransform(int BoneIndex, Transform LocalToWorld)
        {
            return _GetBoneTransform0(NativeHandler,BoneIndex,LocalToWorld);
        }
       
        public Transform GetBoneTransform(int BoneIndex)
        {
            return _GetBoneTransform1(NativeHandler,BoneIndex);
        }
        
        public Quat GetBoneQuaternion(string BoneName, EBoneSpaces space = EBoneSpaces.WorldSpace)
        {
            return _GetBoneQuaternion(NativeHandler,BoneName,space);
        }        

        public Vector GetBoneLocation(string BoneName, EBoneSpaces Space = EBoneSpaces.WorldSpace)
        {
            return _GetBoneLocation(NativeHandler,BoneName,Space);
        }

        public void HideBoneByName(string BoneName, EPhysBodyOp PhysBodyOption)
        {
            _HideBoneByName(NativeHandler, BoneName, PhysBodyOption);
        }  
        
        public void UnHideBoneByName(string BoneName)
        {
            _UnHideBoneByName(NativeHandler, BoneName);
        }
        
        public bool IsBoneHiddenByName(string BoneName)
        {
            return _IsBoneHiddenByName(NativeHandler,BoneName);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static int _GetBoneIndex(IntPtr handler, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static string _GetBoneName(IntPtr handler, int BoneIndex);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static string _GetSocketBoneName(IntPtr handler, string InSocketName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static string _GetParentBone(IntPtr handler, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Matrix _GetBoneMatrix(IntPtr handler, int BoneIndex);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Transform _GetBoneTransform0(IntPtr handler, int BoneIndex, Transform LocalToWorld);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Transform _GetBoneTransform1(IntPtr handler, int BoneIndex);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Quat _GetBoneQuaternion(IntPtr handler, string BoneName, EBoneSpaces space);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Vector _GetBoneLocation(IntPtr handler, string BoneName, EBoneSpaces Space);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _HideBoneByName(IntPtr handler, string BoneName, EPhysBodyOp PhysBodyOption);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _UnHideBoneByName(IntPtr handler, string BoneName);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static bool _IsBoneHiddenByName(IntPtr handler, string BoneName);

    }
}
