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

#ifndef __TESTPUBLISHERAPPLICATION_H__
#define __TESTPUBLISHERAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "TestPublisher.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidTestPublisherApp =
    {
    _UID3
    };

// CLASS DECLARATION

/**
 * CTestPublisherApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CTestPublisherApplication is the application part of the
 * AVKON application framework for the TestPublisher example application.
 */
class CTestPublisherApplication : public CAknApplication
    {
public:
    // Functions from base classes

    /**
     * From CApaApplication, AppDllUid.
     * @return Application's UID (KUidTestPublisherApp).
     */
    TUid AppDllUid() const;

protected:
    // Functions from base classes

    /**
     * From CApaApplication, CreateDocumentL.
     * Creates CTestPublisherDocument document object. The returned
     * pointer in not owned by the CTestPublisherApplication object.
     * @return A pointer to the created document object.
     */
    CApaDocument* CreateDocumentL();
    };

#endif // __TESTPUBLISHERAPPLICATION_H__
// End of File
