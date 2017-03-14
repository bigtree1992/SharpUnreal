// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SharpUnrealEditorPrivatePCH.h"
#include "MonoComponentDetails.h"
#include "MonoComponent.h"

#define LOCTEXT_NAMESPACE "MonoComponentDetails"

TSharedRef<IDetailCustomization> FMonoComponentDetails::MakeInstance()
{
	return MakeShareable(new FMonoComponentDetails);
}

bool FMonoComponentDetails::IsEditEnabled() const
{
	return true;
}

FReply FMonoComponentDetails::OnEditClicked()
{
	return FReply::Handled();
}

void FMonoComponentDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	auto widgets = SNew(SVerticalBox);
	widgets->AddSlot().FillHeight(1.0f)
		.Padding(2.0f, 0.0f)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		[
			SAssignNew(SearchBoxPtr, SAssetSearchBox)
			.HintText(this, &FMonoComponentDetails::GetSearchAssetsHintText)
			.OnTextChanged(this, &FMonoComponentDetails::OnSearchBoxChanged)
			.OnTextCommitted(this, &FMonoComponentDetails::OnSearchBoxCommitted)
			.PossibleSuggestions(this, &FMonoComponentDetails::GetAssetSearchSuggestions)
		];

		widgets->AddSlot().FillHeight(1.0f)
		.Padding(2.0f, 0.0f)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.Padding(2.0f, 0.0f)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
			[
				SNew(SEditableText)
				.HintText(FText::FromString(TEXT("Editable:")))
				.OnTextCommitted_Lambda([=](const FText& InText, ETextCommit::Type InCommitType) {
					GLog->Log(InText);
				})
			]

			
		];


	DetailBuilder.EditCategory("MonoComponent", FText::GetEmpty(), ECategoryPriority::Important)
	.AddCustomRow(FText::GetEmpty())
	[
			widgets
	];

}

FText FMonoComponentDetails::GetSearchAssetsHintText() const
{
	return NSLOCTEXT("ContentBrowser", "SearchBoxHint", "Search Assets");
}

void FMonoComponentDetails::OnSearchBoxChanged(const FText& InSearchText)
{

}

void FMonoComponentDetails::OnSearchBoxCommitted(const FText& InSearchText, ETextCommit::Type CommitInfo)
{

}

TArray<FString> FMonoComponentDetails::GetAssetSearchSuggestions() const
{
	TArray<FString> AllSuggestions;
	AllSuggestions.Add(FString(TEXT("Sugges1")));
	AllSuggestions.Add(FString(TEXT("Sugges2")));
	AllSuggestions.Add(FString(TEXT("Sugges3")));
	AllSuggestions.Add(FString(TEXT("Sugges4")));
	AllSuggestions.Add(FString(TEXT("Sugges5")));
	AllSuggestions.Add(FString(TEXT("Sugges6")));
	AllSuggestions.Add(FString(TEXT("Sugges7")));
	AllSuggestions.Add(FString(TEXT("Sugges8")));
	AllSuggestions.Add(FString(TEXT("Sugges9")));
	AllSuggestions.Add(FString(TEXT("Sugges0")));
	AllSuggestions.Add(FString(TEXT("1Sugges4")));
	AllSuggestions.Add(FString(TEXT("2Sugges4")));
	AllSuggestions.Add(FString(TEXT("3Sugges4")));
	AllSuggestions.Add(FString(TEXT("4Sugges4")));
	AllSuggestions.Add(FString(TEXT("5Sugges4")));
	AllSuggestions.Add(FString(TEXT("6Sugges4")));
	AllSuggestions.Add(FString(TEXT("7Sugges4")));
	AllSuggestions.Add(FString(TEXT("8Sugges4")));
	AllSuggestions.Add(FString(TEXT("9Sugges4")));
	AllSuggestions.Add(FString(TEXT("0Sugges4")));
	AllSuggestions.Add(FString(TEXT("aSugges4")));
	AllSuggestions.Add(FString(TEXT("vSugges4")));

	AllSuggestions.Add(FString(TEXT("rSugges4")));
	AllSuggestions.Add(FString(TEXT("tSugges4")));
	AllSuggestions.Add(FString(TEXT("ySugges4")));
	AllSuggestions.Add(FString(TEXT("uSugges4")));
	AllSuggestions.Add(FString(TEXT("iSugges4")));
	AllSuggestions.Add(FString(TEXT("oSugges4")));
	AllSuggestions.Add(FString(TEXT("pSugges4")));

	return AllSuggestions;
}

#undef LOCTEXT_NAMESPACE
