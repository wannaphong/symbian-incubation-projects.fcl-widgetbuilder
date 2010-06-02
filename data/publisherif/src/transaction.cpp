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
#include "transaction.h"

// Constants

// ============================= LOCAL FUNCTIONS ===============================

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTransactionItem::CTransactionItem()
// C++ default constructor
// -----------------------------------------------------------------------------
//
CTransactionItem::CTransactionItem( const TDesC8& aElementId )
    : iElementId( aElementId.Alloc() )
    {    
    }

// -----------------------------------------------------------------------------
// CTransactionItem::~CTransactionItem()
// Destructor
// -----------------------------------------------------------------------------
//
CTransactionItem::~CTransactionItem()
    {    
    delete iElementId;
    }

// -----------------------------------------------------------------------------
// CTransactionItem::ElementId()
// 
// -----------------------------------------------------------------------------
//
const TDesC8& CTransactionItem::ElementId() const
    {
    return iElementId ? *iElementId : KNullDesC8();
    }

// -----------------------------------------------------------------------------
// CImageTransactionItem::CImageTransactionItem
// C++ default constructor
// -----------------------------------------------------------------------------
//
CImageTransactionItem::CImageTransactionItem( const TDesC8& aElementId, 
    TInt aImageHandle, TInt aMaskHandle )
    : CTransactionItem( aElementId ), 
      iImageHandle( aImageHandle ), 
      iMaskHandle( aMaskHandle ), 
      iPath( NULL )
    {    
    }

// -----------------------------------------------------------------------------
// CImageTransactionItem::CImageTransactionItem
// C++ default constructor
// -----------------------------------------------------------------------------
//
CImageTransactionItem::CImageTransactionItem( const TDesC8& aElementId, 
    const TDesC& aPath )
    : CTransactionItem( aElementId ), 
      iImageHandle( KErrBadHandle ), 
      iMaskHandle( KErrBadHandle ), 
      iPath( aPath.Alloc() )
    {   
    }

// -----------------------------------------------------------------------------
// CImageTransactionItem::~CImageTransactionItem()
// Destructor
// -----------------------------------------------------------------------------
//
CImageTransactionItem::~CImageTransactionItem()
    {    
    delete iPath;
    }

// -----------------------------------------------------------------------------
// CImageTransactionItem::Type()
// 
// -----------------------------------------------------------------------------
//
const TDesC8& CImageTransactionItem::Type() const
    {
    _LIT8( KImage, "image" );
    
    return KImage();    
    }

// -----------------------------------------------------------------------------
// CImageTransactionItem::ImageHandle()
// 
// -----------------------------------------------------------------------------
//
TInt CImageTransactionItem::ImageHandle() const
    {
    return iImageHandle;
    }

// -----------------------------------------------------------------------------
// CImageTransactionItem::MaskHandle()
// 
// -----------------------------------------------------------------------------
//
TInt CImageTransactionItem::MaskHandle() const
    {
    return iMaskHandle;
    }

// -----------------------------------------------------------------------------
// CImageTransactionItem::Path()
// 
// -----------------------------------------------------------------------------
//
const TDesC& CImageTransactionItem::Path() const
    {
    return iPath ? *iPath : KNullDesC();
    }

// -----------------------------------------------------------------------------
// CTextTransactionItem::CTextTransactionItem()
// C++ default constructor
// -----------------------------------------------------------------------------
//
CTextTransactionItem::CTextTransactionItem( const TDesC8& aElementId, 
    const TDesC& aText )
    : CTransactionItem( aElementId ),
      iText( aText.Alloc() )
    {    
    }

// -----------------------------------------------------------------------------
// CTextTransactionItem::~CTextTransactionItem()
// Destructor
// -----------------------------------------------------------------------------
//
CTextTransactionItem::~CTextTransactionItem()
    {    
    delete iText;
    }

// -----------------------------------------------------------------------------
// CTextTransactionItem::Type()
// 
// -----------------------------------------------------------------------------
//
const TDesC8& CTextTransactionItem::Type() const
    {
    _LIT8( KText, "text" );
    
    return KText();
    }

// -----------------------------------------------------------------------------
// CTextTransactionItem::Text()
// 
// -----------------------------------------------------------------------------
//
const TDesC& CTextTransactionItem::Text() const
    {
    return iText ? *iText : KNullDesC();
    }


// -----------------------------------------------------------------------------
// CDataTransactionItem::CDataTransactionItem()
// C++ default constructor
// -----------------------------------------------------------------------------
//
CDataTransactionItem::CDataTransactionItem( const TDesC8& aElementId, 
    const TDesC8& aData )
    : CTransactionItem( aElementId ),
      iData( aData.Alloc() )
    {    
    }

// -----------------------------------------------------------------------------
// CDataTransactionItem::~CDataTransactionItem()
// Destructor
// -----------------------------------------------------------------------------
//
CDataTransactionItem::~CDataTransactionItem()
    {    
    delete iData;
    }

// -----------------------------------------------------------------------------
// CDataTransactionItem::Type()
// 
// -----------------------------------------------------------------------------
//
const TDesC8& CDataTransactionItem::Type() const
    {
    _LIT8( KData, "data" );
    
    return KData();
    }

// -----------------------------------------------------------------------------
// CDataTransactionItem::Data()
// 
// -----------------------------------------------------------------------------
//
const TDesC8& CDataTransactionItem::Data() const
    {
    return iData ? *iData : KNullDesC8();
    }

// -----------------------------------------------------------------------------
// CTransaction::CTransaction()
// C++ default constructor
// -----------------------------------------------------------------------------
//
CTransaction::CTransaction( const TDesC& aWidgetId ) 
    : iWidgetId( aWidgetId )
    {            
    }

// -----------------------------------------------------------------------------
// CTransaction::~CTransaction()
// Destructor
// -----------------------------------------------------------------------------
//
CTransaction::~CTransaction()
    {
    iItems.ResetAndDestroy();
    }

// -----------------------------------------------------------------------------
// CTransaction::operator==()
//
// -----------------------------------------------------------------------------
//
TBool CTransaction::operator== ( const TDesC& aWidgetId ) const
    {
    if ( iWidgetId == KNullDesC )
        {
        return EFalse;
        }
    
    return aWidgetId == iWidgetId;
    }

// -----------------------------------------------------------------------------
// CTransaction::AppendL()
//
// -----------------------------------------------------------------------------
//
void CTransaction::AppendL( CTransactionItem* aItem )
    {
    User::LeaveIfError( iItems.InsertInAddressOrder( aItem ) );
    }

// -----------------------------------------------------------------------------
// CTransaction::Items()
//
// -----------------------------------------------------------------------------
//
const RPointerArray< CTransactionItem >& CTransaction::Items() const
    {
    return iItems;
    }

// End of file
