using System;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

namespace CodeGen
{
    internal class Param
    {
        internal string Type;
        internal string Name;
    }

    internal class Function
    {
        internal string Name;
        internal string RetType;
        internal List<Param> Params = new List<Param>();
    }

    internal class Property
    {
        internal string Name;
        internal string Type;
        internal bool HasGet = true;
        internal bool HasSet = false;
    }

    /// <summary>
    /// 根据手动编写的C#函数声明跟属性声明，
    /// 生成C#InternalCall声明与CPP绑定InternalCall的代码
    /// </summary>
    public class CodeGender
    {
        private string m_NameSpace;
        private string m_ClassName;
        private string m_BaseClass;

        private List<Property> m_Propertys = new List<Property>();
        private List<Function> m_Functions = new List<Function>();

        private Dictionary<string, string> m_ToCppType = new Dictionary<string, string>
        {
            { "void","void"},
            { "int","int"},
            { "float","float"},
            { "double","double"},
            { "bool","mono_bool" },
            { "string" ,"MonoString*" },
            { "Vector" ,"FVector" },
            { "Vector2D" ,"FVector2D" },
            { "Vector4D" ,"FVector4D" },
            { "Quat" ,"FQuat" },
            { "Rotator" ,"FRotator" },
            { "Transform" ,"FTransform" },
            { "Plane" ,"FPlane" },
            { "LinearColor" ,"FLinearColor" },
            { "Color" ,"FColor" },
            { "Axis" ,"FAxis" },
            { "Actor","AActor*"}

        };

        private Dictionary<string, string> m_DefaultValue = new Dictionary<string, string>
        {
            { "void",""},
            { "int","0"},
            { "float","0.0f"},
            { "double","0.0"},
            { "bool","0" },
            { "string" ,"NULL" },
            { "Vector" ,"FVector::ZeroVector" },
            { "Vector2D" ,"FVector2D::ZeroVector" },
            { "Vector4D" ,"FVector4D::ZeroVector" },
            { "Quat" ,"FQuat::Identity" },
            { "Rotator" ,"FRotator::ZeroRotator" },
            { "Transform" ,"FTransform::Identity" },
            { "LinearColor" ,"FLinearColor::Black" },
            { "Color" ,"FColor::Black" },
            { "Axis" ,"FAxis::DefaultAxis" },
            { "Actor","NULL"}
        };


        public void Process(string filename)
        {
            var file = File.OpenText(filename);

            while (!file.EndOfStream)
            {
                string line = file.ReadLine();
                line = line.Trim();
                if (line.Contains("enum"))
                {
                    continue;
                }
                else if (line.Contains("namespace"))
                {
                    m_NameSpace = line.Replace("namespace", "");
                    m_NameSpace = m_NameSpace.Trim();
                }
                else if (line.StartsWith("public"))
                {
                    if (line.Contains("class"))
                    {
                        if (line.Contains(":"))
                        {
                            var ls = line.Split(':');
                            if(ls.Length > 1)
                            {
                                m_BaseClass = ls[1];                               
                            }
                            line = ls[0];

                        }
                        m_ClassName = line.Replace("public", "");
                        m_ClassName = m_ClassName.Replace("class", "");
                        m_ClassName = m_ClassName.Trim();
                    }
                    else if (line.Contains("("))
                    {
                        ProcessFunction(file, line);
                    }
                    else
                    {
                        ProcessProperty(file, line);
                    }
                }
                else
                {
                    //skip
                }

            }
        }

        public void ProcessFunction(StreamReader file, string line)
        {            
            try
            {
                var reg = new Regex(@"public (.*) (.*)(\(.*?\))");
                var result = reg.Match(line);

                var func = new Function();
                func.Name = result.Groups[2].Value;
                func.RetType = result.Groups[1].Value;

                string ps = result.Groups[3].Value;
                ps = ps.Replace('(', ' ');
                ps = ps.Replace(')', ' ');

                string[] ss = ps.Split(',');

                for(int i = 0; i < ss.Length; i++)
                {
                    string pl = ss[i];

                    int index = pl.IndexOf('=');
                    if (index > 0)
                    {
                        pl = pl.Remove(index);
                    }
                    pl = pl.Trim();

                    string[] pls = pl.Split(' ');
                    if (pls.Length == 2)
                    {
                        var pa = new Param();
                        pa.Name = pls[1];
                        pa.Type = pls[0];
                        func.Params.Add(pa);
                    }
                    else
                    {
                        Console.WriteLine("[Error] : " + pl);
                        continue;
                    }
                }

                m_Functions.Add(func);
            }
            catch(Exception e)
            {
                Console.WriteLine("[ProcessFunction] Error:" + e);
            }
        }

        public void ProcessProperty(StreamReader file, string line)
        {
            line = line.Replace("public ", "");
            string[] words = line.Split(' ');
            if (words.Length != 2)
            {
                return;
            }

            var property = new Property();
            property.Name = words[1];
            property.Type = words[0];

            for (int i = 0; i < 3; i++)
            {
                line = file.ReadLine();
                if (line.Contains("set"))
                {
                    property.HasSet = true;
                }
                else if(line.Contains("public"))
                {
                    ProcessFunction(file, line);
                }
            }

            m_Propertys.Add(property);
        }

        public void PrintAllData()
        {
            for (int i = 0; i < m_Functions.Count; i++)
            {
                Console.WriteLine("函数名:" + m_Functions[i].Name);
                Console.WriteLine(" 返回值:" + m_Functions[i].RetType);

                for (int j = 0; j < m_Functions[i].Params.Count; j++)
                {
                    Console.Write(" 参数:" + m_Functions[i].Params[j].Name + ":" + m_Functions[i].Params[j].Type);
                }
                Console.WriteLine("");                
            }

            for (int i = 0; i < m_Propertys.Count; i++)
            {
                Console.WriteLine("属性名:" + m_Propertys[i].Name+":" + m_Propertys[i].Type + " : HasSet" + m_Propertys[i].HasSet);
            }

        }

        public void GenerateCS()
        {
            string name = m_ClassName + "_0.cs";
            if (File.Exists(name))
            {
                File.Delete(name);
            }

            var file = File.CreateText(name);
            file.WriteLine("using System;");
            file.WriteLine("using System.Runtime.CompilerServices;");
            file.WriteLine("");
            file.WriteLine("namespace " + m_NameSpace);
            file.WriteLine("{");
            file.WriteLine(N(4) + "public class " + m_ClassName + " : " + m_BaseClass);
            file.WriteLine(N(4) + "{");

            for (int i = 0; i < m_Propertys.Count; i++)
            {
                var property = m_Propertys[i];

                file.WriteLine(N(8) + "public " + property.Type + " " + property.Name);
                file.WriteLine(N(8) + "{");
                file.WriteLine(N(12) + "get");
                file.WriteLine(N(12) + "{");
                file.WriteLine(N(16) + "return _Get" + property.Name + "(NativeHandler);");
                file.WriteLine(N(12) + "}");

                if (property.HasSet)
                {
                    file.WriteLine(N(12) + "set");
                    file.WriteLine(N(12) + "{");
                    file.WriteLine(N(16) + "_Set" + property.Name + "(NativeHandler,value);");
                    file.WriteLine(N(12) + "}");
                }
                file.WriteLine(N(8) + "}");
                file.WriteLine();
            }

            for (int i = 0; i < m_Functions.Count; i++)
            {
                var function = m_Functions[i];
                file.Write(N(8) + "public " + function.RetType + " " + function.Name + "(");
                for (int j = 0; j < function.Params.Count; j++)
                {
                    file.Write(function.Params[j].Type + " ");
                    file.Write(function.Params[j].Name);
                    if (j != function.Params.Count - 1)
                    {
                        file.Write(",");
                    }
                }
                file.WriteLine(")");
                file.WriteLine(N(8) + "{");
                file.Write(N(12));
                if (function.RetType != "void")
                {
                    file.Write("return ");                    
                }

                file.Write("_" + function.Name + "(NativeHandler");

                for (int j = 0; j < function.Params.Count; j++)
                {
                    file.Write(",");
                    file.Write(function.Params[j].Name);                    
                }
                file.WriteLine(");");
                file.WriteLine(N(8) + "}");
                file.WriteLine();
            }

            for (int i = 0; i < m_Propertys.Count; i++)
            {
                var property = m_Propertys[i];
                file.WriteLine(N(8) + "[MethodImpl(MethodImplOptions.InternalCall)]");
                file.Write(N(8) + "private extern static ");
                file.Write(property.Type + " ");
                file.Write("_Get" + property.Name);
                file.WriteLine("(IntPtr handler);");

                if (property.HasSet)
                {
                    file.WriteLine(N(8) + "[MethodImpl(MethodImplOptions.InternalCall)]");
                    file.Write(N(8) + "private extern static void ");
                    file.Write("_Set" + property.Name);
                    file.Write("(IntPtr handler," + property.Type + " " + property.Name);
                    file.WriteLine(");");
                }
            }
            file.WriteLine();
            for (int i = 0; i < m_Functions.Count; i++)
            {
                var function = m_Functions[i];
                file.WriteLine(N(8) + "[MethodImpl(MethodImplOptions.InternalCall)]");
                file.Write(N(8) + "private extern static ");
                file.Write(function.RetType + " ");
                file.Write("_" + function.Name + "(IntPtr handler");

                for (int j = 0; j < function.Params.Count; j++)
                {
                    file.Write(",");
                    file.Write(function.Params[j].Type + " ");
                    file.Write(function.Params[j].Name);
                }
                file.WriteLine(");");
            }

            file.WriteLine(N(4) + "}");
            file.WriteLine("}");
            file.Close();
        }

        //static void UnrealEngine_ActorComponent_SendEventWithInt(UMonoComponent* _this, MonoString* evt, int data)
        //static void UnrealEngine_ActorComponent_SetActivited(UMonoComponent* _this, bool value)
        //static mono_bool UnrealEngine_ActorComponent_GetActivited(UMonoComponent* _this)
        
        public void GenerateCPP()
        {
            string name = m_ClassName + ".cpp";
            if (File.Exists(name))
            {
                File.Delete(name);
            }

            var file = File.CreateText(name);
            file.WriteLine();

            for (int i = 0; i < m_Functions.Count; i++)
            {
                var fun = m_Functions[i];

                file.Write("static " + CT(fun.RetType) + " " + m_NameSpace + "_");
                file.Write(m_ClassName + "_" + fun.Name + "(" + CT(m_ClassName) + "* _this");
                for (int j = 0; j < fun.Params.Count; j++)
                {
                    file.Write("," + CT(fun.Params[j].Type) + " " +fun.Params[j].Name);
                }
                file.WriteLine(")");
                file.WriteLine("{");
                file.WriteLine(N(4) + "if (_this == NULL)");
                file.WriteLine(N(4) + "{");
                file.WriteLine(N(8) + string.Format("GLog->Logf(ELogVerbosity::Error, TEXT(\"[{0}] {1} But _this is NULL.\"));",m_ClassName, fun.Name));
                file.WriteLine(N(8) + string.Format("return {0};",DefualtRet(fun.RetType)));
                file.WriteLine(N(4) + "}");
                file.WriteLine("");
                file.WriteLine("}");
                file.WriteLine("");
            }

            for (int i = 0; i < m_Propertys.Count; i++)
            {
                var property = m_Propertys[i];

                file.Write("static " + CT(property.Type) + " " + m_NameSpace + "_");
                file.Write(m_ClassName + "_Get" + property.Name + "(" + CT(m_ClassName) + "* _this");
                file.WriteLine(")");
                file.WriteLine("{");

                file.WriteLine(N(4) + "if (_this == NULL)");
                file.WriteLine(N(4) + "{");
                file.WriteLine(N(8) + string.Format("GLog->Logf(ELogVerbosity::Error, TEXT(\"[{0}] {1} But _this is NULL.\"));", m_ClassName, "Get" + property.Name));
                file.WriteLine(N(8) + string.Format("return {0};", DefualtRet(property.Type)));
                file.WriteLine(N(4) + "}");

                file.WriteLine("");
                file.WriteLine("}");
                file.WriteLine("");

                if (property.HasSet)
                {
                    file.Write("static void " + m_NameSpace + "_");
                    file.Write(m_ClassName + "_Set" + property.Name + "(" + CT(m_ClassName) + "* _this," + CT(property.Type));
                    file.WriteLine(" value)");
                    file.WriteLine("{");
                    file.WriteLine(N(4) + "if (_this == NULL)");
                    file.WriteLine(N(4) + "{");
                    file.WriteLine(N(8) + string.Format("GLog->Logf(ELogVerbosity::Error, TEXT(\"[{0}] {1} But _this is NULL.\"));", m_ClassName, "Set" + property.Name));
                    file.WriteLine(N(8) + "return ;");
                    file.WriteLine(N(4) + "}");

                    file.WriteLine("");
                    file.WriteLine("}");
                    file.WriteLine("");
                }                
            }

            file.WriteLine();

            ///mono_add_internal_call("UnrealEngine.SkeletalMeshComponent::_IsBodyGravityEnabled",
            //    reinterpret_cast<void*>(UnrealEngine_SkeletalMeshComponent_IsBodyGravityEnabled));


            for (int i = 0; i < m_Functions.Count; i++)
            {
                var fun = m_Functions[i];

                file.WriteLine("    mono_add_internal_call(\"" + m_NameSpace + "." + m_ClassName + "::_" + fun.Name + "\",");
                file.WriteLine("        reinterpret_cast<void*>(" + m_NameSpace + "_" + m_ClassName + "_" + fun.Name + "));");
            }

            for (int i = 0; i < m_Propertys.Count; i++)
            {
                var property = m_Propertys[i];

                file.WriteLine("    mono_add_internal_call(\"" + m_NameSpace + "." + m_ClassName + "::_Get" + property.Name + "\",");
                file.WriteLine("        reinterpret_cast<void*>(" + m_NameSpace + "_" + m_ClassName + "_Get" + property.Name + "));");
                if (property.HasSet)
                {
                    file.WriteLine("    mono_add_internal_call(\"" + m_NameSpace + "." + m_ClassName + "::_Set" + property.Name + "\",");
                    file.WriteLine("        reinterpret_cast<void*>(" + m_NameSpace + "_" + m_ClassName + "_Set" + property.Name + "));");
                }
            }
            file.WriteLine("");
            file.Close();
        }
        
        public string DefualtRet(string t)
        {
            if (m_DefaultValue.ContainsKey(t))
            {
                return m_DefaultValue[t];
            }
            else
            {
                return "NULL";
            }
        }

        public string CT(string type)
        {
            if (m_ToCppType.ContainsKey(type))
            {
                return m_ToCppType[type];
            }
            else
            {
                if (type.Contains("Component"))
                {
                    return "U" + type;
                }
                else {
                    return "A" + type;
                }
                
            }
        }

        private string N(int n)
        {
            return new string(' ',n);
        }
    }
}
