/*
 * EEZ PSU Firmware
 * Copyright (C) 2015 Envox d.o.o.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#pragma once

#include "temperature.h"

namespace eez {
namespace psu {

class Channel;

namespace profile {

struct Parameters;

}
}
} // namespace eez::psu::profile

namespace eez {
namespace psu {
/// Store/restore of persistent configuration data (device configuration, calibration parameters, profiles) using external EEPROM.
namespace persist_conf {

/// Header of the every block stored in EEPROM. It contains checksum and version.
struct BlockHeader {
    uint32_t checksum;
    uint16_t version;
};

/// Device binary flags stored in DeviceConfiguration.
struct DeviceFlags {
    int beep_enabled : 1;
    int date_valid : 1;
    int time_valid : 1;
    int profile_auto_recall : 1;
    int reserved4 : 1;
    int reserved5 : 1;
    int reserved6 : 1;
    int reserved7 : 1;
    int reserved8 : 1;
    int reserved9 : 1;
    int reserved10 : 1;
    int reserved11 : 1;
    int reserved12 : 1;
    int reserved13 : 1;
    int reserved14 : 1;
    int reserved15 : 1;
};

/// Device configuration block.
struct DeviceConfiguration {
    BlockHeader header;
    char calibration_password[PASSWORD_MAX_LENGTH + 1];
    DeviceFlags flags;
    uint8_t date_year;
    uint8_t date_month;
    uint8_t date_day;
    uint8_t time_hour;
    uint8_t time_minute;
    uint8_t time_second;
    int8_t profile_auto_recall_location;
#ifdef EEZ_PSU_SIMULATOR
    bool gui_opened;
#endif // EEZ_PSU_SIMULATOR
};

extern DeviceConfiguration dev_conf;

void loadDevice();
bool saveDevice();

bool changePassword(const char *new_password, size_t new_password_len);

void enableBeep(bool enable);
bool isBeepEnabled();

bool readSystemDate(uint8_t &year, uint8_t &month, uint8_t &day);
void writeSystemDate(uint8_t year, uint8_t month, uint8_t day);

bool enableProfileAutoRecall(bool enable);
bool isProfileAutoRecallEnabled();
bool setProfileAutoRecallLocation(int location);
int getProfileAutoRecallLocation();

bool readSystemTime(uint8_t &hour, uint8_t &minute, uint8_t &second);
void writeSystemTime(uint8_t hour, uint8_t minute, uint8_t second);

void loadChannelCalibration(Channel *channel);
bool saveChannelCalibration(Channel *channel);

bool loadProfile(int location, profile::Parameters *profile);
bool saveProfile(int location, profile::Parameters *profile);

}
}
} // namespace eez::psu::persist_conf
