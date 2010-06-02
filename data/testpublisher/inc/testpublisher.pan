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

#ifndef __TESTPUBLISHER_PAN__
#define __TESTPUBLISHER_PAN__

/** TestPublisher application panic codes */
enum TTestPublisherPanics
    {
    ETestPublisherUi = 1
    // add further panics here
    };

inline void Panic(TTestPublisherPanics aReason)
    {
    _LIT(applicationName, "TestPublisher");
    User::Panic(applicationName, aReason);
    }

#endif // __TESTPUBLISHER_PAN__
