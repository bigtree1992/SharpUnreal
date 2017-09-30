#pragma once

class FMonoComponentDetails : public IDetailCustomization
{
public:
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IDetailCustomization> MakeInstance();

private:
	FText OnHintText() const;

	void OnTextCommitted(const FText& InSearchText, ETextCommit::Type CommitInfo);

	FReply OnApplyClicked();

	TArray<FString> OnPossibleSuggestions() const;

	virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;
	
private:
	TArray<TWeakObjectPtr<UObject>> ObjectsCustomized;
	TSharedPtr<SAssetSearchBox> m_SearchBoxPtr;
	FString m_CommitedComponentName;
};