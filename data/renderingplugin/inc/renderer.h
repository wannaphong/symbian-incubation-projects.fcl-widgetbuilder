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

#ifndef __#replace#RENDERER_H
#define __#replace#RENDERER_H

#include <xnextrenderingpluginadapter.h>

// FORWARD DECLARATIONS

class C#replace#Renderer : public CXnExtRenderingPluginAdapter
    {
public:

    /**
    * Two-phased constructor.
    * @return Pointer to created object.
    */
    static C#replace#Renderer* NewL();

    /**
    * Two-phased constructor.
    * @return Pointer to created object.
    */
    static C#replace#Renderer* NewLC();
    
    /**
    * Destructor.
    */
    virtual ~C#replace#Renderer();

public: // from base classes

    /**
    * From CCoeControl Handles key events.
    * @since Series 60 3.1
    * @param aKeyEvent Key event.
    * @param aType Event type.
    * @return Key response
    */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
    TEventCode aType );
    
    /**
    * From CCoeControl
    */
    void SetContainerWindowL( const CCoeControl &aContainer );
    
    /**
    * See CCoeControl documentation
    */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

    /**
    * From CCoeControl, CountComponentControls
    * @return Number of component controls
    */
    TInt CountComponentControls() const;
    
    /**
    * From CCoeControl, ComponentControl
    * @param aIndex index of component control
    * @return pointer to the specified control
    */
    CCoeControl* ComponentControl( TInt aIndex ) const;
    
    /**
    * Skin change notification.
    * See CXnControlAdapter documentation
    * @since Series 60 3.1
    */
    void SkinChanged();
    
    /**
    * See CXnControlAdapter documentation
    */
    void EnterPowerSaveModeL();

    /**
    * See CXnControlAdapter documentation
    */
    void ExitPowerSaveModeL();
    
    protected: // from base classes
    
    /**
    * From CCoeControl
    * Called if focus changes
    */
    void FocusChanged( TDrawNow aDrawNow );
    
    /**
    * From CCoeControl
    * Called if position or size changes
    */
    void SizeChanged();

private: // from base classes

    /**
    * From CCoeControl, Draw
    * See CCoeControl documentation
    */
    void Draw( const TRect& aRect ) const;
    
    private:
    
    /**
    * C++ default constructor.
    */
    C#replace#Renderer();
    
    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

private: // Member data

    };

#endif // __#replace#RENDERER_H
