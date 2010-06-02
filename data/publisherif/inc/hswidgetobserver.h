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


#ifndef __HSWIDGETOBSERVER_H__
#define __HSWIDGETOBSERVER_H__

//  System includes 
#include <e32base.h>    

// User includes

// Forward declarations

//  Constants

//  Class Definitions
class MHsWidgetObserver
    {
public:
    enum EState
        {
        /** 
         * Widget instance should enter to suspended state.
         * This means that Homescreen is not visible anymore. 
         */
        ESuspend = 0,
        /** 
         * Widget instance should enter to alive state.
         * This means that Homescreen visible. Resource consumption and publishing is allowed.
         */                
        EAlive,
        /**
         * Widget instance may enter to online state.
         * This means that it may consume network resources.
         */
        EOnline,
        /**
         * Widget instance must enter to offline state.
         * This means that it is not allowed to consume network resources.
         */
        EOffline        
        };
    
    enum EStartReason
        {
        /**
         * Widget was started because system starts-up. 
         */
        ESystemStart = 1,
        /**
         * Widget was started because of Homescreen page change. 
         */
        EPageStart,
        /**
         * Widget was started because of it was added to Homescreen. 
         */
        EWidgetStart
        };

    enum EStopReason
        {
        /**
         * Widget was stopped because system shutsdown.
         */
        ESystemStop = 1,
        /**
         * Widget was stopped because of Homescreen page change.
         */
        EPageStop,
        /**
         * Widget was stopped because it was removed from Homescreen. 
         */
        EWidgetStop
        };
        
    /**
     * Requests this publisher's identity.
     * 
     * @return Publisher identity in <UID:PublisherName> format.
     *         The identity must map to xml <configuration> element, i.e.:
     *         <configuration name="publisher" value="MyUid:MyPublisherName"/>
     */
    virtual const TDesC& Identity() = 0;    
    
    /**
     * Notifies that Homescreen has started widget.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aReason Reason why Homescreen started the widget instance. 
     */
    virtual void NotifyWidgetStarted( 
        const TDesC& aWidgetId, 
        EStartReason aReason ) = 0;

    /**
     * Notifies that Homescreen has stopped widget.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aReason Reason why Homescreen stopped the widget instance. 
     */    
    virtual void NotifyWidgetStopped( 
        const TDesC& aWidgetId, 
        EStopReason aReason ) = 0;

    /**
     * Notifies that Homescreen has changed widget state.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aState New state for the widget instance. 
     */        
    virtual void NotifyWidgetState( 
        const TDesC& aWidgetId, 
        EState aState ) = 0;    

    /**
     * Notifies a widget specific event.
     * 
     * @param aWidgetId Widget Id identifying the widget instance.
     * @param aEvent Event from the widget instance. 
     * @param aParam Event parameter from the widget instance.
     */            
    virtual void NotifyWidgetEvent(
        const TDesC& aWidgetId,
        const TDesC& aEvent,
        const TDesC& aParam ) = 0;
    };

#endif // __HSWIDGETOBSERVER_H__

// End of file
