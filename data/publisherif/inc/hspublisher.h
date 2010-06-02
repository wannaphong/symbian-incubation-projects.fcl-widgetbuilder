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


#ifndef __HSPUBLISHER_H__
#define __HSPUBLISHER_H__

//  System includes 
#include <e32base.h>	
#include <fbs.h>

// User includes

// Forward declarations
class CHsPublisherImpl;
class MHsWidgetObserver;

//  Constants

//  Class Definitions
NONSHARABLE_CLASS( CHsPublisher ) : public CBase
    {
public:
    // constructors and destructor

    /**
     * Constructor
     * 
     * @param aObserver Widget observer interface
     * @param aEnablePersist ETrue if publisher wants to save published data to SQL database for later usage.
     *        This option should be used with caution as it taxes runtime performance and resources.               
     */
    static CHsPublisher* NewL( 
        MHsWidgetObserver& aObserver, 
        TBool aEnablePersist = EFalse );
    
    /**
     * Constructor
     * 
     * @param aObserver Widget observer interface
     * @param aEnablePersist ETrue if publisher wants to save published data to SQL database for later usage.
     *        This option should be used with caution as it taxes runtime performance and resources.                
     */
    static CHsPublisher* NewLC(            
        MHsWidgetObserver& aObserver,
        TBool aEnablePersist = EFalse );
        
    /**
     * Destructor
     */
    ~CHsPublisher();

public:
    // new functions
    
    /**
     * Publishes text to a <text> element in widget
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the text element in the widget.
     * @param aText Text to set.     
     * @return System wide error code.
     */
    TInt PublishText( 
        const TDesC& aWidgetId, 
        const TDesC8& aElementId, 
        const TDesC& aText );

    /**
     * Publishes image to an <image> element in widget
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the iamge element in the widget.
     * @param aImage Image to set.
     * @param aMask Mask to set. 
     * @return System wide error code.
     */    
    TInt PublishImage( 
        const TDesC& aWidgetId, 
        const TDesC8& aElementId,
        const CFbsBitmap* aImage,
        const CFbsBitmap* aMask );

    /**
     * Publishes image to an <image> element in widget
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the image element in the widget.
     * @param aImageHandle Image handle.
     * @param aMaskHandle Mask handle.
     * @return System wide error code.
     */        
    TInt PublishImage( 
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
    TInt PublishImage( 
        const TDesC& aWidgetId,           
        const TDesC8& aElementId, 
        const TDesC& aSource );
    
    /**
     * Publishes stream to a <data> element in widget
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the data element in the widget.
     * @param aStream The stream as descriptor.         
     * @return System wide error code.
     */            
    TInt PublishStream(
        const TDesC& aWidgetId,
        const TDesC8& aElementId,
        const TDesC8& aStream );

    /**
     * Cleans published text from a <text> element.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the data element in the widget.
     * @return System wide error code.     
     */
    TInt CleanText( const TDesC& aWidgetId,    
        const TDesC8& aElementId );

    /**
     * Cleans published image from an <image> element.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aElementId Element id identifying the data element in the widget.
     * @return System wide error code.     
     */    
    TInt CleanImage( const TDesC& aWidgetId,    
        const TDesC8& aElementId );
    
    /**
     * Starts a publish transaction. Transaction must be committed  
     * with CommitTransaction method.
     * 
     * @param aWidget Widget Id identifying the transaction for widget instance.
     * @return System wide error code.
     */                
    TInt StartTransaction( 
        const TDesC& aWidgetId );
    
    /**
     * Commits the publish transaction and flushes changes to Homescreen.
     * 
     * @param aWidget Widget Id identifying the transaction for the widget instance.
     * @return System wide error code.
     */            
    TInt CommitTransaction( 
        const TDesC& aWidgetId );    
       
private:
    // private constructors
    
    /**
     * C++ default constructor
     */
    CHsPublisher();
    
    /**
     * 2nd phase constructor
     */
    void ConstructL( 
        MHsWidgetObserver& aObserver,
        TBool aEnablePersist );
    
private:
    // data
        
    /** HS publisher implementation, owned */
    CHsPublisherImpl* iImpl;
    };

#endif  // __HSPUBLISHER_H__

// End of file
