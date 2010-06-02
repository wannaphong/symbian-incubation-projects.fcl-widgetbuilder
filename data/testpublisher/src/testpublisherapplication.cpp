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
#include "TestPublisher.hrh"
#include "TestPublisherDocument.h"
#include "TestPublisherApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestPublisherApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CTestPublisherApplication::CreateDocumentL()
    {
    // Create an TestPublisher document, and return a pointer to it
    return CTestPublisherDocument::NewL(*this);
    }

// -----------------------------------------------------------------------------
// CTestPublisherApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CTestPublisherApplication::AppDllUid() const
    {
    // Return the UID for the TestPublisher application
    return KUidTestPublisherApp;
    }

// End of File
