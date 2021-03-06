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
 
#include "psu.h"
#include <scpi-parser.h>
#include "scpi_psu.h"
#include "scpi_debug.h"

#if CONF_DEBUG

namespace eez {
namespace psu {

using namespace debug;

namespace scpi {

scpi_result_t debug_scpi_command(scpi_t *context) {
    return SCPI_RES_OK;
}

scpi_result_t debug_scpi_commandQ(scpi_t *context) {
    char buffer[512] = { 0 };
    char *p = buffer;

    sprintf(p, "max_loop_duration: %lu\n", max_loop_duration);
    p += strlen(p);

    sprintf(p, "last_loop_duration: %lu\n", last_loop_duration);
    p += strlen(p);

    sprintf(p, "total_ioexp_int_counter: %lu\n", total_ioexp_int_counter);
    p += strlen(p);

    sprintf(p, "last_ioexp_int_counter: %lu\n", last_ioexp_int_counter);
    p += strlen(p);

    sprintf(p, "CH1: u_dac=%u, u_mon_dac=%d, u_mon=%d, i_dac=%u, i_mon_dac=%d, i_mon=%d\n",
        (unsigned int)u_dac[0], (int)u_mon_dac[0], (int)u_mon[0],
        (unsigned int)i_dac[0], (int)i_mon_dac[0], (int)i_mon[0]);
    p += strlen(p);

    sprintf(p, "CH2: u_dac=%u, u_mon_dac=%d, u_mon=%d, i_dac=%u, i_mon_dac=%d, i_mon=%d\n",
        (unsigned int)u_dac[1], (int)u_mon_dac[1], (int)u_mon[1],
        (unsigned int)i_dac[1], (int)i_mon_dac[1], (int)i_mon[1]);
    p += strlen(p);

    SCPI_ResultCharacters(context, buffer, strlen(buffer));

    return SCPI_RES_OK;
}

}
}
} // namespace eez::psu::scpi

#endif // CONF_DEBUG