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


#ifndef __HSPUBLISHERIMPL_H__
#define __HSPUBLISHERIMPL_H__

// System includes 
#include <e32base.h>    
#include <liwcommon.h>

// User includes

// Forward declarations
class MHsWidgetObserver;
class CLiwServiceHandler;
class CLiwCriteriaItem;
class CLiwGenericParamList;
class MLiwInterface;
class CFbsBitmap;
class CTransaction;

// Constants

// Class declaration
NONSHARABLE_CLASS( CHsPublisherImpl ) : public CBase,
    public MLiwNotifyCallback
    {
public:
    // constructors and destructor

    /**
     * Constructor
     * 
     * @param aObserver Widget observer interface.
     * @param aEnablePersist ETrue if publisher wants to save published data to SQL database for later usage.
     *        This option should be used with caution as it taxes runtime performance and resources.       
     */
    static CHsPublisherImpl* NewL( 
        MHsWidgetObserver& aObserver,        
        TBool aEnablePersist );
            
    /**
     * Constructor
     * 
     * @param aObserver Widget observer interface.
     * @param aEnablePersist ETrue if publisher wants to save published data to SQL database for later usage.
     *        This option should be used with caution as it taxes runtime performance and resources.           
     */
    static CHsPublisherImpl* NewLC( 
        MHsWidgetObserver& aObserver,        
        TBool aEnablePersist );
        
    /**
     * Destructor
     */
    ~CHsPublisherImpl();

private:
    // from MLiwNotifyCallback
    
    /**
    * Handles notifications caused by an asynchronous Execute*CmdL call
    * or an event.
    *
    * @param aCmdId The service command associated to the event.
    * @param aEventId Occured event, see LiwCommon.hrh.
    * @param aEventParamList Event parameters, if any, as defined per
    *        each event.
    * @param aInParamList Input parameters, if any, given in the
    *        related HandleCommmandL.
    * @return Error code for the callback.
    */
    TInt HandleNotifyL( TInt aCmdId, TInt aEventId,               
        CLiwGenericParamList& aEventParamList,
        const CLiwGenericParamList& aInParamList );
    
public:
    // new functions
           
    /**
     * Publishes text to a <text> element in the widget.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the text element in the widget.
     * @param aText Text to set.          
     */
    void PublishTextL( 
        const TDesC& aWidgetId, 
        const TDesC8& aElementId, 
        const TDesC& aText );

    /**
     * Publishes image to an <image> element in the widget.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the image element in the widget.
     * @param aImage Image to set.
     * @param aMask Mask to set.          
     */    
    void PublishImageL( 
        const TDesC& aWidgetId, 
        const TDesC8& aElementId,
        const CFbsBitmap* aImage,
        const CFbsBitmap* aMask );

    /**
     * Publishes image to an <image> element in the widget.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the image element in the widget.
     * @param aImageHandle Handle to Image to set.     
     * @param aMaskHandle Handle to mask to set.
     */        
    void PublishImageL( 
        const TDesC& aWidgetId,      
        const TDesC8& aElementId, 
        TInt aImageHandle, 
        TInt aMaskHandle );

    /**
     * Publishes image to an <image> element in the widget.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the image element in the widget.
     * @param aSource Source for the image. Supported source formats are:
     * - Filesystem path, i.e. _LIT( KMyImagePath, "c:\\data\\Installs\\MyWidget\\image.jpg");
     * - skin(<majorId> <minorId>), i.e. _LIT( KMySkinImage, "skin(270501603 8586)" );
     * - mif(<MifFileName.mif> <bitmapId> <maskId>), i.e. _LIT( KMyMifImage, "mif(c:\\data\\Installs\\MyWidget\\mymwidget.mif 16384 16385" );
     */            
    void PublishImageL( 
        const TDesC& aWidgetId,      
        const TDesC8& aElementId,
        const TDesC& aSource );
       
    /**
     * Publishes stream to a <data> element in widget.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the data element in the widget.
     * @param aStream The stream as descriptor.              
     */                
    void PublishStreamL( 
        const TDesC& aWidgetId,    
        const TDesC8& aElementId, 
        const TDesC8& aStream );
    
    /**
     * Cleans published text from a <text> element.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the data element in the widget.     
     */
    void CleanTextL( const TDesC& aWidgetId,    
        const TDesC8& aElementId );

    /**
     * Cleans published image from an <image> element.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the data element in the widget.     
     */    
    void CleanImageL( const TDesC& aWidgetId,    
        const TDesC8& aElementId );
    
    /**
     * Starts a publish transaction. Transaction must be committed  
     * with CommitTransaction method.
     * 
     * @param aWidget Widget Id identifying the transaction for widget instance.
     * @return System wide error code.
     */                    
    void StartTransactionL( 
        const TDesC& aWidgetId );
    
    /**
     * Commits the publish transaction and flushes changes to Homescreen.
     * 
     * @param aWidget Widget Id identifying the transaction for the widget instance.     
     */                
    void CommitTransactionL( 
        const TDesC& aWidgetId );
        
private:
    // new functions
    
    /** 
     * Attaches to CPS service.
     */
    void AttachL();
    
    /**
     * Detaches from CPS servive.
     */
    void DetachL();
        
    /**
     * Process CPS notification and delegates it to MHsWidgetObserver.
     * 
     * @param aWidgetId The widget instance from the event was initiated.
     * @param aEvent Event which maps to Content Model.
     */
    void ProcessEvent( 
        const TDesC& aWidgetId, 
        const TDesC8& aEvent ) const;    
    
    /**
     * Gets transaction for aWidgetId.
     * 
     * @param aWidgetId The widget instance to use in transaction look-up.
     * @return Transaction, NULL if not found.
     */
    CTransaction* Transaction( const TDesC& aWidgetId ) const;
    
private:
    // private constructors
    
    /**
     * C++ constructor
     */
    CHsPublisherImpl( 
        MHsWidgetObserver& aObserver,        
        TBool aEnablePersist );
    
    /**
     * 2nd phase constructor
     */
    void ConstructL();

private:
    // data
    
    /** HS Widget observer, not owned */
    MHsWidgetObserver& iObserver;        
    /** SAPI service handler, owned */
    CLiwServiceHandler* iServiceHandler;    
    /** CPS SAPI service, owned */
    CLiwCriteriaItem* iCpsService;    
    /** Cps interface, owned */
    MLiwInterface* iCpsInterface;
    /** Publish transactions, owned */
    RPointerArray< CTransaction > iTransactions;
    /** Attached succesfully to CPS service */
    TBool iCpServiceAvailable;
    /** Flag Enable persist */
    TBool iEnablePersist;
    };

#endif // __HSPUBLISHERIMPL_H__

// End of file
