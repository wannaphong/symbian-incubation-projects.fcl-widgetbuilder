/*
* Copyright (c) {Year(s)} {Copyright owner}.
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.symbianfoundation.org/legal/sfl-v10.html".
*
* Initial Contributors:
* {Name} {Company} ? Initial contribution
*
* Contributors:
* {Name} {Company} ? {{Description of contribution}}
*
* Description:
* {{Description of the file}}
*
*/

#ifndef __TESTPUBLISHERAPPVIEW_h__
#define __TESTPUBLISHERAPPVIEW_h__

// INCLUDES
#include <coecntrl.h>
#include <babitflags.h>
#include <badesca.h>

#include "hswidgetobserver.h"

class CHsPublisher;

// CLASS DECLARATION
class CTestPublisherAppView : public CCoeControl, public MHsWidgetObserver
    {
public:
    // New methods

    /**
     * NewL.
     * Two-phased constructor.
     * Create a CTestPublisherAppView object, which will draw itself to aRect.
     * @param aRect The rectangle this view will be drawn to.
     * @return a pointer to the created instance of CTestPublisherAppView.
     */
    static CTestPublisherAppView* NewL(const TRect& aRect);

    /**
     * NewLC.
     * Two-phased constructor.
     * Create a CTestPublisherAppView object, which will draw itself
     * to aRect.
     * @param aRect Rectangle this view will be drawn to.
     * @return A pointer to the created instance of CTestPublisherAppView.
     */
    static CTestPublisherAppView* NewLC(const TRect& aRect);

    /**
     * ~CTestPublisherAppView
     * Virtual Destructor.
     */
    virtual ~CTestPublisherAppView();

public:
    // Functions from base classes

    /**
     * From CCoeControl, Draw
     * Draw this CTestPublisherAppView to the screen.
     * @param aRect the rectangle of this view that needs updating
     */
    void Draw(const TRect& aRect) const;

    /**
     * From CoeControl, SizeChanged.
     * Called by framework when the view size is changed.
     */
    virtual void SizeChanged();

    /**
     * From CoeControl, HandlePointerEventL.
     * Called by framework when a pointer touch event occurs.
     * Note: although this method is compatible with earlier SDKs, 
     * it will not be called in SDKs without Touch support.
     * @param aPointerEvent the information about this event
     */
    virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private:
    // from MHsWidgetObserver
    
    /**
     * @see MHsWidgetObserver
     */
    const TDesC& Identity();    
    
    /**
     * @see MHsWidgetObserver
     */
    void NotifyWidgetStarted( 
        const TDesC& aWidgetId, 
        MHsWidgetObserver::EStartReason aReason );
    
    /**
     * @see MHsWidgetObserver
     */
    void NotifyWidgetStopped( 
        const TDesC& aWidgetId, 
        MHsWidgetObserver::EStopReason aReason );
    
    /**
     * @see MHsWidgetObserver
     */
    void NotifyWidgetState( 
        const TDesC& aWidgetId, 
        MHsWidgetObserver::EState aState );

    /**
     * @see MHsWidgetObserver
     */
    void NotifyWidgetEvent(
        const TDesC& aWidgetId,
        const TDesC& aEvent,
        const TDesC& aParam );
    
private:
    // Constructors

    /**
     * ConstructL
     * 2nd phase constructor.
     * Perform the second phase construction of a
     * CTestPublisherAppView object.
     * @param aRect The rectangle this view will be drawn to.
     */
    void ConstructL(const TRect& aRect);

    /**
     * CTestPublisherAppView.
     * C++ default constructor.
     */
    CTestPublisherAppView();
    
    void PublishL( const TDesC& aWidgetId );
private:
    // data
    
    /** Publisher, owned */
    CHsPublisher* iPublisher;
    /** Id of active widget instance, owned */
    CDesCArrayFlat* iWidgetIds;
    /** Flags */
    TBitFlags iFlags;  
    /** Helper to alternate published image */
    TBool iFeedCnt;
    };

#endif // __TESTPUBLISHERAPPVIEW_h__
// End of File
