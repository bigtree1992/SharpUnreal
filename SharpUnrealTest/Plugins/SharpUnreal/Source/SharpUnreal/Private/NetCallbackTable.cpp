#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "NetCallbackTable.h"

#include <mono/jit/jit.h>
#include "mono/metadata/metadata.h"
#include <mono/metadata/assembly.h>
#include <mono/metadata/image.h>
#include <mono/metadata/class.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/tokentype.h>
#include <mono/utils/mono-counters.h>

static TMap<MonoClass*,TMap<int, _MonoMethod*> *> s_FunctionMap;

bool NetCallbackTable::CreateTable(_MonoImage* engine, _MonoImage* main) 
{
	MonoClass* base = mono_class_from_name(engine, "UnrealEngine", "NetComponent");
	if (base == NULL)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] NetCallbackTable::CreateTable Failed! Not Find NetComponent."));
		return false;
	}

	MonoClass* rpc_klass = mono_class_from_name(engine, "UnrealEngine", "RPC");
	if (rpc_klass == NULL)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] NetCallbackTable::CreateTable Failed! Not Find RPC."));
		return false;
	}

	MonoProperty* property = mono_class_get_property_from_name(rpc_klass, "ID");
	if (property == NULL)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] NetCallbackTable::CreateTable Failed! Not Find ID Property."));
		return false;
	}

	unsigned length = 0;
	int rows = mono_image_get_table_rows(main, MONO_TABLE_TYPEDEF);
	for (int i = 1; i < rows; ++i)
	{
		MonoClass * klass = mono_class_get(main, (i + 1) | MONO_TOKEN_TYPE_DEF);

		if (klass == NULL)
		{
			continue;
		}

		if (mono_class_is_subclass_of(klass, base, false))
		{
			TMap<int, _MonoMethod*>* map = s_FunctionMap.Add(klass, new TMap<int, _MonoMethod*>());

			void* iter = NULL;
			MonoMethod *method = NULL;
			while (true)
			{
				method = mono_class_get_methods(klass, &iter);
				if (method == NULL) 
				{
					break;
				}

				MonoCustomAttrInfo*  attr_info = mono_custom_attrs_from_method(method);
				if (attr_info == NULL) 
				{
					continue;
				}

				MonoObject* attr_object = mono_custom_attrs_get_attr(attr_info, rpc_klass);
				if (attr_object == NULL) 
				{
					continue;
				}

				if (mono_object_get_class(attr_object) != rpc_klass) 
				{
					continue;
				}
				
				
				//GLog->Logf(ELogVerbosity::Warning,
				//	TEXT("[MonoRuntime] NetCallbackTable A Net Method : %s"), ANSI_TO_TCHAR(mono_method_get_name(method)));

				int id;
				MonoObject* id_object = mono_property_get_value(property, attr_object, NULL, NULL);
				if (id_object == NULL)
				{
					continue;
				}

				id = *(int*)(mono_object_unbox(id_object));
				if (!map->Contains(id))
				{
					map->Add(id, method);
				}
				else
				{
					GLog->Logf(ELogVerbosity::Warning, 
						TEXT("[MonoRuntime] NetCallbackTable::CreateTable Find A Repeated Net Id(%d) Function In Method (%s).")
						, id, ANSI_TO_TCHAR(mono_method_get_name(method)));
				}
			}
		}
	}

	return true;
}

void NetCallbackTable::DestroyTable() 
{
	for (auto& elem : s_FunctionMap)
	{
		if (elem.Value)
		{
			delete elem.Value;
		}
	}
	s_FunctionMap.Empty();
}

_MonoMethod* NetCallbackTable::GetMethod(_MonoClass* mono_class, int id)
{
	if (!s_FunctionMap.Contains(mono_class)) 
	{
		return NULL;		
	}

	TMap<int, _MonoMethod*>* map = s_FunctionMap[mono_class];
	if (map == NULL)
	{
		return NULL;		
	}

	if (!map->Contains(id))
	{
		return NULL;
	}
	
	MonoMethod* function = (*map)[id];
	return function;
}

