#include "MyProject.h"
#include "MySlateImage.h"

DECLARE_CYCLE_STAT(TEXT("OnPaint SMySlateImage"), STAT_SlateOnPaint_SMySlateImage, STATGROUP_Slate);

/**
* Construct this widget
*
* @param	InArgs	The declaration data for this widget
*/
void SMySlateImage::Construct(const FArguments& InArgs)
{
	Image = InArgs._Image;
	ColorAndOpacity = InArgs._ColorAndOpacity;
	Thickness = InArgs._Thickness.Get();
	OnMouseButtonDownHandler = InArgs._OnMouseButtonDown;
}

void SMySlateImage::SetThickness(float InThickness)
{
	Thickness = InThickness;
}

int32 SMySlateImage::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
#ifdef SLATE_HD_STATS
	SCOPE_CYCLE_COUNTER(STAT_SlateOnPaint_SSoftEdgeImage);
#endif
	const FSlateBrush* ImageBrush = Image.Get();

	if ((ImageBrush != nullptr) && (ImageBrush->DrawAs != ESlateBrushDrawType::NoDrawType))
	{
		const bool bIsEnabled = ShouldBeEnabled(bParentEnabled);
		// error C2440: 'initializing': cannot convert from 'ESlateDrawEffect' to 'uint32'
		//  note: This conversion requires an explicit cast (static_cast, C-style cast or function-style cast)
		const uint32 DrawEffects = (uint32)(bIsEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect);

		// error C2248: 'FColor::FColor': cannot access private member declared in class 'FColor'
		//const FColor FinalColorAndOpacity(InWidgetStyle.GetColorAndOpacityTint() * ColorAndOpacity.Get().GetColor(InWidgetStyle) * ImageBrush->GetTint(InWidgetStyle));
		const FLinearColor FinalColorAndOpacity(InWidgetStyle.GetColorAndOpacityTint() * ColorAndOpacity.Get().GetColor(InWidgetStyle) * ImageBrush->GetTint(InWidgetStyle));

		//For Thickness
		for (int32 v = 0; v < Thickness; v++)
		{
			//Size
			FVector2D AdjustedSize =
				FVector2D(
					AllottedGeometry.GetLocalSize().X - v * 2,
					AllottedGeometry.GetLocalSize().Y - v * 2
				);

			//There's a warning about using this constructor in Geometry.h
			//		But it looks like the code was fixed in Geometry.cpp to use layout transform properly. Plus all render transforms work great in Editor.
			//			So keeping this for now :)
			FPaintGeometry PaintGeom =
				AllottedGeometry.ToPaintGeometry(
					FVector2D(v, v),		//Local Translation
					AdjustedSize,		//Local Size
					1			//Local Scale
				);

			// warning C4996: 'FSlateDrawElement::MakeBox': ClippingRects are no longer supplied for individual draw element calls.  If you require a specialized clipping rect, use PushClip / PopClip on the WindowElementList, otherwise, just remove the parameter. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
			// error C2665: 'FSlateDrawElement::MakeBox': none of the 4 overloads could convert all the argument types
			//FSlateDrawElement::MakeBox(
			//	OutDrawElements, 	//Out
			//	LayerId,
			//	PaintGeom, 		//Paint Geom
			//	ImageBrush, 		//Brush
			//	MyClippingRect, 		//Clip
			//	(ESlateDrawEffect)DrawEffects,
			//	FinalColorAndOpacity 	//Color and Opacity
			//);

			// ref : UnrealEngine\Engine\Source\Editor\Sequencer\Private\SSequencerSection.cpp
			// ref: int32 SSequencerSection::OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const

			// ref: UnrealEngine\Engine\Source\Developer\TreeMap\STreeMap.cpp
			// ref: int32 STreeMap::OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const
			FSlateClippingZone ClippingZone(MyClippingRect);
			OutDrawElements.PushClip(ClippingZone);

			FSlateDrawElement::MakeBox(
				OutDrawElements, 	//Out
				LayerId,
				PaintGeom, 		//Paint Geom
				ImageBrush, 		//Brush
				(ESlateDrawEffect)DrawEffects,
				FinalColorAndOpacity 	//Color and Opacity
			);

			OutDrawElements.PopClip();

		} //For loop
	}
	return LayerId;
}