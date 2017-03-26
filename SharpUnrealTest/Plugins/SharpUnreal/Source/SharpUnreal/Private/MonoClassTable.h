// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

struct _MonoClass;
/**
 * 保存了MonoClass跟UClass的对应关系
 */
class MonoClassTable
{
public:
	static void CreateTable();
	static void DestroyTable();
	static UClass* GetUClassFromName(const FName& name);

};
