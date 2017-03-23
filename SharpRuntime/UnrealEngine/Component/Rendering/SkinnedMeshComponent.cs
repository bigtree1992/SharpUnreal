using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class SkinnedMeshComponent : MeshComponent
    {
        public int GetBoneIndex(string BoneName)
        {
            return _GetBoneIndex(m_NativeHandler,BoneName);
        }
      
        public string GetBoneName(int BoneIndex)
        {
            return _GetBoneName(m_NativeHandler,BoneIndex);
        }
        
        public string GetSocketBoneName(string InSocketName)
        {
            return _GetSocketBoneName(m_NativeHandler,InSocketName);
        }
       
        public string GetParentBone(string BoneName)
        {
            return _GetParentBone(m_NativeHandler,BoneName);
        }
        
        public Matrix GetBoneMatrix(int BoneIndex)
        {
            return _GetBoneMatrix(m_NativeHandler,BoneIndex);
        }
        
        public Transform GetBoneTransform(int BoneIndex, Transform LocalToWorld)
        {
            return _GetBoneTransform(m_NativeHandler,BoneIndex,LocalToWorld);
        }
       
        public Transform GetBoneTransform(int BoneIndex)
        {
            return _GetBoneTransform(m_NativeHandler,BoneIndex);
        }
        
        public Quat GetBoneQuaternion(string BoneName, EBoneSpaces space = EBoneSpaces.WorldSpace)
        {
            return _GetBoneQuaternion(m_NativeHandler,BoneName,space);
        }        

        public Vector GetBoneLocation(string BoneName, EBoneSpaces Space = EBoneSpaces.WorldSpace)
        {
            return _GetBoneLocation(m_NativeHandler,BoneName,Space);
        }

        public void HideBoneByName(string BoneName, EPhysBodyOp PhysBodyOption)
        {
            _HideBoneByName(m_NativeHandler, BoneName, PhysBodyOption);
        }  
        
        public void UnHideBoneByName(string BoneName)
        {
            _UnHideBoneByName(m_NativeHandler, BoneName);
        }
        
        public bool IsBoneHiddenByName(string BoneName)
        {
            return _IsBoneHiddenByName(m_NativeHandler,BoneName);
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
        private extern static Transform _GetBoneTransform(IntPtr handler, int BoneIndex, Transform LocalToWorld);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static Transform _GetBoneTransform(IntPtr handler, int BoneIndex);
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
