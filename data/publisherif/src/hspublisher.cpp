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

// System includes  

// User includes
#include "hspublisherimpl.h"
#include "hspublisher.h"	

// Constants


// ============================= LOCAL FUNCTIONS ===============================

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CHsPublisher::NewLC()
// Two-phased constructor
// -----------------------------------------------------------------------------
//
CHsPublisher* CHsPublisher::NewLC( MHsWidgetObserver& aObserver, 
    TBool aEnablePersist )
    {
    CHsPublisher* self = new ( ELeave ) CHsPublisher();
    CleanupStack::PushL( self );
    self->ConstructL( aObserver, aEnablePersist );
    return self;
    }

// -----------------------------------------------------------------------------
// CHsPublisher::NewL()
// Two-phased constructor
// -----------------------------------------------------------------------------
//
CHsPublisher* CHsPublisher::NewL( MHsWidgetObserver& aObserver,    
    TBool aEnablePersist )    
    {
    CHsPublisher* self = CHsPublisher::NewLC( aObserver, aEnablePersist );         
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHsPublisher::CHsPublisher()
// C++ default constructor
// -----------------------------------------------------------------------------
//
CHsPublisher::CHsPublisher()    
    {
    }

// -----------------------------------------------------------------------------
// CHsPublisher::ConstructL()
// 2nd phase constructor
// -----------------------------------------------------------------------------
//
void CHsPublisher::ConstructL( MHsWidgetObserver& aObserver,
    TBool aEnablePersist )
    {
    iImpl = CHsPublisherImpl::NewL( aObserver, aEnablePersist );         
    }

// -----------------------------------------------------------------------------
// CHsPublisher::~CHsPublisher()
// Destructor
// -----------------------------------------------------------------------------
//
CHsPublisher::~CHsPublisher()
    {
    delete iImpl;    
    }

// -----------------------------------------------------------------------------
// CHsPublisher::PublishText()
// 
// -----------------------------------------------------------------------------
//
TInt CHsPublisher::PublishText( const TDesC& aWidgetId,         
    const TDesC8& aElementId, const TDesC& aText )
    {
    TRAPD( err, iImpl->PublishTextL( aWidgetId, aElementId, aText ) );
    
    return err;    
    }
  
// -----------------------------------------------------------------------------
// CHsPublisher::PublishImage()
// 
// -----------------------------------------------------------------------------
//
TInt CHsPublisher::PublishImage( const TDesC& aWidgetId,      
    const TDesC8& aElementId, const CFbsBitmap* aImage, const CFbsBitmap* aMask )
    {
    TRAPD( err, iImpl->PublishImageL( aWidgetId, aElementId, aImage, aMask ) );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CHsPublisher::PublishImage()
// 
// -----------------------------------------------------------------------------
//
TInt CHsPublisher::PublishImage( const TDesC& aWidgetId,      
    const TDesC8& aElementId, TInt aImageHandle, TInt aMaskHandle )
    {
    TRAPD( err, iImpl->PublishImageL( 
        aWidgetId, aElementId, aImageHandle, aMaskHandle ) );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CHsPublisher::PublishImage()
// 
// -----------------------------------------------------------------------------
//
TInt CHsPublisher::PublishImage( const TDesC& aWidgetId,           
    const TDesC8& aElementId, const TDesC& aSource )
    {
    TRAPD( err, iImpl->PublishImageL( aWidgetId, aElementId, aSource ) );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CHsPublisher::PublishStream()
// 
// -----------------------------------------------------------------------------
//
TInt CHsPublisher::PublishStream( const TDesC& aWidgetId,    
    const TDesC8& aElementId, const TDesC8& aStream )
    {
    TRAPD( err, iImpl->PublishStreamL( aWidgetId, aElementId, aStream ) ); 
            
    return err;
    }

// -----------------------------------------------------------------------------
// CHsPublisher::CleanText()
// 
// -----------------------------------------------------------------------------
//
TInt CHsPublisher::CleanText( const TDesC& aWidgetId, 
    const TDesC8& aElementId )        
    {
    TRAPD( err, iImpl->CleanTextL( aWidgetId, aElementId ) );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CHsPublisher::CleanImage()
// 
// -----------------------------------------------------------------------------
//
TInt CHsPublisher::CleanImage( const TDesC& aWidgetId, 
    const TDesC8& aElementId )        
    {
    TRAPD( err, iImpl->CleanImageL( aWidgetId, aElementId ) );
    
    return err;    
    }

// -----------------------------------------------------------------------------
// CHsPublisher::StartTransaction()
// 
// -----------------------------------------------------------------------------
//
TInt CHsPublisher::StartTransaction( const TDesC& aWidgetId )
    {
    TRAPD( err, iImpl->StartTransactionL( aWidgetId ) );
    
    return err;
    }

// -----------------------------------------------------------------------------
// CHsPublisher::CommitTransaction()
// 
// -----------------------------------------------------------------------------
//
TInt CHsPublisher::CommitTransaction( const TDesC& aWidgetId )
    {
    TRAPD( err, iImpl->CommitTransactionL( aWidgetId ) );
    
    return err;
    }

// End of file
