using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnrealEngine
{
    public class ActorComponent : UObject
    {
        public bool Activited { get; set; }

        public bool CanEverTick { get; set; }

        protected virtual void Initialize()
        {
        }

	    protected virtual void Uninitialize()
        {
        }

        protected virtual void Tick(float dt)
        {
        }

        protected virtual void OnRegister()
        {
        }

        protected virtual void OnUnregister()
        {
        }

        public Actor GetOwner()
        {
            return null;
        }

        public bool ComponentHasTag(string tag)
        {
            return false;
        }

        public void SetTickableWhenPaused(bool bTickableWhenPaused)
        {
        }
    }
}
