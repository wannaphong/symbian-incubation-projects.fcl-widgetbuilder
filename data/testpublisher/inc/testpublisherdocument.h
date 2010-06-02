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

#ifndef __TESTPUBLISHERDOCUMENT_h__
#define __TESTPUBLISHERDOCUMENT_h__

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CTestPublisherAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CTestPublisherDocument application class.
 * An instance of class CTestPublisherDocument is the Document part of the
 * AVKON application framework for the TestPublisher example application.
 */
class CTestPublisherDocument : public CAknDocument
    {
public:
    // Constructors and destructor

    /**
     * NewL.
     * Two-phased constructor.
     * Construct a CTestPublisherDocument for the AVKON application aApp
     * using two phase construction, and return a pointer
     * to the created object.
     * @param aApp Application creating this document.
     * @return A pointer to the created instance of CTestPublisherDocument.
     */
    static CTestPublisherDocument* NewL(CEikApplication& aApp);

    /**
     * NewLC.
     * Two-phased constructor.
     * Construct a CTestPublisherDocument for the AVKON application aApp
     * using two phase construction, and return a pointer
     * to the created object.
     * @param aApp Application creating this document.
     * @return A pointer to the created instance of CTestPublisherDocument.
     */
    static CTestPublisherDocument* NewLC(CEikApplication& aApp);

    /**
     * ~CTestPublisherDocument
     * Virtual Destructor.
     */
    virtual ~CTestPublisherDocument();

public:
    // Functions from base classes

    /**
     * CreateAppUiL
     * From CEikDocument, CreateAppUiL.
     * Create a CTestPublisherAppUi object and return a pointer to it.
     * The object returned is owned by the Uikon framework.
     * @return Pointer to created instance of AppUi.
     */
    CEikAppUi* CreateAppUiL();

private:
    // Constructors

    /**
     * ConstructL
     * 2nd phase constructor.
     */
    void ConstructL();

    /**
     * CTestPublisherDocument.
     * C++ default constructor.
     * @param aApp Application creating this document.
     */
    CTestPublisherDocument(CEikApplication& aApp);

    };

#endif // __TESTPUBLISHERDOCUMENT_h__
// End of File
