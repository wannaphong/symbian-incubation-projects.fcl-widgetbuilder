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
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>

#include <TestPublisher_0xE5555555.rsg>

#include "TestPublisher.hrh"
#include "TestPublisher.pan"
#include "TestPublisherApplication.h"
#include "TestPublisherAppUi.h"
#include "TestPublisherAppView.h"

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestPublisherAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestPublisherAppUi::ConstructL()
    {
    // Initialise app UI with standard value.
    BaseConstructL(CAknAppUi::EAknEnableSkin);

    // Create view object
    iAppView = CTestPublisherAppView::NewL(ClientRect());
    }
// -----------------------------------------------------------------------------
// CTestPublisherAppUi::CTestPublisherAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CTestPublisherAppUi::CTestPublisherAppUi()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CTestPublisherAppUi::~CTestPublisherAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CTestPublisherAppUi::~CTestPublisherAppUi()
    {
    if (iAppView)
        {
        delete iAppView;
        iAppView = NULL;
        }

    }

// -----------------------------------------------------------------------------
// CTestPublisherAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CTestPublisherAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        case ECommand1:
            {

            // Load a string from the resource file and display it
            HBufC* textResource = StringLoader::LoadLC(R_COMMAND1_TEXT);
            CAknInformationNote* informationNote;

            informationNote = new (ELeave) CAknInformationNote;

            // Show the information Note with
            // textResource loaded with StringLoader.
            informationNote->ExecuteLD(*textResource);

            // Pop HBuf from CleanUpStack and Destroy it.
            CleanupStack::PopAndDestroy(textResource);
            }
            break;
        case ECommand2:
            {

            }
            break;
        case EAbout:
            {

            CAknMessageQueryDialog* dlg =
                    new (ELeave) CAknMessageQueryDialog();
            dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
            HBufC* title = iEikonEnv->AllocReadResourceLC(
                    R_ABOUT_DIALOG_TITLE);
            dlg->QueryHeading()->SetTextL(*title);
            CleanupStack::PopAndDestroy(); //title
            HBufC* msg = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TEXT);
            dlg->SetMessageTextL(*msg);
            CleanupStack::PopAndDestroy(); //msg
            dlg->RunLD();
            }
            break;
        default:
            Panic( ETestPublisherUi);
            break;
        }
    }
// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CTestPublisherAppUi::HandleStatusPaneSizeChange()
    {
    iAppView->SetRect(ClientRect());
    }

// End of File
