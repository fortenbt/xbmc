/*
 *      Copyright (C) 2014 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "addons/include/xbmc_peripheral_utils.hpp"
#include "input/joysticks/IJoystickButtonMap.h"
#include "peripherals/addons/PeripheralAddon.h"

namespace PERIPHERALS
{
  class CAddonJoystickButtonMap : public IJoystickButtonMap
  {
  public:
    CAddonJoystickButtonMap(const PERIPHERALS::PeripheralAddonPtr& addon, unsigned int index);

    virtual ~CAddonJoystickButtonMap(void) { }

    virtual bool Load(void);

    JoystickActionID GetAction(const CButtonPrimitive& button);

    bool GetButtonPrimitive(JoystickActionID id, CButtonPrimitive& button);

    bool GetAnalogStick(JoystickActionID id, int& horizIndex, bool& horizInverted,
                                             int& vertIndex,  bool& vertInverted);

    bool GetAccelerometer(JoystickActionID id, int& xIndex, bool& xInverted,
                                               int& yIndex, bool& yInverted,
                                               int& zIndex, bool& zInverted);

  private:
    PERIPHERALS::PeripheralAddonPtr m_addon;
    unsigned int                    m_index;
    ADDON::ButtonMap                m_buttonMap;
  };
}