using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class NetWorkBehavior: MonoComponent
    {
        #region CallBack

        public virtual void OnStartOnlieGameComplete(bool bSuccess)
        {
        }
        public virtual void OnFindOnlieGameComplete(bool bSuccess)
        {
        }
        public virtual void OnJoinOnlieGameComplete(bool bSuccess)
        {
        }
        public virtual void OnDestroyOnlieGameComplete(bool bSuccess)
        {
        }
        #endregion

        public void StartOnlineGame(string mapName, int playerNum)
        {
            _StartOnlineGame(NativeHandler,mapName, playerNum);
        }

        public void FindOnlineGame()
        {
            _FindOnlineGame(NativeHandler);
        }

        public void JoinOnlineGame()
        {
            _JoinOnlineGame(NativeHandler);
        }

        public void DestroySessionAndLeaveGame()
        {
            _DestroySessionAndLeaveGame(NativeHandler);
        }

        public int GetOnlineGamePlayerNum()
        {
            return _GetOnlineGamePlayerNum(NativeHandler);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _StartOnlineGame(IntPtr handler, string mapName, int playerNum);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _FindOnlineGame(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _JoinOnlineGame(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _DestroySessionAndLeaveGame(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static int _GetOnlineGamePlayerNum(IntPtr handler);
    }
}
