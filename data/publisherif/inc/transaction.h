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


#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

// System includes 
#include <e32base.h>

// User includes

// Forward declarations

// Constants

// CTransactionItem Class declaration
NONSHARABLE_CLASS( CTransactionItem ) : public CBase
    {
public:
    // constrcutor and destructor

    /**
     * C++ constructor
     */
    CTransactionItem( const TDesC8& aElementId );        
    
    /**
     * Destructor
     */
    ~CTransactionItem();

public:
    // new functions
    
    /**
     * Returns this transaction's element id.
     * 
     * @return Transaction element id.
     */
    const TDesC8& ElementId() const;
    
    /**
     * Returns this transaction's content type.
     * To be overriden by sub-classes.
     * 
     * @return Transaction element type. 
     */
    virtual const TDesC8& Type() const = 0;
    
protected:
    // data
    
    /** Transaction's element id, owned */
    HBufC8* iElementId;
    };

// CImageTransactionItem Class declaration
NONSHARABLE_CLASS( CImageTransactionItem ) : public CTransactionItem
    {
public:
    // constructors and destructor

    /**
     * C++ constructor
     */
    CImageTransactionItem( 
        const TDesC8& aElementId, 
        TInt aImageHandle, 
        TInt aMaskHandle );
    
    /**
     * C++ constructor
     */    
    CImageTransactionItem( 
        const TDesC8& aElementId, 
        const TDesC& aPath );
    
    /**
     * Destructor
     */    
    ~CImageTransactionItem();
    
public:
    // from CTransactionItem
    
    /**
     * @see CTransactionItem
     */
    const TDesC8& Type() const;
    
public:
    // new functions
    
    /** 
     * Gets transaction's image handle.
     * Notice that path and handles are mutually exclusice in one transaction.
     * 
     * @return Image handle
     */
    TInt ImageHandle() const;

    /** 
     * Gets transaction's mask handle.
     * Notice that path and handles are mutually exclusice in one transaction.
     * 
     * @return Mask handle
     */    
    TInt MaskHandle() const;

    /** 
     * Gets transaction's path. 
     * Notice that path and handles are mutually exclusice in one transaction.
     * 
     * @return Path
     */        
    const TDesC& Path() const;
    
private:
    // data
            
    /** Transaction's data, caller must maintain the bitmap alive */
    TInt iImageHandle;
    /** Transaction's data, caller must maintain the bitmap alive */
    TInt iMaskHandle;
    /** Transaction's data, owned */
    HBufC* iPath;
    };

// CTextTransactionItem Class declaration
NONSHARABLE_CLASS( CTextTransactionItem ) : public CTransactionItem 
    {
public:    
    // constructors and destructor

    /**
     * C++ constructor
     */
    CTextTransactionItem( 
        const TDesC8& aElementId, 
        const TDesC& aText );
    
    /**
     * Destructor
     */        
    ~CTextTransactionItem();
    
public:
    // from CTransactionItem

    /**
     * @see CTransactionItem
     */
    const TDesC8& Type() const;

public:
    // new functions
    
    /**
     * Gets transaction's text
     * 
     * @return Text
     */
    const TDesC& Text() const;
    
private:
    // data
    
    /** Transaction's data, owned */
    HBufC* iText;
    };

// CDataTransactionItem Class declaration
NONSHARABLE_CLASS( CDataTransactionItem ) : public CTransactionItem 
    {
public:    
    // constructors and destructor

    /**
     * C++ constructor
     */
    CDataTransactionItem( 
        const TDesC8& aElementId, 
        const TDesC8& aData );
    
    /**
     * Destructor
     */        
    ~CDataTransactionItem();
    
public:
    // from CTransactionItem

    /**
     * @see CTransactionItem
     */
    const TDesC8& Type() const;

public:
    // new functions
    
    /**
     * Gets transaction's data
     * 
     * @return Data
     */
    const TDesC8& Data() const;
    
private:
    // data
    
    /** Transaction's data, owned */
    HBufC8* iData;
    };


// CTransaction Class declaration
NONSHARABLE_CLASS( CTransaction ) : public CBase
    {
public:
    // constructors and destructor

    /**
     * C++ constructor
     */
    CTransaction( 
        const TDesC& aWidgetId ); 
    
    /**
     * Destructor
     */            
    ~CTransaction();

public:
    // new functions
    
    /**
     * Equals operator
     * 
     * @param aWidgetId Widget id to use in comparision
     * @return ETrue if this transaction matches to aWidgetId, EFalse otherwise
     */
    TBool operator== ( const TDesC& aWidgetId ) const;

    /**
     * Appends transaction item to transaction items array.
     * 
     * @param aItem Transaction item. This transaction takes item's ownership.
     */
    void AppendL( CTransactionItem* aItem );

    /**
     * Gets transaction items from this transaction.
     * 
     * @return Transaction items. 
     */    
    const RPointerArray< CTransactionItem >& Items() const;
    
private:    
    // data
    
    /** Transaction items, owned */
    mutable RPointerArray< CTransactionItem > iItems;
    /** Transaction's id, same as widget id */
    const TDesC& iWidgetId;    
    };

#endif // __TRANSACTION_H__

// End of file
