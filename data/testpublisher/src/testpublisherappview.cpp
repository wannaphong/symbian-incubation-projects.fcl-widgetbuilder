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


// INCLUDE FILES
#include <coemain.h>
#include <aknglobalnote.h>
#include <aknsconstants.h>
#include "TestPublisherAppView.h"
#include "hspublisher.h"

_LIT( KId, "#replaceuid#:#replace#" );

// Type definitions
enum TFlags
    {
    ERequirePublish =1,
    EPublishAllowed
    };


_LIT( KGNews1, "World news!");
_LIT( KGFeed1, "Bangkok tense as thousands remain on streets." );
_LIT( KGFeed2, "France frees killer of former Iran PM." );
_LIT( KGFeed3, "Lingering ash cloud spurs new rules." );

_LIT( KSNews1, "Sport news!");
_LIT( KSFeed1, "Motorsport: Webber dampens title talk." );
_LIT( KSFeed2, "Cricket: IPL boss seeks reinstatement." );
_LIT( KSFeed3, "Tennis: Nadal too strong for Federer." );


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestPublisherAppView* CTestPublisherAppView::NewL(const TRect& aRect)
    {
    CTestPublisherAppView* self = CTestPublisherAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestPublisherAppView* CTestPublisherAppView::NewLC(const TRect& aRect)
    {
    CTestPublisherAppView* self = new (ELeave) CTestPublisherAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestPublisherAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    iWidgetIds = new (ELeave) CDesCArrayFlat(5);
    //Create the publihser interface
    iPublisher = CHsPublisher::NewL( *this );
    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CTestPublisherAppView::CTestPublisherAppView()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CTestPublisherAppView::~CTestPublisherAppView()
    {
    delete iPublisher;
    delete iWidgetIds;
    }

// -----------------------------------------------------------------------------
// Draws the display.
// -----------------------------------------------------------------------------
//
void CTestPublisherAppView::Draw(const TRect& /*aRect*/) const
    {
    // Get the standard graphics context
    CWindowGc& gc = SystemGc();

    // Gets the control's extent
    TRect drawRect(Rect());

    // Clears the screen
    gc.Clear(drawRect);

    }

// -----------------------------------------------------------------------------
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CTestPublisherAppView::SizeChanged()
    {
    DrawNow();
    }

// -----------------------------------------------------------------------------
// Called by framework to handle pointer touch events.
// Note: although this method is compatible with earlier SDKs, 
// it will not be called in SDKs without Touch support.
// -----------------------------------------------------------------------------
//
void CTestPublisherAppView::HandlePointerEventL(
        const TPointerEvent& aPointerEvent)
    {

    // Call base class HandlePointerEventL()
    CCoeControl::HandlePointerEventL(aPointerEvent);
    }

// -----------------------------------------------------------------------------
//
// 
// -----------------------------------------------------------------------------
//
const TDesC& CTestPublisherAppView::Identity()
    {
    return KId();
    }

// -----------------------------------------------------------------------------
//
// 
// -----------------------------------------------------------------------------
//
void CTestPublisherAppView::NotifyWidgetStarted( const TDesC& aWidgetId,     
    MHsWidgetObserver::EStartReason /*aReason*/ )
    {
    TInt pos( KErrNotFound );
    if( iWidgetIds->Find( aWidgetId, pos ) != 0)
        {
        iWidgetIds->AppendL( aWidgetId );
        }
    
    // Publish after widget is alive, lazy.
    iFlags.Set( ERequirePublish );
    }

// -----------------------------------------------------------------------------
// 
// 
// -----------------------------------------------------------------------------
void CTestPublisherAppView::NotifyWidgetStopped( const TDesC& aWidgetId,     
    MHsWidgetObserver::EStopReason /*aReason*/ )
    {
    TInt pos( KErrNotFound );
    if( iWidgetIds->Find( aWidgetId, pos ) == 0 )
        {
        // widget removed from homescreen or in invisible page
        iWidgetIds->Delete( pos );
        }
    }

// -----------------------------------------------------------------------------
// 
// 
// -----------------------------------------------------------------------------
//
void CTestPublisherAppView::NotifyWidgetState( const TDesC& aWidgetId,      
    MHsWidgetObserver::EState aState )
    {
    if ( aState == MHsWidgetObserver::EAlive )
        {
        iFlags.Set( EPublishAllowed );
        
        // PublishL will determine if it is necessary to update widget data
        TRAP_IGNORE( PublishL( aWidgetId ) );
        }
    else if ( aState == MHsWidgetObserver::ESuspend )
        {
        iFlags.Clear( EPublishAllowed );
        }
    }

// -----------------------------------------------------------------------------
// 
// 
// -----------------------------------------------------------------------------
//
void CTestPublisherAppView::NotifyWidgetEvent( const TDesC& aWidgetId,    
    const TDesC& aEvent, const TDesC& /*aParam*/ )
    {
    if ( aEvent == _L("imageclicked"))
        {
        CAknGlobalNote* globalNote = CAknGlobalNote::NewLC();
        TInt noteId = globalNote->ShowNoteL( EAknGlobalInformationNote, _L("Image clicked"));
        User::After( 2000 );  // waiting for 3 seconds
        // discard note
        globalNote->CancelNoteL( noteId );
        CleanupStack::PopAndDestroy();
        iPublisher->StartTransaction( aWidgetId );
        iPublisher->PublishText(
                aWidgetId, _L8("text2"), KGFeed3 );
        iPublisher->CommitTransaction( aWidgetId );
        }
    else if ( aEvent == _L("textclicked") )
        {
        CAknGlobalNote* globalNote = CAknGlobalNote::NewLC();
        TInt noteId = globalNote->ShowNoteL( EAknGlobalInformationNote, _L("Text clicked") );
        User::After( 2000 );  // waiting for 3 seconds
        // discard note
        globalNote->CancelNoteL( noteId );
        CleanupStack::PopAndDestroy();
        iPublisher->StartTransaction( aWidgetId );
        iPublisher->PublishText(
            aWidgetId, _L8("text3"), KGFeed2 );
        iPublisher->CommitTransaction( aWidgetId );
        }
    else if ( aEvent == _L("widgetclicked") )
        {
        CAknGlobalNote* globalNote = CAknGlobalNote::NewLC();
        TInt noteId = globalNote->ShowNoteL( EAknGlobalInformationNote, _L("Widget clicked") );
        User::After( 3000 );  // waiting for 3 seconds
        // discard note
        globalNote->CancelNoteL( noteId );
        CleanupStack::PopAndDestroy();
        iPublisher->StartTransaction( aWidgetId );
        if( !iFeedCnt )
            {
            iPublisher->PublishText(
                aWidgetId, _L8("text2"), KGFeed3 );
            iFeedCnt = ETrue;
            }
        else
            {iPublisher->PublishText(
                    aWidgetId, _L8("text3"), KGFeed2 );
            iFeedCnt = EFalse;
            }
        
        iPublisher->CommitTransaction( aWidgetId );
        }
    else if( aEvent == _L("OnTitleScrolled"))
        {
        TInt pos( KErrNotFound );
        if( iWidgetIds->Find( aWidgetId, pos ) == 0 && pos % 2 == 1 )
            {
            iPublisher->StartTransaction( aWidgetId );
            if( iFeedCnt == 0 )
                {
                iPublisher->PublishImage(aWidgetId,
                         _L8("image1"), _L("c:\\data\\Installs\\cricket.png"));
                iFeedCnt++;
                }
            else if( iFeedCnt == 1 )
                {
                iPublisher->PublishImage(aWidgetId,
                         _L8("image1"), _L("c:\\data\\Installs\\tennis.png"));
                iFeedCnt++;
                }
            else if( iFeedCnt == 2)
                {
                iPublisher->PublishImage(aWidgetId,
                         _L8("image1"), _L("c:\\data\\Installs\\f1.png"));
                iFeedCnt = 0;
                }
            iPublisher->CommitTransaction( aWidgetId );
            }
        }
    
    }

// -----------------------------------------------------------------------------
// 
// 
// -----------------------------------------------------------------------------
//
void CTestPublisherAppView::PublishL( const TDesC& aWidgetId )
    {
    if ( iFlags.IsClear( ERequirePublish ) )
        {        
        // Can't publish without widget instance id or no reason to publish
        return;
        }
    if ( iFlags.IsSet( EPublishAllowed ) )
        {            
        iPublisher->StartTransaction( aWidgetId );

        iPublisher->PublishImage(aWidgetId,
             _L8("graphic"), _L("c:\\data\\Installs\\rss.png"));
       
        iPublisher->PublishText( aWidgetId, _L8("text1"), KGFeed1 );                    
        /*
        iPublisher->PublishText( 
                    aWidgetId, _L8("text2"), KGFeed2 );
        iPublisher->PublishText( 
                    aWidgetId, _L8("text3"), KGFeed3 );
        iPublisher->PublishText( 
                    aWidgetId, _L8("text4"), KSFeed1 );
        */
        iPublisher->PublishText( 
                    aWidgetId, _L8("title1"), KGFeed1 );
        iPublisher->PublishText( 
                    aWidgetId, _L8("title2"), KGFeed2 );
        iPublisher->PublishText( 
                    aWidgetId, _L8("title4"), KGFeed3 );
        
        iPublisher->PublishText( 
                    aWidgetId, _L8("title3"), KSFeed1 );
        iPublisher->PublishText( 
                    aWidgetId, _L8("title5"), KSFeed2 );
        iPublisher->PublishText( 
                    aWidgetId, _L8("title6"), KSFeed3 );
                    
        
        iPublisher->PublishImage(aWidgetId,
            _L8("image1"), _L("c:\\data\\Installs\\rss_small.png"));
        iPublisher->PublishImage(aWidgetId,
            _L8("image2"), _L("c:\\data\\Installs\\rss_small.png"));
        iPublisher->PublishImage(aWidgetId,
            _L8("image3"), _L("c:\\data\\Installs\\rss_small.png"));

        iPublisher->CommitTransaction( aWidgetId );

        iFlags.Clear( ERequirePublish );
        }
    }

// End of File
