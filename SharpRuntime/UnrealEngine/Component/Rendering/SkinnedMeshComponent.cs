using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class SkinnedMeshComponent : MeshComponent
    {
        public int GetBoneIndex(string BoneName)
        {
            return 0;
        }
        public string GetBoneName(int BoneIndex)
        {
            return "";
        }

        public string GetSocketBoneName(string InSocketName)
        {
            return "";
        }
        public string GetParentBone(string BoneName)
        {
            return "";
        }

        public Matrix GetBoneMatrix(int BoneIndex)
        {
            return Matrix.Identity;
        }

        public Transform GetBoneTransform(int BoneIndex, Transform LocalToWorld)
        {
            return Transform.Identity;
        }

        public Transform GetBoneTransform(int BoneIndex)
        {
            return Transform.Identity;
        }

        public enum EBoneSpaces
        {
            /** Set absolute position of bone in world space. */
            WorldSpace,
            /** Set position of bone in components reference frame. */
            ComponentSpace
            /** Set position of bone relative to parent bone. */
            //LocalSpace		UMETA( DisplayName = "Parent Bone Space" ),
        };
        public Quat GetBoneQuaternion(string BoneName, EBoneSpaces space = EBoneSpaces.WorldSpace)
        {
            return Quat.Identity;
        }

        public Vector GetBoneLocation(string BoneName, EBoneSpaces Space = EBoneSpaces.WorldSpace)
        {
            return Vector.ZeroVector;
        }

        public enum EPhysBodyOp
        {
            /** Don't do anything. */
            PBO_None,
            /** Terminate - if you terminate, you won't be able to re-init when unhidden. */
            PBO_Term,
            /** Disable collision - it will enable collision when unhidden. */
            PBO_Disable,
            PBO_MAX
        };

        public void HideBoneByName(string BoneName, EPhysBodyOp PhysBodyOption)
        {

        }

        public void UnHideBoneByName(string BoneName)
        {

        }

        public bool IsBoneHiddenByName(string BoneName)
        {
            return false;
        }
    }
}
