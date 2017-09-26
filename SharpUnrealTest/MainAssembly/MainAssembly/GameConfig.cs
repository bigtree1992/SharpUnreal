using System;
using System.Xml.Serialization;
using System.IO;

namespace MainAssembly
{
    public class GameConfig
    {

        public static GameConfig singleton = null;
        public int StartAsServer;

        /// <summary>
        /// 根据配置文件初始化当前配置类
        /// </summary>
        public static void InitConfig(string path)
        {
            GameConfig.Deserialize(path);
        }

        /// <summary>
        /// config类
        /// </summary>
        /// <param name="path">Path.</param>
        public static GameConfig Deserialize(string path)
        {
            if (singleton == null)
            {
                var stream = File.Open(path, FileMode.Open);
                var xs = new XmlSerializer(typeof(GameConfig));
                singleton = xs.Deserialize(stream) as GameConfig;
                stream.Close();
            }
            return singleton;
        }
    }
}
