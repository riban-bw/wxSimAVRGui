#pragma once
#include <wx/string.h>

/** Class represents a profile of AVR device */
class avrProfile
{
    public:

        avrProfile(wxString sName, long lId, wxString sDeviceType, long lFrequency = 8000000, wxString sDescription = "") :
            m_lId(lId),
            m_lFrequency(lFrequency),
            m_sName(sName),
            m_sDescription(sDescription),
            m_sDeviceType(sDeviceType)
            {};

        /** @brief  Get the profile ID
        *   @return <i>long</i> Profile ID
        *   @note   Used as event id for menu events, etc.
        */
        long GetId() { return m_lId; };

        /** @brief  Get the profile name
        *   @return <i>wxString</i> Profile name
        */
        wxString GetName() { return m_sName; };

        /** @brief  Get the profile description
        *   @return <i>wxString</i> Profile description
        */
        wxString GetDescription() { return m_sDescription; };

        /** @brief  Get the device type
        *   @return <i>wxString</i> Device type
        */
        wxString GetDeviceType() { return m_sDeviceType; };

        /** @brief  Get the frequency
        *   @return <i>long</i> Frequency
        */
        long GetFrequency() { return m_lFrequency; };

        /** @brief  Set the profile ID
        *   @param  lId ID
        *   @note   Used as event id for menu events, etc.
        */
        void SetId(long lId) { m_lId = lId; };

        /** @brief  Set the profile name
        *   @param  sName Profile name
        */
        void SetName(wxString sName) { m_sName = sName; };

        /** @brief  Set the profile description
        *   @param  sDescription
        */
        void SetDescription(wxString sDescription) { m_sDescription = sDescription; };

        /** @brief  Set the profile device type
        *   @param  sType Device type
        */
        void SetDeviceType(wxString sType) { m_sDeviceType = sType; };

        /** @brief  Set the frequency
        *   @param  lFrequency Frequency
        */
        void SetFrequency(long lFrequency) { m_lFrequency = lFrequency; };

    private:

        long m_lId; //!< Unique ID used by application to identify profile, e.g. as menu event id
        long m_lFrequency; //!< Frequency of device
        wxString m_sName; //!< Descriptive name of profile used in menus and logs
        wxString m_sDescription; //!< Long description
        wxString m_sDeviceType; //!< Name of device type
};
