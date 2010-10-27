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

#include <ecom/implementationproxy.h>
#include "#replace#renderer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Symbian static 1st phase constructor
// -----------------------------------------------------------------------------
//
C#replace#Renderer* C#replace#Renderer::NewL()
    {
    C#replace#Renderer* self = C#replace#Renderer::NewLC();
    CleanupStack::Pop( self );
    return self;
    }
// -----------------------------------------------------------------------------
// Symbian static 1st phase constructor
// -----------------------------------------------------------------------------
//
C#replace#Renderer* C#replace#Renderer::NewLC()
    {
    C#replace#Renderer* self = new( ELeave ) C#replace#Renderer();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// C++ destructor
// -----------------------------------------------------------------------------
//
C#replace#Renderer::~C#replace#Renderer()
    {
    }

// -----------------------------------------------------------------------------
// Handles key events.
// -----------------------------------------------------------------------------
//
TKeyResponse C#replace#Renderer::OfferKeyEventL( const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    }

// -----------------------------------------------------------------------------
// Set window for this control
// -----------------------------------------------------------------------------
//
void C#replace#Renderer::SetContainerWindowL( const CCoeControl &aContainer )
    {
    CCoeControl::SetContainerWindowL( aContainer );
    }

// -----------------------------------------------------------------------------
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void C#replace#Renderer::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    CCoeControl::HandlePointerEventL( aPointerEvent );
    }

// -----------------------------------------------------------------------------
// Returns the number of component controls
// -----------------------------------------------------------------------------
//
TInt C#replace#Renderer::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// Returns the specified control
// -----------------------------------------------------------------------------
//
CCoeControl* C#replace#Renderer::ComponentControl( TInt aIndex ) const
    {
    return NULL;
    }

// -----------------------------------------------------------------------------
// Skin change notification.
// -----------------------------------------------------------------------------
//
void C#replace#Renderer::SkinChanged()
    {
    }

// -----------------------------------------------------------------------------
// EnterPowerSaveModeL
// -----------------------------------------------------------------------------
//
void C#replace#Renderer::EnterPowerSaveModeL()
    {
    }

// -----------------------------------------------------------------------------
// ExitPowerSaveModeL
//
// -----------------------------------------------------------------------------
//
void C#replace#Renderer::ExitPowerSaveModeL()
    {
    }

// -----------------------------------------------------------------------------
// Called if focus changes
// -----------------------------------------------------------------------------
//
void C#replace#Renderer::FocusChanged( TDrawNow /*aDrawNow*/ )
    {
    }

// -----------------------------------------------------------------------------
// Called if position or size changes
// -----------------------------------------------------------------------------
//
void C#replace#Renderer::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// Draws the carousel component
// -----------------------------------------------------------------------------
//
void C#replace#Renderer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc( SystemGc() );
    gc.DrawEllipse( aRect );
    }

// -----------------------------------------------------------------------------
// C++ default constructor
// -----------------------------------------------------------------------------
//
C#replace#Renderer::C#replace#Renderer()
    {
    // Do nothing
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void C#replace#Renderer::ConstructL()
    {
    }

// ============================ PUBLIC FUNCTIONS ===============================

const TImplementationProxy KImplementationTable[] =
    {
#ifdef __EABI__
    IMPLEMENTATION_PROXY_ENTRY( 0x22334455, C#replace#Renderer::NewL )
#else
    { { 0x22334455 }, C#replace#Renderer::NewL }
#endif
    };

// -----------------------------------------------------------------------------
// Returns the list of implementations provided by the plugin
// -----------------------------------------------------------------------------
//
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(
    TInt& aTableCount )
    {
    aTableCount = sizeof( KImplementationTable ) / sizeof( TImplementationProxy );
    return KImplementationTable;
    }

