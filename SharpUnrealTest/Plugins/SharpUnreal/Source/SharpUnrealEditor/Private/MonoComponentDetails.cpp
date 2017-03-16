// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SharpUnrealEditorPrivatePCH.h"
#include "MonoComponentDetails.h"
#include "MonoComponent.h"
#include "MonoRuntime.h"

#define LOCTEXT_NAMESPACE "MonoComponentDetails"

TSharedRef<IDetailCustomization> FMonoComponentDetails::MakeInstance()
{
	return MakeShareable(new FMonoComponentDetails);
}

void FMonoComponentDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//获取正在编辑的对象的引用
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);
	if (Objects.Num() != 1)
	{
		return;
	}

	m_MonoComponent = Cast<UMonoComponent>(Objects[0].Get());
	if (!m_MonoComponent.Get())
	{
		return;
	}
	
	//自定义一个编辑MonoComponent的UI
	auto widgets = SNew(SHorizontalBox);
	widgets->AddSlot().FillWidth(8.0f)
		.Padding(2.0f, 1.0f)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		[
			SAssignNew(m_SearchBoxPtr, SAssetSearchBox)
			.HintText(this, &FMonoComponentDetails::OnHintText)
			.OnTextCommitted(this, &FMonoComponentDetails::OnTextCommitted)
			.PossibleSuggestions(this, &FMonoComponentDetails::OnPossibleSuggestions)
		];

	widgets->AddSlot().FillWidth(5.0f)
		.Padding(0.5f, 1.0f)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		[
			SNew(SButton)
			.OnClicked(this, &FMonoComponentDetails::OnApplyClicked)
			.Content()
			[
				SNew(STextBlock)				
				.Text(LOCTEXT("MonoComponent", "Apply"))
				.ToolTipText(LOCTEXT("MonoComponent", "Apply."))
			]
		];


	DetailBuilder.EditCategory("MonoComponent", FText::GetEmpty(), ECategoryPriority::Important)
	.AddCustomRow(FText::GetEmpty())
	[
		widgets
	];

}

FReply FMonoComponentDetails::OnApplyClicked()
{
	GLog->Log(ELogVerbosity::Error, TEXT("[MonoDetail] OnApplyClicked."));
	if (m_MonoComponent != NULL)
	{
		if (m_CommitedComponentName.Len() > 0) 
		{
			//PreEditChange跟PostEditChange保证了编辑完Property之后场景会被设置为已更改状态
			UProperty* NameProperty = FindField<UProperty>(
				UMonoComponent::StaticClass(), "ComponentName");
			m_MonoComponent->PreEditChange(NameProperty);

			//设置脚本名字
			m_MonoComponent->ComponentName = m_CommitedComponentName;
			
			FPropertyChangedEvent PropertyChangedEvent(NameProperty);
			m_MonoComponent->PostEditChangeProperty(PropertyChangedEvent);
		}		
	}
	else
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoDetail] MonoComponent Is Null."));
	}
	return FReply::Handled();
}

FText FMonoComponentDetails::OnHintText() const
{
	return NSLOCTEXT("SharpUnreal", "MonoComponent", "Search MonoComponent");
}


void FMonoComponentDetails::OnTextCommitted(const FText& InSearchText, ETextCommit::Type CommitInfo)
{
	m_CommitedComponentName = InSearchText.ToString();
}

//根据MonoRuntime获取Dll中继承于ActorComponent的类的列表
TArray<FString> FMonoComponentDetails::OnPossibleSuggestions() const
{
	return MonoRuntime::Instance()->GetAllMonoComponent();
}

#undef LOCTEXT_NAMESPACE
