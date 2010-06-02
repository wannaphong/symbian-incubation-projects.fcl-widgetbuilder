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
#ifndef __TESTPUBLISHERAPPUI_h__
#define __TESTPUBLISHERAPPUI_h__

// INCLUDES
#include <aknappui.h>

// FORWARD DECLARATIONS
class CTestPublisherAppView;

// CLASS DECLARATION
/**
 * CTestPublisherAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CTestPublisherAppUi : public CAknAppUi
    {
public:
    // Constructors and destructor

    /**
     * ConstructL.
     * 2nd phase constructor.
     */
    void ConstructL();

    /**
     * CTestPublisherAppUi.
     * C++ default constructor. This needs to be public due to
     * the way the framework constructs the AppUi
     */
    CTestPublisherAppUi();

    /**
     * ~CTestPublisherAppUi.
     * Virtual Destructor.
     */
    virtual ~CTestPublisherAppUi();

private:
    // Functions from base classes

    /**
     * From CEikAppUi, HandleCommandL.
     * Takes care of command handling.
     * @param aCommand Command to be handled.
     */
    void HandleCommandL(TInt aCommand);

    /**
     *  HandleStatusPaneSizeChange.
     *  Called by the framework when the application status pane
     *  size is changed.
     */
    void HandleStatusPaneSizeChange();

private:
    // Data

    /**
     * The application view
     * Owned by CTestPublisherAppUi
     */
    CTestPublisherAppView* iAppView;

    };

#endif // __TESTPUBLISHERAPPUI_h__
// End of File
