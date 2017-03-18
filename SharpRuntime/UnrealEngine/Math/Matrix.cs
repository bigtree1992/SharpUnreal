using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public partial struct Matrix
    {
        public readonly static Matrix Identity = new Matrix(EForceInit.ForceInit);

        public Matrix(EForceInit Init) 
        {
            XPlane = new Plane();
            YPlane = new Plane();
            ZPlane = new Plane();
            WPlane = new Plane();
            SetIdentity(); 
        }

        public Matrix(Plane InX, Plane InY, Plane InZ, Plane InW)
        {
            XPlane = InX;
            YPlane = InY;
            ZPlane = InZ;
            WPlane = InW;
        }

        public Matrix(Vector InX, Vector InY, Vector InZ, Vector InW)
        {
            XPlane = new Plane();
            YPlane = new Plane();
            ZPlane = new Plane();
            WPlane = new Plane();

            this[0, 0] = InX.X; this[0, 1] = InX.Y; this[0, 2] = InX.Z; this[0, 3] = 0.0f;
            this[1, 0] = InY.X; this[1, 1] = InY.Y; this[1, 2] = InY.Z; this[1, 3] = 0.0f;
            this[2, 0] = InZ.X; this[2, 1] = InZ.Y; this[2, 2] = InZ.Z; this[2, 3] = 0.0f;
            this[3, 0] = InW.X; this[3, 1] = InW.Y; this[3, 2] = InW.Z; this[3, 3] = 1.0f;
        }

        public float this[int Index1,int Index2]
        {
            get
            {
                switch(Index1)
                {
                    case 0:
                        return XPlane[Index2];
                    case 1:
                        return YPlane[Index2];
                    case 2:
                        return ZPlane[Index2];
                    case 3:
                        return WPlane[Index2];
                    default:
                        throw new IndexOutOfRangeException();
                }
            }

            set
            {
                switch (Index1)
                {
                    case 0:
                        XPlane[Index2] = value;
                        break;
                    case 1:
                        YPlane[Index2] = value;
                        break;
                    case 2:
                        ZPlane[Index2] = value;
                        break;
                    case 3:
                        WPlane[Index2] = value;
                        break;
                    default:
                        throw new IndexOutOfRangeException();
                }
            }
        }

        // Set this to the identity matrix
        public void SetIdentity()
        {
            this[0, 0] = 1; this[0, 1] = 0; this[0, 2] = 0; this[0, 3] = 0.0f;
            this[1, 0] = 0; this[1, 1] = 1; this[1, 2] = 0; this[1, 3] = 0.0f;
            this[2, 0] = 0; this[2, 1] = 0; this[2, 2] = 1; this[2, 3] = 0.0f;
            this[3, 0] = 0; this[3, 1] = 0; this[3, 2] = 0; this[3, 3] = 1.0f;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Matrix Multiply(ref Matrix This,ref Matrix Other);

        /**
         * Gets the result of multiplying a Matrix to this.
         *
         * @param Other The matrix to multiply this by.
         * @return The result of multiplication.
         */
        public static Matrix operator* (Matrix This,Matrix Other)
        {
            return Multiply(ref This,ref Other);
        }

        /**
         * Gets the result of adding a matrix to this.
         *
         * @param Other The Matrix to add.
         * @return The result of addition.
         */
        public static Matrix operator+ (Matrix This,Matrix Other)
        {
            Matrix ResultMat = new Matrix();

	        for(int X = 0;X < 4;X++)
	        {
		        for(int Y = 0;Y < 4;Y++)
		        {
			        ResultMat[X,Y] = This[X,Y]+Other[X,Y];
		        }
	        }

	        return ResultMat;
        }

        /** 
          * This isn't applying SCALE, just multiplying float to all members - i.e. weighting
          */
        public static Matrix operator* (Matrix This,float Other)
        {
            Matrix ResultMat = new Matrix();

	        for(int X = 0;X < 4;X++)
	        {
		        for(int Y = 0;Y < 4;Y++)
		        {
			        ResultMat[X,Y] = This[X,Y]*Other;
		        }
	        }

	        return ResultMat;
        }

        /**
         * Checks whether two matrix are identical.
         *
         * @param Other The other matrix.
         * @return true if two matrix are identical, otherwise false.
         */
        public static bool operator==(Matrix This,Matrix Other)
        {
            return This.Equals(Other);
        }

        /**
         * Checks whether another Matrix is equal to this, within specified tolerance.
         *
         * @param Other The other Matrix.
         * @param Tolerance Error Tolerance.
         * @return true if two Matrix are equal, within specified tolerance, otherwise false.
         */
        public override bool Equals(object Obj)
        {
            Matrix Other = (Matrix)Obj;
            float Tolerance=Const.KINDA_SMALL_NUMBER;
            for(int X = 0;X < 4;X++)
	        {
		        for(int Y = 0;Y < 4;Y++)
		        {
			        if(System.Math.Abs(this[X,Y] - Other[X,Y]) > Tolerance )
			        {
				        return false;
			        }
		        }
	        }

	        return true;
        }
        public override int GetHashCode()
        { return base.GetHashCode(); }
        /**
         * Checks whether another Matrix is not equal to this, within specified tolerance.
         *
         * @param Other The other Matrix.
         * @return true if two Matrix are not equal, within specified tolerance, otherwise false.
         */
        public static bool operator!=(Matrix This,Matrix Other)
        {
            return !This.Equals(Other);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Vector4D TransformFVector4(ref Matrix This,ref Vector4D V);
        // Homogeneous transform.
        public Vector4D TransformFVector4(Vector4D V)
        {
            return TransformFVector4(ref this,ref V);
        }

        /** Transform a location - will take into account translation part of the FMatrix. */
        public Vector4D TransformPosition(Vector V)
        {
            return TransformFVector4(new Vector4D(V.X,V.Y,V.Z,1.0f));
        }

        /** Inverts the matrix and then transforms V - correctly handles scaling in this matrix. */
        public Vector InverseTransformPosition(Vector V)
        {
            Matrix InvSelf = this.InverseFast();
	        return InvSelf.TransformPosition(V);
        }

        /** 
         *	Transform a direction vector - will not take into account translation part of the FMatrix. 
         *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT.
         */
        public Vector4D TransformVector(Vector V)
        {
            return TransformFVector4(new Vector4D(V.X,V.Y,V.Z,0.0f));
        }

        /** 
         *	Transform a direction vector by the inverse of this matrix - will not take into account translation part.
         *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT with adjoint of matrix inverse.
         */
         public Vector InverseTransformVector(Vector V)
         {
             Matrix InvSelf = this.InverseFast();
	         return InvSelf.TransformVector(V);
         }

        // Transpose.

        public Matrix GetTransposed()
        {
            Matrix	Result = new UnrealEngine.Matrix();

	        Result[0,0] = this[0,0];
	        Result[0,1] = this[1,0];
	        Result[0,2] = this[2,0];
	        Result[0,3] = this[3,0];

	        Result[1,0] = this[0,1];
	        Result[1,1] = this[1,1];
	        Result[1,2] = this[2,1];
	        Result[1,3] = this[3,1];

	        Result[2,0] = this[0,2];
	        Result[2,1] = this[1,2];
	        Result[2,2] = this[2,2];
	        Result[2,3] = this[3,2];

	        Result[3,0] = this[0,3];
	        Result[3,1] = this[1,3];
	        Result[3,2] = this[2,3];
	        Result[3,3] = this[3,3];

	        return Result;
        }

        // @return determinant of this matrix.

        public float Determinant()
        {
            	return	this[0,0] * (
				this[1,1] * (this[2,2] * this[3,3] - this[2,3] * this[3,2]) -
				this[2,1] * (this[1,2] * this[3,3] - this[1,3] * this[3,2]) +
				this[3,1] * (this[1,2] * this[2,3] - this[1,3] * this[2,2])
				) -
			this[1,0] * (
				this[0,1] * (this[2,2] * this[3,3] - this[2,3] * this[3,2]) -
				this[2,1] * (this[0,2] * this[3,3] - this[0,3] * this[3,2]) +
				this[3,1] * (this[0,2] * this[2,3] - this[0,3] * this[2,2])
				) +
			this[2,0] * (
				this[0,1] * (this[1,2] * this[3,3] - this[1,3] * this[3,2]) -
				this[1,1] * (this[0,2] * this[3,3] - this[0,3] * this[3,2]) +
				this[3,1] * (this[0,2] * this[1,3] - this[0,3] * this[1,2])
				) -
			this[3,0] * (
				this[0,1] * (this[1,2] * this[2,3] - this[1,3] * this[2,2]) -
				this[1,1] * (this[0,2] * this[2,3] - this[0,3] * this[2,2]) +
				this[2,1] * (this[0,2] * this[1,3] - this[0,3] * this[1,2])
				);
        }

        /** @return the determinant of rotation 3x3 matrix */
        public float RotDeterminant()
        {
            	return	
		this[0,0] * (this[1,1] * this[2,2] - this[1,2] * this[2,1]) -
		this[1,0] * (this[0,1] * this[2,2] - this[0,2] * this[2,1]) +
		this[2,0] * (this[0,1] * this[1,2] - this[0,2] * this[1,1]);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Matrix InverseFast(ref Matrix This);
        /** Fast path, doesn't check for nil matrices in final release builds */
        public Matrix InverseFast()
        {
            return InverseFast(ref this);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Matrix Inverse(ref Matrix This);
        /** Fast path, and handles nil matrices. */
        public Matrix Inverse()
        {
            return Inverse(ref this);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Matrix TransposeAdjoint(ref Matrix This);
        public Matrix TransposeAdjoint()
        {
            return TransposeAdjoint(ref this);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static void RemoveScaling(ref Matrix This, float Tolerance);
        // NOTE: There is some compiler optimization issues with WIN64 that cause FORCEINLINE to cause a crash
        // Remove any scaling from this matrix (ie magnitude of each row is 1) with error Tolerance
        public void RemoveScaling(float Tolerance=Const.SMALL_NUMBER)
        {
            RemoveScaling(ref this,Tolerance);
        }

        // Returns matrix after RemoveScaling with error Tolerance
        public Matrix GetMatrixWithoutScale(float Tolerance=Const.SMALL_NUMBER)
        {
            Matrix Result = this;
	        Result.RemoveScaling(Tolerance);
	        return Result;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Vector ExtractScaling(ref Matrix This,float Tolerance);
        /** Remove any scaling from this matrix (ie magnitude of each row is 1) and return the 3D scale vector that was initially present with error Tolerance */
        public Vector ExtractScaling(float Tolerance=Const.SMALL_NUMBER)
        {
            return ExtractScaling(ref this,Tolerance);
        }

        /** return a 3D scale vector calculated from this matrix (where each component is the magnitude of a row vector) with error Tolerance. */
        public Vector GetScaleVector(float Tolerance=Const.SMALL_NUMBER)
        {
            Vector Scale3D = new Vector(1,1,1);

	        // For each row, find magnitude, and if its non-zero re-scale so its unit length.
	        for(int i=0; i<3; i++)
	        {
		        float SquareSum = (this[i,0] * this[i,0]) + (this[i,1] * this[i,1]) + (this[i,2] * this[i,2]);
		        if(SquareSum > Tolerance)
		        {
			        Scale3D[i] = (float)System.Math.Sqrt(SquareSum);
		        }
		        else
		        {
			        Scale3D[i] = 0.0f;
		        }
	        }

	        return Scale3D;
        }

        // Remove any translation from this matrix
        public Matrix RemoveTranslation()
        {
            Matrix Result = this;
	        Result[3,0] = 0.0f;
	        Result[3,1] = 0.0f;
	        Result[3,2] = 0.0f;
	        return Result;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Matrix ConcatTranslation(ref Matrix This,ref Vector Translation);
        /** Returns a matrix with an additional translation concatenated. */
        public Matrix ConcatTranslation(Vector Translation)
        {
            return ConcatTranslation(ref this,ref Translation);
        }

        /** Scale the translation part of the matrix by the supplied vector. */
        public void ScaleTranslation(Vector InScale3D)
        {
            this[3,0] *= InScale3D.X;
	        this[3,1] *= InScale3D.Y;
	        this[3,2] *= InScale3D.Z;
        }

        /** @return the maximum magnitude of any row of the matrix. */
        public float GetMaximumAxisScale()
        {
            	float MaxRowScaleSquared = Math.Max(
		        GetScaledAxis( EAxis.X ).SizeSquared(),
		        Math.Max(
			        GetScaledAxis( EAxis.Y ).SizeSquared(),
			        GetScaledAxis( EAxis.Z ).SizeSquared()
			        )
		        );
	        return (float)System.Math.Sqrt(MaxRowScaleSquared);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static  Matrix ApplyScale(ref Matrix This,float Scale);
        /** Apply Scale to this matrix **/
        public Matrix ApplyScale(float Scale)
        {
            return ApplyScale(ref this,Scale);
        }

        // @return the origin of the co-ordinate system
        public Vector GetOrigin()
        {
            return new Vector(this[3,0],this[3,1],this[3,2]);
        }

        /**
         * get axis of this matrix scaled by the scale of the matrix
         *
         * @param i index into the axis of the matrix
         * @ return vector of the axis
         */
        public Vector GetScaledAxis(EAxis InAxis)
        {
            switch ( InAxis )
	        {
	        case EAxis.X:
		        return new Vector(this[0,0], this[0,1], this[0,2]);

	        case EAxis.Y:
		        return new Vector(this[1,0], this[1,1], this[1,2]);

	        case EAxis.Z:
		        return new Vector(this[2,0], this[2,1], this[2,2]);

	        default:
		        return Vector.ZeroVector;
	        }
        }

        /**
         * get axes of this matrix scaled by the scale of the matrix
         *
         * @param X axes returned to this param
         * @param Y axes returned to this param
         * @param Z axes returned to this param
         */
        public void GetScaledAxes(out Vector X,out  Vector Y,out  Vector Z)
        {
            X.X = this[0,0]; X.Y = this[0,1]; X.Z = this[0,2];
	        Y.X = this[1,0]; Y.Y = this[1,1]; Y.Z = this[1,2];
	        Z.X = this[2,0]; Z.Y = this[2,1]; Z.Z = this[2,2];
        }

        /**
         * get unit length axis of this matrix
         *
         * @param i index into the axis of the matrix
         * @return vector of the axis
         */
        public Vector GetUnitAxis(EAxis InAxis)
        {
            return GetScaledAxis( InAxis ).GetSafeNormal();
        }

        /**
         * get unit length axes of this matrix
         *
         * @param X axes returned to this param
         * @param Y axes returned to this param
         * @param Z axes returned to this param
         */
        public void GetUnitAxes(out Vector X,out  Vector Y,out  Vector Z)
        {
            GetScaledAxes(out X,out Y,out Z);
	        X.Normalize();
	        Y.Normalize();
	        Z.Normalize();
        }

        /**
         * set an axis of this matrix
         *
         * @param i index into the axis of the matrix
         * @param Axis vector of the axis
         */
        public void SetAxis( int i,Vector Axis )
        {
            this[i,0] = Axis.X;
	        this[i,1] = Axis.Y;
	        this[i,2] = Axis.Z;
        }

        // Set the origin of the coordinate system to the given vector
        public void SetOrigin(Vector NewOrigin )
        {
            this[3,0] = NewOrigin.X;
	        this[3,1] = NewOrigin.Y;
	        this[3,2] = NewOrigin.Z;
        }

        /**
         * get a column of this matrix
         *
         * @param i index into the column of the matrix
         * @return vector of the column 
         */
        public Vector GetColumn(int i)
        {
            return new Vector(this[0,i], this[1,i], this[2,i]);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static  Rotator Rotator(ref Matrix This);
        /** @return rotator representation of this matrix */
        public Rotator Rotator()
        {
            return Rotator(ref this);
        }

        /** 
         * Transform a rotation matrix into a quaternion.
         *
         * @warning rotation part will need to be unit length for this to be right!
         */
        public Quat ToQuat()
        {
            Quat Result = new Quat(this);
	        return Result;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static  bool GetFrustumNearPlane(ref Matrix This,out Plane OutPlane);
        // Frustum plane extraction.
        /** @param OutPlane the near plane of the Frustum of this matrix */
        public bool GetFrustumNearPlane(out Plane OutPlane)
        {
            return GetFrustumNearPlane(ref this,out OutPlane);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static  bool GetFrustumFarPlane(ref Matrix This,out Plane OutPlane);
        /** @param OutPlane the far plane of the Frustum of this matrix */
        public bool GetFrustumFarPlane(out Plane OutPlane)
        {
            return GetFrustumFarPlane(ref this,out OutPlane);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static  bool GetFrustumLeftPlane(ref Matrix This,out Plane OutPlane);
        /** @param OutPlane the left plane of the Frustum of this matrix */
        public bool GetFrustumLeftPlane(out Plane OutPlane)
        {
            return GetFrustumLeftPlane(ref this,out OutPlane);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static  bool GetFrustumRightPlane(ref Matrix This,out Plane OutPlane);
        /** @param OutPlane the right plane of the Frustum of this matrix */
        public bool GetFrustumRightPlane(out Plane OutPlane)
        {
            return GetFrustumRightPlane(ref this,out OutPlane);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static  bool GetFrustumTopPlane(ref Matrix This,out Plane OutPlane);
        /** @param OutPlane the top plane of the Frustum of this matrix */
        public bool GetFrustumTopPlane(out Plane OutPlane)
        {
            return GetFrustumTopPlane(ref this,out OutPlane);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static  bool GetFrustumBottomPlane(ref Matrix This,out Plane OutPlane);
        /** @param OutPlane the bottom plane of the Frustum of this matrix */
        public bool GetFrustumBottomPlane(out Plane OutPlane)
        {
            return GetFrustumBottomPlane(ref this,out OutPlane);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static void Mirror(ref Matrix This, int MirrorAxis, int FlipAxis);
        /**
         * Utility for mirroring this transform across a certain plane, and flipping one of the axis as well.
         */
        public void Mirror(EAxis MirrorAxis, EAxis FlipAxis)
        {
            Mirror(ref this, (int)MirrorAxis, (int)FlipAxis);
        }

        /**
         * Get a textual representation of the vector.
         *
         * @return Text describing the vector.
         */
        public override string ToString()
        {
            string Output = "";

	        Output += string.Format("[{0} {1} {2} {3}] ", this[0,0], this[0,1], this[0,2], this[0,3]);
            Output += string.Format("[{0} {1} {2} {3}] ", this[1,0], this[1,1], this[1,2], this[1,3]);
            Output += string.Format("[{0} {1} {2} {3}] ", this[2,0], this[2,1], this[2,2], this[2,3]);
            Output += string.Format("[{0} {1} {2} {3}] ", this[3,0], this[3,1], this[3,2], this[3,3]);

	        return Output;
        }
    }
}
