// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectWidget.h"

#include "CharacterSelectInfoWidget.h"
#include "SeSAC/Player/SelectPawn.h"

void UCharacterSelectWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UE_LOG(LogTemp, Warning, TEXT("NativeOnInitialized"));
}

void UCharacterSelectWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	UE_LOG(LogTemp, Warning, TEXT("NativePreConstruct"));
}

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("GameStart")));
	if (IsValid(mStartButton))
	{
		mStartButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::StartButtonClick);
	}

	mInfoWidget = Cast<UCharacterSelectInfoWidget>(GetWidgetFromName(TEXT("WB_CharacterSelectInfo")));

	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct"));
}

void UCharacterSelectWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UE_LOG(LogTemp, Warning, TEXT("NativeDestruct"));
}

void UCharacterSelectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCharacterSelectWidget::StartButtonClick()
{
	if (!IsValid(mOnSelectPawn))
	{
		return;
	}
	
	FString Option = FString::Printf(TEXT("Job=%d"), static_cast<int32>(mOnSelectPawn->GetJob()));
	
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"), true, Option);
}

void UCharacterSelectWidget::StartButtonEnable(bool Enable)
{
	mStartButton->SetIsEnabled(Enable);

	if (Enable)
	{
		mInfoWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		mInfoWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UCharacterSelectWidget::SetSelectPawn(ASelectPawn* Pawn)
{
	mOnSelectPawn = Pawn;
}

FReply UCharacterSelectWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	FReply result = Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnFocusReceived"));

	return result;
}

void UCharacterSelectWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnFocusLost"));
}

void UCharacterSelectWidget::NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath,
	const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusChanging(PreviousFocusPath, NewWidgetPath, InFocusEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnFocusChanging"));
}

void UCharacterSelectWidget::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnAddedToFocusPath"));
}

void UCharacterSelectWidget::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnRemovedFromFocusPath"));
}

FNavigationReply UCharacterSelectWidget::NativeOnNavigation(const FGeometry& MyGeometry,
	const FNavigationEvent& InNavigationEvent, const FNavigationReply& InDefaultReply)
{
	FNavigationReply result = Super::NativeOnNavigation(MyGeometry, InNavigationEvent, InDefaultReply);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnNavigation"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnKeyChar(const FGeometry& InGeometry, const FCharacterEvent& InCharEvent)
{
	FReply result = Super::NativeOnKeyChar(InGeometry, InCharEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnKeyChar"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply result = Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnPreviewKeyDown"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply result = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnKeyDown"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply result = Super::NativeOnKeyUp(InGeometry, InKeyEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnKeyUp"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnAnalogValueChanged(const FGeometry& InGeometry,
	const FAnalogInputEvent& InAnalogEvent)
{
	FReply result = Super::NativeOnAnalogValueChanged(InGeometry, InAnalogEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnAnalogValueChanged"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonDown"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnPreviewMouseButtonDown"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonUp"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseMove"));

	return result;
}

void UCharacterSelectWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseEnter"));
}

void UCharacterSelectWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseLeave"));
}

FReply UCharacterSelectWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseWheel(InGeometry, InMouseEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseWheel"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonDoubleClick"));

	return result;
}

void UCharacterSelectWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnDragDetected"));
}

void UCharacterSelectWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnDragEnter"));
}

void UCharacterSelectWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnDragLeave"));
}

bool UCharacterSelectWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	bool result = Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnDragOver"));

	return result;
}

bool UCharacterSelectWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	bool result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnDrop"));

	return result;
}

void UCharacterSelectWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnDragCancelled"));
}

FReply UCharacterSelectWidget::NativeOnTouchGesture(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	FReply result = Super::NativeOnTouchGesture(InGeometry, InGestureEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnTouchGesture"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	FReply result = Super::NativeOnTouchStarted(InGeometry, InGestureEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnTouchStarted"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	FReply result = Super::NativeOnTouchMoved(InGeometry, InGestureEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnTouchMoved"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	FReply result = Super::NativeOnTouchEnded(InGeometry, InGestureEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnTouchEnded"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnMotionDetected(const FGeometry& InGeometry, const FMotionEvent& InMotionEvent)
{
	FReply result = Super::NativeOnMotionDetected(InGeometry, InMotionEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnMotionDetected"));

	return result;
}

FReply UCharacterSelectWidget::NativeOnTouchForceChanged(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent)
{
	FReply result = Super::NativeOnTouchForceChanged(MyGeometry, TouchEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnTouchForceChanged"));

	return result;
}

FCursorReply UCharacterSelectWidget::NativeOnCursorQuery(const FGeometry& InGeometry,
	const FPointerEvent& InCursorEvent)
{
	FCursorReply result = Super::NativeOnCursorQuery(InGeometry, InCursorEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnCursorQuery"));

	return result;
}

FNavigationReply UCharacterSelectWidget::NativeOnNavigation(const FGeometry& InGeometry,
	const FNavigationEvent& InNavigationEvent)
{
	FNavigationReply result = Super::NativeOnNavigation(InGeometry, InNavigationEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnNavigation"));

	return result;
}

void UCharacterSelectWidget::NativeOnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent)
{
	Super::NativeOnMouseCaptureLost(CaptureLostEvent);

	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseCaptureLost"));
}
