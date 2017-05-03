using System;
using System.IO;

namespace UnrealEngine
{
    public class FLog
    {
        static FileStream ostrm;
        static StreamWriter writer;

        public static void SetLogToFile()
        {
            try
            {
                string filename = "QLog-" + DateTime.Now.ToString("yyyy-MM-dd") + ".txt";

                string path = Path.GetFullPath(".\\Log\\");
                if (!Directory.Exists(path))
                {
                    Directory.CreateDirectory(path);
                }

                ostrm = new FileStream(".\\Log\\" + filename, FileMode.Append, FileAccess.Write);
                writer = new StreamWriter(ostrm);
                writer.AutoFlush = true;
            }
            catch (Exception e)
            {
                Console.WriteLine("[Log] Cannot open QLog.txt for writing.");
                Console.WriteLine(e.Message);
                return;
            }
            Console.SetOut(writer);
        }

        public static void WriteLog(string level, string content)
        {
            Console.WriteLine("[{0}] {1} {2}", level, DateTime.Now.ToString("hh.mm.ss"), content);
        }

        public static void Warning(string content)
        {
            WriteLog("Warning", content);
        }

        public static void Debug(string content)
        {
            WriteLog("Debug", content);
        }

        public static void Error(string content)
        {
            WriteLog("Error", content);
        }
    }
}
