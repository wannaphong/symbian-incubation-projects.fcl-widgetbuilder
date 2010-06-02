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
#include "TestPublisherAppUi.h"
#include "TestPublisherDocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestPublisherDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestPublisherDocument* CTestPublisherDocument::NewL(CEikApplication& aApp)
    {
    CTestPublisherDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestPublisherDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestPublisherDocument* CTestPublisherDocument::NewLC(CEikApplication& aApp)
    {
    CTestPublisherDocument* self = new (ELeave) CTestPublisherDocument(aApp);

    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CTestPublisherDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestPublisherDocument::ConstructL()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CTestPublisherDocument::CTestPublisherDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CTestPublisherDocument::CTestPublisherDocument(CEikApplication& aApp) :
    CAknDocument(aApp)
    {
    // No implementation required
    }

// ---------------------------------------------------------------------------
// CTestPublisherDocument::~CTestPublisherDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CTestPublisherDocument::~CTestPublisherDocument()
    {
    // No implementation required
    }

// ---------------------------------------------------------------------------
// CTestPublisherDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CTestPublisherDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it;
    // the framework takes ownership of this object
    return new (ELeave) CTestPublisherAppUi;
    }

// End of File
