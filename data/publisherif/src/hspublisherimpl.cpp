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
#include <liwservicehandler.h>
#include <liwvariant.h>
#include <liwgenericparam.h>
#include <fbs.h>

// User includes
#include "transaction.h"
#include "hswidgetobserver.h"
#include "hspublisherimpl.h"  

// Constants
_LIT8( KCPSConfigurationIf, "IContentPublishing" );
_LIT8( KCPS, "Service.ContentPublishing" );

_LIT( KCpData, "cp_data" );

_LIT( KHsWidget, "hswidget" );
_LIT( KPublisher, "publisher" );
_LIT( KAll, "all" );

_LIT( KDataAndPublisher, "cp_data:publisher" );

_LIT8( KAdd, "add" );
_LIT8( KType, "type" );
_LIT8( KFilter, "filter" );
_LIT8( KFlag, "flag" );
_LIT8( KErrorCode, "ErrorCode" );
_LIT8( KDataMap, "data_map" );
_LIT8( KItem, "item" );
_LIT8( KDelete, "Delete" );
_LIT8( KPublisherId, "publisher" );
_LIT8( KContentType, "content_type" );
_LIT8( KContentId, "content_id" );
_LIT8( KOperation, "operation" );
_LIT8( KExecute, "execute" );
    
_LIT8( KRequestNotification, "RequestNotification" );
_LIT8( KChangeInfo, "change_info" );
_LIT8( KActionTrigger, "action_trigger" );

_LIT8( KActionMap, "action_map" );
_LIT8( KActive, "active" );

_LIT8( KSuspend, "suspend" );
_LIT8( KResume, "resume" );
_LIT8( KOnline, "online" );
_LIT8( KOffline, "offline" );

_LIT8( KSystemStartup, "systemstartup" );
_LIT8( KPageStartup, "pagestartup" );
_LIT8( KWidgetStartup, "pluginstartup" );

_LIT8( KSystemShutdown, "systemshutdown" );
_LIT8( KPageShutdown, "pageshutdown" );
_LIT8( KWidgetShutdown, "pluginshutdown" );

const TUint KDisablePersist( 0x1000 );

// Type definitions 
typedef TBuf< 256 > TVariantBuf;
typedef TBuf8< 256 > TVariantBuf8;


// ============================= LOCAL FUNCTIONS ===============================

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CHsPublisherImpl::NewLC()
// Two-phased constructor
// -----------------------------------------------------------------------------
//
CHsPublisherImpl* CHsPublisherImpl::NewLC( MHsWidgetObserver& aObserver, 
    TBool aEnablePersist )    
    {
    CHsPublisherImpl* self = new ( ELeave ) 
        CHsPublisherImpl( aObserver, aEnablePersist );
    
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;    
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::NewL()
// Two-phased constructor
// -----------------------------------------------------------------------------
//
CHsPublisherImpl* CHsPublisherImpl::NewL( MHsWidgetObserver& aObserver, 
    TBool aEnablePersist )   
    {
    CHsPublisherImpl* self = 
        CHsPublisherImpl::NewLC( aObserver, aEnablePersist );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::CHsPublisherImpl()
// C++ default constructor
// -----------------------------------------------------------------------------
//
CHsPublisherImpl::CHsPublisherImpl( MHsWidgetObserver& aObserver, 
    TBool aEnablePersist )
    : iObserver( aObserver ), 
      iEnablePersist( aEnablePersist )             
    {
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::ConstructL()
// 2nd phase constructor
// -----------------------------------------------------------------------------
//
void CHsPublisherImpl::ConstructL()
    {
    AttachL();
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::~CHsPublisherImpl()
// Destructor
// -----------------------------------------------------------------------------
//
CHsPublisherImpl::~CHsPublisherImpl()
    {
    iTransactions.ResetAndDestroy();
           
    TRAP_IGNORE( DetachL() );    
    }

// ---------------------------------------------------------------------------
// CHsPublisherImpl::AttachL
//
// ---------------------------------------------------------------------------
//
void CHsPublisherImpl::AttachL()
    {            
    // Attach to CPS service
    RCriteriaArray interestList;
    CleanupClosePushL( interestList );
           
    iServiceHandler = CLiwServiceHandler::NewL();
                    
    iCpsService = CLiwCriteriaItem::NewL( 1, KCPSConfigurationIf, KCPS ); 
                  
    iCpsService->SetServiceClass( TUid::Uid( KLiwClassBase ) );
    
    interestList.AppendL( iCpsService );
    iServiceHandler->AttachL( interestList );

    CLiwGenericParamList& inParamList( iServiceHandler->InParamListL() );
    CLiwGenericParamList& outParamList( iServiceHandler->OutParamListL() );
    
    iServiceHandler->ExecuteServiceCmdL(
          *iCpsService,
          inParamList,
          outParamList );
    
    TInt pos( 0 );
           
    outParamList.FindFirst( pos, KCPSConfigurationIf );
           
    if ( pos != KErrNotFound )
        {
        iCpsInterface = outParamList[pos].Value().AsInterface();                       
        }
    
    inParamList.Reset();
    outParamList.Reset();
    
    if ( !iCpsInterface )
        {
        User::Leave( KErrNotFound );
        }
        
    const TDesC& publisherId( iObserver.Identity() );
    
    // Register Observer       
    CLiwDefaultMap* reqmap = CLiwDefaultMap::NewLC();
        
    reqmap->InsertL( KPublisherId, TLiwVariant( publisherId  ) );
    reqmap->InsertL( KContentType, TLiwVariant( KAll ) );
    reqmap->InsertL( KContentId, TLiwVariant( KAll ) );
    reqmap->InsertL( KOperation, TLiwVariant( KExecute ) );

    inParamList.AppendL( TLiwGenericParam( 
        KType, TLiwVariant( KDataAndPublisher ) ) );        
        
    inParamList.AppendL( TLiwGenericParam( 
        KFilter, TLiwVariant( reqmap ) ) );
        
    iCpsInterface->ExecuteCmdL( 
        KRequestNotification, inParamList, outParamList, 0, this ); 

    const TLiwGenericParam* outparam( NULL );
    
    pos = 0;
    
    outparam = outParamList.FindFirst( pos, KErrorCode );
    
    TInt err( KErrNone );
    
    if ( outparam )
        {                     
        if ( outparam->Value().AsTInt32() )
            {
            err = KErrGeneral;
            }
        }

    inParamList.Reset();
    outParamList.Reset();
        
    User::LeaveIfError( err );            

    CleanupStack::PopAndDestroy( reqmap ); 
        
    // Register Publisher                           
    CLiwDefaultMap* datamap = CLiwDefaultMap::NewLC();
    CLiwDefaultMap* actionmap = CLiwDefaultMap::NewLC();
    
    datamap->InsertL( KPublisherId, TLiwVariant( publisherId ) );
    datamap->InsertL( KContentType, TLiwVariant( KAll ) );
    datamap->InsertL( KContentId, TLiwVariant( KAll ) );
            
    actionmap->InsertL( KActive, TLiwVariant() );
        
    datamap->InsertL( KActionMap, TLiwVariant( actionmap ) );

    inParamList.AppendL( TLiwGenericParam( 
        KType, TLiwVariant( KPublisher ) ) );       
        
    inParamList.AppendL( TLiwGenericParam( 
        KItem, TLiwVariant( datamap ) ) );
    
    iCpsInterface->ExecuteCmdL( KAdd, inParamList, outParamList );
        
    outparam = NULL;
    
    pos = 0;
           
    outparam = outParamList.FindFirst( pos, KErrorCode );
    
    err = KErrNone;
    
    if ( outparam )
        {
        if ( outparam->Value().AsTInt32() )
            {
            err = KErrGeneral;
            }
        }
                
    inParamList.Reset();
    outParamList.Reset();
    
    User::LeaveIfError( err );        
    
    CleanupStack::PopAndDestroy( 2, datamap ); // actionmap
                                            
    CleanupStack::PopAndDestroy( &interestList );
    
    iCpServiceAvailable = ETrue;       
    }

// ---------------------------------------------------------------------------
// CHsPublisherImpl::DetachL
//
// ---------------------------------------------------------------------------
//
void CHsPublisherImpl::DetachL()
    {     
    if ( iServiceHandler && iCpsInterface )
        {
        CLiwGenericParamList& inParamList( iServiceHandler->InParamListL() );
        CLiwGenericParamList& outParamList( iServiceHandler->OutParamListL() );
    
        // Remove widget data
        CLiwDefaultMap* cpdatamap = CLiwDefaultMap::NewLC();
        
        const TDesC& publisherId( iObserver.Identity() );
        
        cpdatamap->InsertL( KPublisherId, TLiwVariant( publisherId ) );
        cpdatamap->InsertL( KContentType, TLiwVariant( KAll ) );
        cpdatamap->InsertL( KContentId, TLiwVariant( KAll ) );
              
        inParamList.AppendL( TLiwGenericParam( 
            KType, TLiwVariant( KCpData ) ) );
        
        inParamList.AppendL( TLiwGenericParam( 
            KItem, TLiwVariant( cpdatamap ) ) );
        
        TRAP_IGNORE( iCpsInterface->ExecuteCmdL( 
            KDelete, inParamList, outParamList ) );
        
        inParamList.Reset();
        outParamList.Reset();
              
        CleanupStack::PopAndDestroy( cpdatamap );

        // Unregister Observer                 
        TRAP_IGNORE( iCpsInterface->ExecuteCmdL( 
                KRequestNotification,
                inParamList,
                outParamList,
                KLiwOptCancel,
                this ) );
        
        // Detach from CPS service
        if ( iCpsInterface )
           {
           // Close interface
           iCpsInterface->Close();
           }
        
        iCpsInterface = NULL;
        
        if ( iServiceHandler && iCpsService )
            {                   
            // Detach services from the handler       
            RCriteriaArray list;
                 
            list.Append( iCpsService );
           
            TRAP_IGNORE( iServiceHandler->DetachL( list ) );    
            
            list.Reset();
            }        
        }    
    
    delete iCpsService;
    iCpsService = NULL;
    
    delete iServiceHandler;
    iServiceHandler = NULL;                    
       
    iCpServiceAvailable = EFalse;
    }

// ---------------------------------------------------------------------------
// CHsPublisherImpl::HandleNotifyL
//
// ---------------------------------------------------------------------------
//
TInt CHsPublisherImpl::HandleNotifyL( TInt /*aCmdId*/, TInt /*aEventId*/,               
    CLiwGenericParamList& aEventParamList,
    const CLiwGenericParamList& /*aInParamList*/ )
    {           
    TInt pos( 0 );
       
    aEventParamList.FindFirst( pos, KChangeInfo );

    if ( pos == KErrNotFound )
        {        
        return pos;
        }
    
    const TDesC& publisherId( iObserver.Identity() );
    
    // Get list of maps
    TLiwVariant listvariant( aEventParamList[pos].Value() );
    listvariant.PushL();
    
    const CLiwList* list( listvariant.AsList() );
            
    // Iterate through list 
    for ( TInt i = 0; i < list->Count(); i++ )
        {
        TVariantBuf publisher;
        TVariantBuf contenttype;
        TVariantBuf widgetid;
        
        TVariantBuf8 operation;
        TVariantBuf8 trigger;
                
        TLiwVariant variant;
        variant.PushL();
        
        if ( list->AtL( i, variant ) ) 
            {
            const CLiwMap* map( variant.AsMap() ); 
        
            if( map->FindL( KPublisherId, variant ) )
                {
                variant.Get( publisher );
                }
                    
            if ( publisher != publisherId )
                {
                // Not targeted to this publisher
                continue;
                }
            
            // Check what triggered a notification
            if ( map->FindL( KOperation, variant ) )
                {
                variant.Get( operation );
                }
                                   
            if ( operation == KExecute() )
                {                 
                if ( map->FindL( KActionTrigger, variant ) )
                    {
                    variant.Get( trigger );
                    }
                
                if ( map->FindL( KContentId, variant ) )
                    {
                    variant.Get( widgetid );
                    }                               
                
                if ( map->FindL( KContentType, variant ) )
                    {
                    variant.Get( contenttype );
                    }
                
                if ( contenttype == KHsWidget() )
                    {
                    // HS specific notification    
                    ProcessEvent( widgetid, trigger );                    
                    }
                else
                    {
                    // Widget specific notification                    
                    HBufC* param = HBufC::NewLC( trigger.Length() );                                       
                    param->Des().Copy( trigger );
                    
                    iObserver.NotifyWidgetEvent( 
                        widgetid, contenttype, *param );
                    
                    CleanupStack::PopAndDestroy( param );
                    }                
                }                      
            
            CleanupStack::PopAndDestroy(); // variant
            }
        }                            
    
    CleanupStack::PopAndDestroy(); // listvariant       
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::ProcessEvent()
// 
// -----------------------------------------------------------------------------
//
void CHsPublisherImpl::ProcessEvent( const TDesC& aWidgetId, 
    const TDesC8& aEvent ) const
    {
    if ( aEvent == KResume() )
        {
        iObserver.NotifyWidgetState( 
            aWidgetId, MHsWidgetObserver::EAlive );
        }
    else if ( aEvent == KSuspend() )
        {
        iObserver.NotifyWidgetState( 
            aWidgetId, MHsWidgetObserver::ESuspend );
        }
    else if ( aEvent == KOnline() )
        {
        iObserver.NotifyWidgetState( 
            aWidgetId, MHsWidgetObserver::EOnline );
        }
    else if ( aEvent == KOffline() )
        {
        iObserver.NotifyWidgetState( 
            aWidgetId, MHsWidgetObserver::EOffline );
        }
    else if ( aEvent == KSystemStartup() )
        {
        iObserver.NotifyWidgetStarted( 
            aWidgetId, MHsWidgetObserver::ESystemStart );
        }
    else if ( aEvent == KPageStartup() )
        {
        iObserver.NotifyWidgetStarted( 
            aWidgetId, MHsWidgetObserver::EPageStart );    
        }
    else if ( aEvent == KWidgetStartup() )
        {
        iObserver.NotifyWidgetStarted( 
            aWidgetId, MHsWidgetObserver::EWidgetStart );    
        }
    else if ( aEvent == KSystemShutdown() )
        {
        iObserver.NotifyWidgetStopped( 
            aWidgetId, MHsWidgetObserver::ESystemStop );
        }
    else if ( aEvent == KPageShutdown() )
        {
        iObserver.NotifyWidgetStopped( 
            aWidgetId, MHsWidgetObserver::EPageStop );    
        }
    else if ( aEvent == KWidgetShutdown() )
        {
        iObserver.NotifyWidgetStopped( 
            aWidgetId, MHsWidgetObserver::EWidgetStop );    
        }
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::PublishTextL()
// 
// -----------------------------------------------------------------------------
//
void CHsPublisherImpl::PublishTextL( const TDesC& aWidgetId,         
    const TDesC8& aElementId, const TDesC& aText )
    {
    __ASSERT_ALWAYS( iCpServiceAvailable, User::Invariant() );
    
    CTransaction* tr( Transaction( aWidgetId ) );
    
    if ( !tr )
        {
        // Transaction not started 
        User::Leave( KErrNotReady );
        }
    
    CTextTransactionItem* item = 
        new ( ELeave ) CTextTransactionItem( aElementId, aText ); 

    CleanupStack::PushL( item );
     
    tr->AppendL( item );
    CleanupStack::Pop( item );      
    }
  
// -----------------------------------------------------------------------------
// CHsPublisherImpl::PublishImageL()
// 
// -----------------------------------------------------------------------------
//
void CHsPublisherImpl::PublishImageL( const TDesC& aWidgetId,      
    const TDesC8& aElementId, const CFbsBitmap* aImage, const CFbsBitmap* aMask )
    {
    __ASSERT_ALWAYS( iCpServiceAvailable, User::Invariant() );
    
    TInt imageHandle( KErrBadHandle );
    TInt maskHandle( KErrBadHandle );
    
    if ( aImage )
        {
        imageHandle = aImage->Handle();
        }
    
    if ( aMask )
        {
        maskHandle = aMask->Handle();
        }
    
    PublishImageL( aWidgetId, aElementId, imageHandle, maskHandle );
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::PublishImageL()
// 
// -----------------------------------------------------------------------------
//
void CHsPublisherImpl::PublishImageL( const TDesC& aWidgetId,      
    const TDesC8& aElementId, TInt aImageHandle, TInt aMaskHandle )
    {
    __ASSERT_ALWAYS( iCpServiceAvailable, User::Invariant() );
    
    CTransaction* tr( Transaction( aWidgetId ) );
    
    if ( !tr )
        {
        // Transaction not started 
        User::Leave( KErrNotReady );
        }
    
    CImageTransactionItem* item = 
        new ( ELeave ) CImageTransactionItem( 
            aElementId, aImageHandle, aMaskHandle );
    
    CleanupStack::PushL( item );
    
    tr->AppendL( item );
    CleanupStack::Pop( item );        
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::PublishImageL()
// 
// -----------------------------------------------------------------------------
//
void CHsPublisherImpl::PublishImageL( const TDesC& aWidgetId,           
    const TDesC8& aElementId, const TDesC& aSource )
    {
    __ASSERT_ALWAYS( iCpServiceAvailable, User::Invariant() );
    
    CTransaction* tr( Transaction( aWidgetId ) );
    
    if ( !tr )
        {
        // Transaction not started 
        User::Leave( KErrNotReady );
        }
    
    CImageTransactionItem* item = 
        new ( ELeave ) CImageTransactionItem( aElementId, aSource );
    CleanupStack::PushL( item );
    
    tr->AppendL( item );
    CleanupStack::Pop( item );    
    }
    
// -----------------------------------------------------------------------------
// CHsPublisherImpl::PublishStreamL()
// 
// -----------------------------------------------------------------------------
//
void CHsPublisherImpl::PublishStreamL( const TDesC& aWidgetId,    
    const TDesC8& aElementId, const TDesC8& aStream )
    {
    CTransaction* tr( Transaction( aWidgetId ) );
    
    if ( !tr )
        {
        // Transaction not started 
        User::Leave( KErrNotReady );
        }
    
    CDataTransactionItem* item = 
        new ( ELeave ) CDataTransactionItem( aElementId, aStream );
    CleanupStack::PushL( item );
    
    tr->AppendL( item );
    CleanupStack::Pop( item );        
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::CleanTextL()
// 
// -----------------------------------------------------------------------------
//
void CHsPublisherImpl::CleanTextL( const TDesC& aWidgetId,    
    const TDesC8& aElementId )
    {
    CTransaction* tr( Transaction( aWidgetId ) );
    
    if ( !tr )
        {
        // Transaction not started 
        User::Leave( KErrNotReady );
        }
    
    CTextTransactionItem* item = 
        new ( ELeave ) CTextTransactionItem( aElementId, KNullDesC() ); 
    CleanupStack::PushL( item );
     
    tr->AppendL( item );
    CleanupStack::Pop( item );          
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::CleanImageL()
// 
// -----------------------------------------------------------------------------
//
void CHsPublisherImpl::CleanImageL( const TDesC& aWidgetId,    
    const TDesC8& aElementId )
    {
    CTransaction* tr( Transaction( aWidgetId ) );
    
    if ( !tr )
        {
        // Transaction not started 
        User::Leave( KErrNotReady );
        }
    
    CImageTransactionItem* item = 
        new ( ELeave ) CImageTransactionItem( 
            aElementId, KErrBadHandle, KErrBadHandle );    
    CleanupStack::PushL( item );
    
    tr->AppendL( item );
    CleanupStack::Pop( item );            
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::StartTransactionL()
// 
// -----------------------------------------------------------------------------
//
void CHsPublisherImpl::StartTransactionL( const TDesC& aWidgetId )
    {
    __ASSERT_ALWAYS( iCpServiceAvailable, User::Invariant() );
        
    CTransaction* tr( Transaction( aWidgetId ) );
    
    if ( tr )
        {
        // Transaction already started
        User::Leave( KErrAlreadyExists );    
        }
    
    // Create new transaction for this widget instance
    tr = new ( ELeave ) CTransaction( aWidgetId );
    CleanupStack::PushL( tr );
    
    iTransactions.AppendL( tr );
    CleanupStack::Pop( tr );
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::CommitTransactionL()
// 
// -----------------------------------------------------------------------------
//
void CHsPublisherImpl::CommitTransactionL( const TDesC& aWidgetId )
    {
    __ASSERT_ALWAYS( iCpServiceAvailable, User::Invariant() );

    CTransaction* tr( Transaction( aWidgetId ) );
    
    if ( !tr )
        {
        // Transaction not started 
        User::Leave( KErrNotReady );
        }
    
    // Remove transaction
    iTransactions.Remove( iTransactions.Find( tr ) );
    
    // Transaction will be destroyed
    CleanupStack::PushL( tr );
    
    const RPointerArray< CTransactionItem >& items( tr->Items() );
    
    if ( items.Count() == 0 )
        {
        // Nothing to publish   
        CleanupStack::PopAndDestroy( tr );    
        return;
        }
    
    CLiwGenericParamList& inParamList( iServiceHandler->InParamListL() );
    CLiwGenericParamList& outParamList( iServiceHandler->OutParamListL() );

    inParamList.AppendL( TLiwGenericParam(  
        KType, TLiwVariant( KCpData ) ) );
    
    CLiwDefaultMap* cpdatamap = CLiwDefaultMap::NewLC();

    const TDesC& publisherId( iObserver.Identity() );
    
    cpdatamap->InsertL( KPublisherId, TLiwVariant( publisherId ) );
    cpdatamap->InsertL( KContentType, TLiwVariant( KAll ) );
    cpdatamap->InsertL( KContentId, TLiwVariant( aWidgetId ) );
       
    CLiwDefaultMap* datamap = CLiwDefaultMap::NewLC();
             
    for ( TInt i = 0; i < items.Count(); i++ )
        {
        CTransactionItem* item( items[i] );
        
        CImageTransactionItem* image = 
            dynamic_cast< CImageTransactionItem* >( item );
        
        CTextTransactionItem* text =
            dynamic_cast< CTextTransactionItem* >( item );
        
        CDataTransactionItem* data =
            dynamic_cast< CDataTransactionItem* >( item );
        
        if ( image )
            {
            const TDesC& source( image->Path() );
            
            if ( source != KNullDesC )
                {
                datamap->InsertL( image->ElementId(), 
                    TLiwVariant( source ) );                      
                }
            else
                {
                datamap->InsertL( image->ElementId(),  
                    TLiwVariant( TInt32( image->ImageHandle() ) ) );
                
                datamap->InsertL( image->ElementId(),  
                    TLiwVariant( TInt32( image->MaskHandle() ) ) );                
                }                        
            }
        else if ( text )
            {                                                        
            datamap->InsertL( text->ElementId(), 
                TLiwVariant( text->Text() ) );                
            }
        else if ( data )
            {
            datamap->InsertL( data->ElementId(), 
                TLiwVariant( data->Data() ) );                        
            }
        }   
    
    cpdatamap->InsertL( KDataMap, TLiwVariant( datamap ) );
                      
    inParamList.AppendL( TLiwGenericParam(  
        KItem, TLiwVariant( cpdatamap ) ) );
    
    iCpsInterface->ExecuteCmdL( KAdd, inParamList, outParamList,           
        iEnablePersist ? 0 : KDisablePersist );
          
    inParamList.Reset();
    outParamList.Reset();
    
    CleanupStack::PopAndDestroy( 3, tr ); // cpdatamap, datamap
    }

// -----------------------------------------------------------------------------
// CHsPublisherImpl::Transaction()
// 
// -----------------------------------------------------------------------------
//
CTransaction* CHsPublisherImpl::Transaction( 
    const TDesC& aWidgetId ) const
    {
    CTransaction* tr( NULL );
    
    for ( TInt i = 0; i < iTransactions.Count(); i++ )
        {
        if ( *iTransactions[i] == aWidgetId )
            {   
            tr = iTransactions[i];
            break;
            }
        }
    
    return tr;
    }

// End of file
