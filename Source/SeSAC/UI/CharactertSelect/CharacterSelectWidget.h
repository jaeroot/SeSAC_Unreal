// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/UI/UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectWidget.generated.h"

class UCharacterSelectInfoWidget;
class ASelectPawn;
/**
 * 
 */
UCLASS()
class SESAC_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
protected:
	UButton* mStartButton;
	UCharacterSelectInfoWidget* mInfoWidget;
	

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void StartButtonEnable(bool Enable);
	void SetSelectPawn(ASelectPawn* Pawn);

	void SetPlayerImage(UMaterialInstance* Mtrl);
	void SetPlayerName(const FString& Name);
	
protected:
	UFUNCTION()
	void StartButtonClick();


protected:

	virtual FReply NativeOnFocusReceived( const FGeometry& InGeometry, const FFocusEvent& InFocusEvent ) override;
	virtual void NativeOnFocusLost( const FFocusEvent& InFocusEvent ) override;
	virtual void NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual FNavigationReply NativeOnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent, const FNavigationReply& InDefaultReply) override;
	virtual FReply NativeOnKeyChar( const FGeometry& InGeometry, const FCharacterEvent& InCharEvent ) override;
	virtual FReply NativeOnPreviewKeyDown( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent ) override;
	virtual FReply NativeOnKeyDown( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent ) override;
	virtual FReply NativeOnKeyUp( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent ) override;
	virtual FReply NativeOnAnalogValueChanged( const FGeometry& InGeometry, const FAnalogInputEvent& InAnalogEvent ) override;
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnPreviewMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseButtonUp( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseMove( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnMouseEnter( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnMouseLeave( const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseWheel( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseButtonDoubleClick( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnDragDetected( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation ) override;
	virtual void NativeOnDragEnter( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual void NativeOnDragLeave( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual bool NativeOnDragOver( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual void NativeOnDragCancelled( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual FReply NativeOnTouchGesture( const FGeometry& InGeometry, const FPointerEvent& InGestureEvent ) override;
	virtual FReply NativeOnTouchStarted( const FGeometry& InGeometry, const FPointerEvent& InGestureEvent ) override;
	virtual FReply NativeOnTouchMoved( const FGeometry& InGeometry, const FPointerEvent& InGestureEvent ) override;
	virtual FReply NativeOnTouchEnded( const FGeometry& InGeometry, const FPointerEvent& InGestureEvent ) override;
	virtual FReply NativeOnMotionDetected( const FGeometry& InGeometry, const FMotionEvent& InMotionEvent ) override;
	virtual FReply NativeOnTouchForceChanged(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent) override;
	virtual FCursorReply NativeOnCursorQuery( const FGeometry& InGeometry, const FPointerEvent& InCursorEvent ) override;
	virtual FNavigationReply NativeOnNavigation(const FGeometry& InGeometry, const FNavigationEvent& InNavigationEvent) override;
	virtual void NativeOnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;

protected:
	ASelectPawn* mOnSelectPawn = nullptr;


};
