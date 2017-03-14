#pragma once

class FMonoComponentDetails : public IDetailCustomization
{
public:
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IDetailCustomization> MakeInstance();

	bool IsEditEnabled() const;

	FReply OnEditClicked();

private:
	FText GetSearchAssetsHintText() const;

	void OnSearchBoxChanged(const FText& InSearchText);

	void OnSearchBoxCommitted(const FText& InSearchText, ETextCommit::Type CommitInfo);

	TArray<FString> GetAssetSearchSuggestions() const;

	/** IDetailCustomization interface */
	virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;

	TWeakObjectPtr<class MonoComponent> MonoComponent;
	
	/** The text box used to search for assets */
	TSharedPtr<SAssetSearchBox> SearchBoxPtr;
};