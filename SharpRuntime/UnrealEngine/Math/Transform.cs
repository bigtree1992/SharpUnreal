using System.Runtime.CompilerServices;
namespace UnrealEngine
{
    public partial struct Transform
    {
        public readonly static Transform Identity = new Transform(Vector.ZeroVector);
        void DiagnosticCheckNaN_All(){}
        void DiagnosticCheckNaN_Translate(){}
        void  DiagnosticCheckNaN_Rotate(){}
	    void DiagnosticCheckNaN_Scale3D(){}

        public Transform(Vector InTranslation)
        {
            Rotation = Quat.Identity;
            Translation = InTranslation;
            Scale3D = new Vector(1.0f);
        }

        public Transform(Quat InRotation)
        {
            Rotation = InRotation;
            Translation = Vector.ZeroVector;
            Scale3D = new Vector(1.0f);
        }

        public Transform(Rotator InRotation)
        {
            Rotation = new Quat(InRotation);
            Translation = Vector.ZeroVector;
            Scale3D = new Vector(1.0f);
        }

        public Transform(Quat InRotation, Vector InTranslation, Vector InScale3D)
        {
            Rotation = InRotation;
            Translation = InTranslation;
            Scale3D = InScale3D;
        }

        public Transform(Rotator InRotation, Vector InTranslation, Vector InScale3D)
        {
            Rotation = new Quat(InRotation);
            Translation = InTranslation;
            Scale3D = InScale3D;
        }


        public Transform(Matrix InMatrix)
	    {
            Rotation = Quat.Identity;
            Translation = Vector.ZeroVector;
            Scale3D = new Vector(1.0f);
		    SetFromMatrix(InMatrix);
	    }
        public Transform(Vector InX,Vector InY,Vector InZ,Vector InTranslation)
	    {
            Rotation = Quat.Identity;
            Translation = Vector.ZeroVector;
            Scale3D = new Vector(1.0f);
		    SetFromMatrix(new Matrix(InX, InY, InZ, InTranslation));
		    DiagnosticCheckNaN_All();
	    }
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Matrix ToMatrixWithScale(ref Transform This);

        /**
	    * Convert this Transform to a transformation matrix with scaling.
	    */
        public Matrix ToMatrixWithScale()
        {
            return ToMatrixWithScale(ref this);
        }

        /**
	    * Convert this Transform to matrix with scaling and compute the inverse of that.
	    */
	    public Matrix ToInverseMatrixWithScale()
	    {
		    // todo: optimize
		    return ToMatrixWithScale().Inverse();
	    }

        /**
	    * Convert this Transform to inverse.
	    */
	    public Transform Inverse()
	    {
		    Quat   InvRotation    = Rotation.Inverse();
		    Vector InvScale3D     = Scale3D.Reciprocal();
		    Vector InvTranslation = InvRotation * (InvScale3D * -Translation);

		    return new Transform(InvRotation, InvTranslation, InvScale3D);
	    }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Matrix ToMatrixNoScale(ref Transform This);
        /**
	    * Convert this Transform to a transformation matrix, ignoring its scaling
	    */
	    public Matrix ToMatrixNoScale()
        {
            return ToMatrixNoScale(ref this);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static void Blend(ref Transform This, ref  Transform Atom1, ref  Transform Atom2, float Alpha);
        /** Set this transform to the weighted blend of the supplied two transforms. */
	    public void Blend(Transform Atom1,Transform Atom2, float Alpha)
        {
            Blend(ref this, ref  Atom1, ref  Atom2, Alpha);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static void BlendWith(ref Transform This, ref Transform OtherAtom, float Alpha);
        /** Set this Transform to the weighted blend of it and the supplied Transform. */
	    public void BlendWith(Transform OtherAtom, float Alpha)
        {
            BlendWith(ref this, ref OtherAtom, Alpha);
        }

        /**
	     * Quaternion addition is wrong here. This is just a special case for linear interpolation.
	     * Use only within blends!!
	     * Rotation part is NOT normalized!!
	     */
	    public static Transform operator+(Transform This,Transform Atom)
	    {
		    return new Transform(This.Rotation + Atom.Rotation, This.Translation + Atom.Translation, This.Scale3D + Atom.Scale3D);
	    }

        public static Transform operator*(Transform This,float Mult)
	    {
		    return new Transform(This.Rotation * Mult, This.Translation * Mult, This.Scale3D * Mult);
	    }

        /**
	     * Return a transform that is the result of this multiplied by another transform.
	     * Order matters when composing transforms : C = A * B will yield a transform C that logically first applies A then B to any subsequent transformation.
	     * 
	     * @param  Other other transform by which to multiply.
	     * @return new transform: this * Other
	     */
        public static Transform operator *(Transform This, Transform Other)
        {
            Transform Output;
	        Multiply(out Output,ref This,ref Other);
	        return Output;
        }

        /**
	    * Return a transform that is the result of this multiplied by another transform (made only from a rotation).
	    * Order matters when composing transforms : C = A * B will yield a transform C that logically first applies A then B to any subsequent transformation.
	    *
	    * @param  Other other quaternion rotation by which to multiply.
	    * @return new transform: this * FTransform(Other)
	    */
	    public static  Transform operator*(Transform This,Quat Other)
        {
	        Transform Output;
            Transform OtherTransform = new Transform(Other, Vector.ZeroVector, new Vector(1.0f));
	        Multiply(out Output, ref This,ref OtherTransform);
	        return Output;
        }
        public void ScaleTranslation(Vector InScale3D)
        {
            Translation *= InScale3D;
	        DiagnosticCheckNaN_Translate();
        }

	    public void ScaleTranslation(float Scale)
        {
            Translation *= Scale;
	        DiagnosticCheckNaN_Translate();
        }

	    public void RemoveScaling(float Tolerance=Const.SMALL_NUMBER)
        {
            Scale3D = new Vector(1,1,1);
	        Rotation.Normalize();

	        DiagnosticCheckNaN_Rotate();
	        DiagnosticCheckNaN_Scale3D();
        }
	    public float GetMaximumAxisScale()
        {
            DiagnosticCheckNaN_Scale3D();
	        return Scale3D.GetAbsMax();
        }
	    public float GetMinimumAxisScale()
        {
            DiagnosticCheckNaN_Scale3D();
	        return Scale3D.GetAbsMin();
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Transform GetRelativeTransform(ref Transform This, ref Transform Other);
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Transform GetRelativeTransformReverse(ref Transform This, ref Transform Other);
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static void SetToRelativeTransform(ref Transform This, ref Transform ParentTransform);
        /*******************************************************************************************
	     * The below 2 functions are the ones to get delta transform and return FTransform format that can be concatenated
	     * Inverse itself can't concatenate with VQS format(since VQS always transform from S->Q->T, where inverse happens from T(-1)->Q(-1)->S(-1))
	     * So these 2 provides ways to fix this
	     * GetRelativeTransform returns this*Other(-1) and parameter is Other(not Other(-1))
	     * GetRelativeTransformReverse returns this(-1)*Other, and parameter is Other. 
	     *******************************************************************************************/
	    public Transform GetRelativeTransform(Transform Other)
        {
            return GetRelativeTransform(ref this,ref Other);
        }
	    public Transform GetRelativeTransformReverse(Transform Other)
        {
            return GetRelativeTransformReverse(ref this,ref Other);
        }

        /**
	     * Set current transform and the relative to ParentTransform.
	     * Equates to This = This->GetRelativeTransform(Parent), but saves the intermediate FTransform storage and copy.
	     */
	    public void		SetToRelativeTransform(Transform ParentTransform)
        {
            SetToRelativeTransform(ref this,ref ParentTransform);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Vector4D TransformFVector4(ref Transform This,ref Vector4D V);
	    public Vector4D	TransformFVector4(Vector4D V)
        {
            return TransformFVector4(ref this,ref V);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Vector4D TransformFVector4NoScale(ref Transform This,ref Vector4D V);
	    public Vector4D	TransformFVector4NoScale(Vector4D V)
        {
            return TransformFVector4NoScale(ref this,ref V);
        }
	    public Vector		TransformPosition(Vector V)
        {
            DiagnosticCheckNaN_All();
	        return Rotation.RotateVector(Scale3D*V) + Translation;
        }
	    public Vector		TransformPositionNoScale(Vector V)
        {
            DiagnosticCheckNaN_All();
	        return Rotation.RotateVector(V) + Translation;
        }


	    /** Inverts the matrix and then transforms V - correctly handles scaling in this matrix. */
	    public Vector		InverseTransformPosition(Vector V)
        {
            DiagnosticCheckNaN_All();
	        return ( Rotation.UnrotateVector(V-Translation) ) * GetSafeScaleReciprocal(Scale3D);
        }

	    public Vector		InverseTransformPositionNoScale(Vector V)
        {
            DiagnosticCheckNaN_All();
	        return ( Rotation.UnrotateVector(V-Translation) );
        }

	    public Vector		TransformVector(Vector V)
        {
            DiagnosticCheckNaN_All();
	        return Rotation.RotateVector(Scale3D*V);
        }

	    public Vector		TransformVectorNoScale(Vector V)
        {
            DiagnosticCheckNaN_All();
	        return Rotation.RotateVector(V);
        }

	    /** 
	     *	Transform a direction vector by the inverse of this matrix - will not take into account translation part.
	     *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT with adjoint of matrix inverse.
	     */
	    public Vector InverseTransformVector(Vector V)
        {
            DiagnosticCheckNaN_All();
	        return ( Rotation.UnrotateVector(V) ) * GetSafeScaleReciprocal(Scale3D);
        }

	    public Vector InverseTransformVectorNoScale(Vector V)
        {
            DiagnosticCheckNaN_All();
	        return ( Rotation.UnrotateVector(V) );
        }

	    public Transform	GetScaled(float InScale)
        {
            Transform A = this;
	        A.Scale3D *= InScale;

	        A.DiagnosticCheckNaN_Scale3D();

	        return A;
        }
	    public Transform	GetScaled(Vector InScale)
        {
            Transform A = (this);
	        A.Scale3D *= InScale;

	        A.DiagnosticCheckNaN_Scale3D();

	        return A;
        }
	    public Vector		GetScaledAxis(EAxis InAxis)
        {
            if ( InAxis == EAxis.X )
	        {
		        return TransformVector(new Vector(1.0f, 0.0f, 0.0f));
	        }
	        else if ( InAxis == EAxis.Y )
	        {
		        return TransformVector(new Vector(0.0f, 1.0f, 0.0f));
	        }

	        return TransformVector(new Vector(0.0f, 0.0f, 1.0f));
        }
	    public Vector	GetUnitAxis(EAxis InAxis)
        {
            if ( InAxis == EAxis.X )
	        {
		        return TransformVectorNoScale(new Vector(1.0f, 0.0f, 0.0f));
	        }
	        else if ( InAxis == EAxis.Y )
	        {
		        return TransformVectorNoScale(new Vector(0.0f, 1.0f, 0.0f));
	        }

	        return TransformVectorNoScale(new Vector(0.0f, 0.0f, 1.0f));
        }
	    public void		Mirror(EAxis MirrorAxis, EAxis FlipAxis)
        {
            // We do convert to Matrix for mirroring. 
	        Matrix M = ToMatrixWithScale();
	        M.Mirror(MirrorAxis, FlipAxis);
	        SetFromMatrix(M);
        }

        static public Vector		GetSafeScaleReciprocal(Vector InScale)
        {
            Vector SafeReciprocalScale;
            // mathematically if you have 0 scale, it should be infinite, 
            // however, in practice if you have 0 scale, and relative transform doesn't make much sense 
            // anymore because you should be instead of showing gigantic infinite mesh
            // also returning BIG_NUMBER causes sequential NaN issues by multiplying 
            // so we hardcode as 0
            if (InScale.X == 0)
            {
                SafeReciprocalScale.X = 0.0f;
            }
            else
            {
                SafeReciprocalScale.X = 1 / InScale.X;
            }

            if (InScale.Y == 0)
            {
                SafeReciprocalScale.Y = 0.0f;
            }
            else
            {
                SafeReciprocalScale.Y = 1 / InScale.Y;
            }

            if (InScale.Z == 0)
            {
                SafeReciprocalScale.Z = 0.0f;
            }
            else
            {
                SafeReciprocalScale.Z = 1 / InScale.Z;
            }

            return SafeReciprocalScale;
        }

        // temp function for easy conversion
	    public Vector GetLocation()
	    {
		    return Translation;
	    }

	    public  Rotator Rotator()
	    {
		    return Rotation.Rotator();
	    }

	    /** Calculate the  */
	    public  float GetDeterminant()
	    {
		    return Scale3D.X * Scale3D.Y * Scale3D.Z;
	    }

	    /** Set the translation of this transformation */
	    public  void SetLocation(Vector Origin)
	    {
		    Translation = Origin;
		    DiagnosticCheckNaN_Translate();
	    }

        /**
	        * Create a new transform: OutTransform = A * B.
	        *
	        * Order matters when composing transforms : A * B will yield a transform that logically first applies A then B to any subsequent transformation.
	        * 
	        * @param  OutTransform pointer to transform that will store the result of A * B.
	        * @param  A Transform A.
	        * @param  B Transform B.
	        */
        [MethodImpl(MethodImplOptions.InternalCall)]
	    public extern static void Multiply(out Transform OutTransform, ref  Transform A, ref  Transform B);

            /**
	     * Sets the components
	     * @param InRotation The new value for the Rotation component
	     * @param InTranslation The new value for the Translation component
	     * @param InScale3D The new value for the Scale3D component
	     */
	    public void SetComponents(Quat InRotation,Vector InTranslation,Vector InScale3D) 
	    {
		    Rotation = InRotation;
		    Translation = InTranslation;
		    Scale3D = InScale3D;

		    DiagnosticCheckNaN_All();
	    }

	    /**
	     * Sets the components to the identity transform:
	     *   Rotation = (0,0,0,1)
	     *   Translation = (0,0,0)
	     *   Scale3D = (1,1,1)
	     */
	    public void SetIdentity()
	    {
		    Rotation = Quat.Identity;
		    Translation	= Vector.ZeroVector;
		    Scale3D = new Vector(1,1,1);
	    }

	    /**
	     * Scales the Scale3D component by a new factor
	     * @param Scale3DMultiplier The value to multiply Scale3D with
	     */
	    public void MultiplyScale3D(Vector Scale3DMultiplier)
	    {
		    Scale3D *= Scale3DMultiplier;
		    DiagnosticCheckNaN_Scale3D();
	    }

	    /**
	     * Sets the translation component
	     * @param NewTranslation The new value for the translation component
	     */
	    public void SetTranslation(Vector NewTranslation)
	    {
		    Translation = NewTranslation;
		    DiagnosticCheckNaN_Translate();
	    }

	    /** Copy translation from another FTransform. */
	    public void CopyTranslation(Transform Other)
	    {
		    Translation = Other.Translation;
	    }

	    /**
	     * Concatenates another rotation to this transformation 
	     * @param DeltaRotation The rotation to concatenate in the following fashion: Rotation = Rotation * DeltaRotation
	     */
	    public void ConcatenateRotation(Quat DeltaRotation)
	    {
		    Rotation = Rotation * DeltaRotation;
		    DiagnosticCheckNaN_Rotate();
	    }

	    /**
	     * Adjusts the translation component of this transformation 
	     * @param DeltaTranslation The translation to add in the following fashion: Translation += DeltaTranslation
	     */
	    public void AddToTranslation(Vector DeltaTranslation)
	    {
		    Translation += DeltaTranslation;
		    DiagnosticCheckNaN_Translate();
	    }

	    /**
	     * Add the translations from two FTransforms and return the result.
	     * @return A.Translation + B.Translation
	     */
	    public static Vector AddTranslations(Transform A, Transform B)
	    {
		    return A.Translation + B.Translation;
	    }

	    /**
	     * Subtract translations from two FTransforms and return the difference.
	     * @return A.Translation - B.Translation.
	     */
	    public static Vector SubtractTranslations(Transform A,Transform B)
	    {
		    return A.Translation - B.Translation;
	    }

	    /**
	     * Sets the rotation component
	     * @param NewRotation The new value for the rotation component
	     */
	    public void SetRotation(Quat NewRotation)
	    {
		    Rotation = NewRotation;
		    DiagnosticCheckNaN_Rotate();
	    }

	    /** Copy rotation from another FTransform. */
	    public void CopyRotation(Transform Other)
	    {
		    Rotation = Other.Rotation;
	    }

	    /**
	     * Sets the Scale3D component
	     * @param NewScale3D The new value for the Scale3D component
	     */
	    public void SetScale3D(Vector NewScale3D)
	    {
		    Scale3D = NewScale3D;
		    DiagnosticCheckNaN_Scale3D();
	    }

	    /** Copy scale from another FTransform. */
	    public void CopyScale3D( Transform Other)
	    {
		    Scale3D = Other.Scale3D;
	    }

	    /**
	     * Sets both the translation and Scale3D components at the same time
	     * @param NewTranslation The new value for the translation component
	     * @param NewScale3D The new value for the Scale3D component
	     */
	    public void SetTranslationAndScale3D(Vector NewTranslation, Vector NewScale3D)
	    {
		    Translation = NewTranslation;
		    Scale3D = NewScale3D;

		    DiagnosticCheckNaN_Translate();
		    DiagnosticCheckNaN_Scale3D();
	    }

	    /**
	     * Accumulates another transform with this one, with an optional blending weight
	     *
	     * Rotation is accumulated additively, in the shortest direction (Rotation = Rotation +/- DeltaAtom.Rotation * Weight)
	     * Translation is accumulated additively (Translation += DeltaAtom.Translation * Weight)
	     * Scale3D is accumulated additively (Scale3D += DeltaAtom.Scale3D * Weight)
	     *
	     * @param DeltaAtom The other transform to accumulate into this one
	     * @param Weight The weight to multiply DeltaAtom by before it is accumulated.
	     */
	    public void AccumulateWithShortestRotation(Transform DeltaAtom, float Weight = 1.0f)
	    {
		    Transform Atom = DeltaAtom * Weight;

		    // To ensure the 'shortest route', we make sure the dot product between the accumulator and the incoming child atom is positive.
		    if( (Atom.Rotation | Rotation) < 0.0f )
		    {
			    Rotation.X -= Atom.Rotation.X;
			    Rotation.Y -= Atom.Rotation.Y;
			    Rotation.Z -= Atom.Rotation.Z;
			    Rotation.W -= Atom.Rotation.W;
		    }
		    else
		    {
			    Rotation.X += Atom.Rotation.X;
			    Rotation.Y += Atom.Rotation.Y;
			    Rotation.Z += Atom.Rotation.Z;
			    Rotation.W += Atom.Rotation.W;
		    }

		    Translation += Atom.Translation;
		    Scale3D += Atom.Scale3D;

		    DiagnosticCheckNaN_All();
	    }

	    /**
	     * Accumulates another transform with this one
	     *
	     * Rotation is accumulated multiplicatively (Rotation = SourceAtom.Rotation * Rotation)
	     * Translation is accumulated additively (Translation += SourceAtom.Translation)
	     * Scale3D is accumulated multiplicatively (Scale3D *= SourceAtom.Scale3D)
	     *
	     * @param SourceAtom The other transform to accumulate into this one
	     */
	    public void Accumulate(Transform SourceAtom)
	    {
		    // Add ref pose relative animation to base animation, only if rotation is significant.
		    if(SourceAtom.Rotation.W*SourceAtom.Rotation.W < 1.0f - Const.DELTA * Const.DELTA )
		    {
			    Rotation = SourceAtom.Rotation * Rotation;
		    }

		    Translation += SourceAtom.Translation;
		    Scale3D *= SourceAtom.Scale3D;

		    DiagnosticCheckNaN_All();

		    //checkSlow( IsRotationNormalized() );
	    }

       /** Accumulates another transform with this one, with a blending weight
	    *
	    * Let SourceAtom = Atom * BlendWeight
	    * Rotation is accumulated multiplicatively (Rotation = SourceAtom.Rotation * Rotation).
	    * Translation is accumulated additively (Translation += SourceAtom.Translation)
	    * Scale3D is accumulated multiplicatively (Scale3D *= SourceAtom.Scale3D)
	    *
	    * Note: Rotation will not be normalized! Will have to be done manually.
	    *
	    * @param Atom The other transform to accumulate into this one
	    * @param BlendWeight The weight to multiply Atom by before it is accumulated.
	    */
	    public void Accumulate(Transform Atom, float BlendWeight)
	    {
		    Transform SourceAtom = Atom * BlendWeight;

		    // Add ref pose relative animation to base animation, only if rotation is significant.
		    if(SourceAtom.Rotation.W*SourceAtom.Rotation.W < 1.0f - Const.DELTA * Const.DELTA )
		    {
			    Rotation = SourceAtom.Rotation * Rotation;
		    }

		    Translation += SourceAtom.Translation;
		    Scale3D *= SourceAtom.Scale3D;

		    DiagnosticCheckNaN_All();
	    }

	    /**
	     * Set the translation and Scale3D components of this transform to a linearly interpolated combination of two other transforms
	     *
	     * Translation = FMath::Lerp(SourceAtom1.Translation, SourceAtom2.Translation, Alpha)
	     * Scale3D = FMath::Lerp(SourceAtom1.Scale3D, SourceAtom2.Scale3D, Alpha)
	     *
	     * @param SourceAtom1 The starting point source atom (used 100% if Alpha is 0)
	     * @param SourceAtom2 The ending point source atom (used 100% if Alpha is 1)
	     * @param Alpha The blending weight between SourceAtom1 and SourceAtom2
	     */
	    public void LerpTranslationScale3D(Transform SourceAtom1, Transform SourceAtom2, float Alpha)
	    {
		    Translation	= Math.Lerp(SourceAtom1.Translation, SourceAtom2.Translation, Alpha);
            Scale3D = Math.Lerp(SourceAtom1.Scale3D, SourceAtom2.Scale3D, Alpha);

		    DiagnosticCheckNaN_Translate();
		    DiagnosticCheckNaN_Scale3D();
	    }

	    /**
	     * Accumulates another transform with this one
	     *
	     * Rotation is accumulated multiplicatively (Rotation = SourceAtom.Rotation * Rotation)
	     * Translation is accumulated additively (Translation += SourceAtom.Translation)
	     * Scale3D is accumulated additively (Scale3D += SourceAtom.Scale3D)
	     *
	     * @param SourceAtom The other transform to accumulate into this one
	     */
	    public void AccumulateWithAdditiveScale3D(Transform SourceAtom)
	    {
		    if(SourceAtom.Rotation.W* SourceAtom.Rotation.W < 1.0f - Const.DELTA * Const.DELTA )
		    {
			    Rotation = SourceAtom.Rotation * Rotation;
		    }

		    Translation += SourceAtom.Translation;
		    Scale3D += SourceAtom.Scale3D;

		    DiagnosticCheckNaN_All();
	    }

	    /**
	     * Normalize the rotation component of this transformation
	     */
	    public void NormalizeRotation()
	    {
		    Rotation.Normalize();
		    DiagnosticCheckNaN_Rotate();
	    }

	    /**
	     * Checks whether the rotation component is normalized or not
	     *
	     * @return true if the rotation component is normalized, and false otherwise.
	     */
	    public bool IsRotationNormalized() 
	    {
		    return Rotation.IsNormalized();
	    }

	    /**
	     * Returns the rotation component
	     *
	     * @return The rotation component
	     */
	    public Quat GetRotation()
	    {
		    DiagnosticCheckNaN_Rotate();
		    return Rotation;
	    }

	    /**
	     * Returns the translation component
	     *
	     * @return The translation component
	     */
	    public Vector GetTranslation()
	    {
		    DiagnosticCheckNaN_Translate();
		    return Translation;
	    }

	    /**
	     * Returns the Scale3D component
	     *
	     * @return The Scale3D component
	     */
	    public Vector GetScale3D()
	    {
		    DiagnosticCheckNaN_Scale3D();
		    return Scale3D;
	    }

	    /**
	     * Sets the Rotation and Scale3D of this transformation from another transform
	     *
	     * @param SrcBA The transform to copy rotation and Scale3D from
	     */
	    public void CopyRotationPart(Transform SrcBA)
	    {
		    Rotation = SrcBA.Rotation;
		    Scale3D = SrcBA.Scale3D;

		    DiagnosticCheckNaN_Rotate();
		    DiagnosticCheckNaN_Scale3D();
	    }

	    /**
	     * Sets the Translation and Scale3D of this transformation from another transform
	     *
	     * @param SrcBA The transform to copy translation and Scale3D from
	     */
	    public void CopyTranslationAndScale3D(Transform SrcBA)
	    {
		    Translation = SrcBA.Translation;
		    Scale3D = SrcBA.Scale3D;

		    DiagnosticCheckNaN_Translate();
		    DiagnosticCheckNaN_Scale3D();
	    }

	    public void SetFromMatrix(Matrix InMatrix)
	    {
		    Matrix M = InMatrix;

		    // Get the 3D scale from the matrix
		    Scale3D = M.ExtractScaling();

		    // If there is negative scaling going on, we handle that here
		    if(InMatrix.Determinant() < 0.0f)
		    {
			    // Assume it is along X and modify transform accordingly. 
			    // It doesn't actually matter which axis we choose, the 'appearance' will be the same
			    Scale3D.X *= -1.0f;
			    M.SetAxis(0, -M.GetScaledAxis( EAxis.X ));
		    }

		    Rotation = new Quat(M);
		    Translation = InMatrix.GetOrigin();

		    // Normalize rotation
		    Rotation.Normalize();
	    }
    }
}
