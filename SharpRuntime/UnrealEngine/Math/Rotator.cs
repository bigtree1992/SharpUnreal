using System.Runtime.CompilerServices;
namespace UnrealEngine
{
    public partial struct Rotator
    {
	    /**
	     * Constructor
	     *
	     * @param InF Value to set all components to.
	     */
	    public Rotator(float InF)
        {
            this.Pitch = this.Roll = this.Yaw = InF;
        }

	    /**
	     * Constructor.
	     *
	     * @param InPitch Pitch in degrees.
	     * @param InYaw Yaw in degrees.
	     * @param InRoll Roll in degrees.
	     */
        public Rotator(float InPitch, float InYaw, float InRoll)
        {
            this.Pitch = InPitch;
            this.Yaw = InYaw;
            this.Roll = InRoll;
        }

        public Rotator(Rotator Other)
        {
            this.Pitch =Other.Pitch;
            this.Yaw = Other.Yaw;
            this.Roll = Other.Roll;
        }

        /**
	     * Get the result of adding a rotator to this.
	     *
	     * @param R The other rotator.
	     * @return The result of adding a rotator to this.
	     */
        public static Rotator operator +(Rotator A,Rotator R)
        {
            return new Rotator(A.Pitch + R.Pitch, A.Yaw + R.Yaw, A.Roll + R.Roll);
        }

	    /**
	     * Get the result of subtracting a rotator from this.
	     *
	     * @param R The other rotator.
	     * @return The result of subtracting a rotator from this.
	     */
        public static Rotator operator -(Rotator A, Rotator R)
        {
            return new Rotator(A.Pitch - R.Pitch, A.Yaw - R.Yaw, A.Roll - R.Roll);
        }

	    /**
	     * Get the result of scaling this rotator.
	     *
	     * @param Scale The scaling factor.
	     * @return The result of scaling.
	     */
	    public static Rotator operator*(Rotator A, float Scale )
        {
            return new Rotator( A.Pitch*Scale, A.Yaw*Scale, A.Roll*Scale );
        }

        /**
	     * Checks whether two rotators are identical. This checks each component for exact equality.
	     *
	     * @param R The other rotator.
	     * @return true if two rotators are identical, otherwise false.
	     * @see Equals()
	     */
	    public static bool operator==(Rotator A, Rotator R )
        {
            return A.Equals(R);
        }

	    /**
	     * Checks whether two rotators are different.
	     *
	     * @param V The other rotator.
	     * @return true if two rotators are different, otherwise false.
	     */
	    public static bool operator!=(Rotator A,Rotator V )
        {
            return !A.Equals(V);
        }

        bool Equals(Rotator R, float Tolerance=Const.KINDA_SMALL_NUMBER )
        {
            	return (System.Math.Abs(NormalizeAxis(Pitch - R.Pitch)) <= Tolerance) 
		    && (System.Math.Abs(NormalizeAxis(Yaw - R.Yaw)) <= Tolerance) 
		    && (System.Math.Abs(NormalizeAxis(Roll - R.Roll)) <= Tolerance);
        }

        public override bool Equals(object obj)
        {
            return Equals((Rotator)obj);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        /**
	    * Adds to each component of the rotator.
	    *
	    * @param DeltaPitch Change in pitch. (+/-)
	    * @param DeltaYaw Change in yaw. (+/-)
	    * @param DeltaRoll Change in roll. (+/-)
	    * @return Copy of rotator after addition.
	    */
	    public Rotator Add( float DeltaPitch, float DeltaYaw, float DeltaRoll )
        {
            Yaw   += DeltaYaw;
	        Pitch += DeltaPitch;
	        Roll  += DeltaRoll;
	        //DiagnosticCheckNaN();
	        return this;
        }

	    /**
	    * Returns the inverse of the rotator.
	    */
	    public Rotator GetInverse()
        {
            return Quaternion().Inverse().Rotator();
        }

        public bool IsNearlyZero(float Tolerance)
        {
            return Math.Abs(NormalizeAxis(Pitch)) <= Tolerance && 
                   Math.Abs(NormalizeAxis(Yaw)) <= Tolerance && 
                   Math.Abs(NormalizeAxis(Roll)) <= Tolerance;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Vector Vector(ref Rotator _this);

        /**
	     * Convert a rotation into a unit vector facing in its direction.
	     *
	     * @return Rotation as a unit direction vector.
	     */
	    public Vector Vector()
        {
            return Vector(ref this);
        }
        
	    /**
	     * Get Rotation as a quaternion.
	     *
	     * @return Rotation as a quaternion.
	     */

        public Quat Quaternion()
        {
            const float DEG_TO_RAD = Const.PI / (180.0f);
            const float DIVIDE_BY_2 = DEG_TO_RAD / 2.0f;
            float SP, SY, SR;
            float CP, CY, CR;

            Math.SinCos(out SP, out CP, Pitch * DIVIDE_BY_2);
            Math.SinCos(out SY, out CY, Yaw * DIVIDE_BY_2);
            Math.SinCos(out SR, out CR, Roll * DIVIDE_BY_2);

            Quat RotationQuat;
            RotationQuat.X = CR * SP * SY - SR * CP * CY;
            RotationQuat.Y = -CR * SP * CY - SR * CP * SY;
            RotationQuat.Z = CR * CP * SY - SR * SP * CY;
            RotationQuat.W = CR * CP * CY + SR * SP * SY;
            return RotationQuat;
        }

        /**
	     * Convert a Rotator into floating-point Euler angles (in degrees). Rotator now stored in degrees.
	     *
	     * @return Rotation as a Euler angle vector.
	     */
        public Vector Euler()
        {
            return new Vector( Roll, Pitch, Yaw );
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Vector RotateVector(ref Rotator _this,Vector V);
	    /**
	     * Rotate a vector rotated by this rotator.
	     *
	     * @param V The vector to rotate.
	     * @return The rotated vector.
	     */
	    public Vector RotateVector(Vector V )
        {
            return RotateVector(ref this,V);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static Vector UnrotateVector(ref Rotator _this,Vector V);
	    /**
	     * Returns the vector rotated by the inverse of this rotator.
	     *
	     * @param V The vector to rotate.
	     * @return The rotated vector.
	     */
	    public Vector UnrotateVector( Vector V )
        {
            return UnrotateVector(ref this,V);
        }

	    /**
	     * Gets the rotation values so they fall within the range [0,360]
	     *
	     * @return Clamped version of rotator.
	     */
	    public Rotator Clamp()
        {
            return new Rotator(ClampAxis(Pitch), ClampAxis(Yaw), ClampAxis(Roll));
        }


        /** 
	     * Create a copy of this rotator and normalize, removes all winding and creates the "shortest route" rotation. 
	     *
	     * @return Normalized copy of this rotator
	     */
	    public Rotator GetNormalized()
        {
            Rotator Rot = this;
	        Rot.Normalize();
	        return Rot;
        }

	    /** 
	     * Create a copy of this rotator and denormalize, clamping each axis to 0 - 360. 
	     *
	     * @return Denormalized copy of this rotator
	     */
	    public Rotator GetDenormalized()
        {
            Rotator Rot = this;
	        Rot.Pitch	= ClampAxis(Rot.Pitch);
	        Rot.Yaw		= ClampAxis(Rot.Yaw);
	        Rot.Roll	= ClampAxis(Rot.Roll);
	        return Rot;
        }

	    /**
	     * In-place normalize, removes all winding and creates the "shortest route" rotation.
	     */
	    public void Normalize()
        {
            Pitch = NormalizeAxis(Pitch);
	        Yaw = NormalizeAxis(Yaw);
	        Roll = NormalizeAxis(Roll);
        }

        /**
	     * Clamps an angle to the range of [0, 360).
	     *
	     * @param Angle The angle to clamp.
	     * @return The clamped angle.
	     */
	    public static float ClampAxis( float Angle )
        {
            //Angle = FMath::Fmod(Angle, 360.f);
            Angle = Angle% 360.0f;

	        if (Angle < 0.0f)
	        {
		        // shift to [0,360) range
		        Angle += 360.0f;
	        }

	        return Angle;
        }

	    /**
	     * Clamps an angle to the range of (-180, 180].
	     *
	     * @param Angle The Angle to clamp.
	     * @return The clamped angle.
	     */
	    public static float NormalizeAxis( float Angle )
        {
            // returns Angle in the range [0,360)
	        Angle = ClampAxis(Angle);

	        if (Angle > 180.0f)
	        {
		        // shift to (-180,180]
		        Angle -= 360.0f;
	        }

	        return Angle;
        }

	    /**
	     * Convert a vector of floating-point Euler angles (in degrees) into a Rotator. Rotator now stored in degrees
	     *
	     * @param Euler Euler angle vector.
	     * @return A rotator from a Euler angle.
	     */
	    public static Rotator MakeFromEuler( Vector Euler )
        {
            return new Rotator(Euler.Y, Euler.Z, Euler.X);
        }

        public static readonly Rotator ZeroRotator = new Rotator();
    }
}
