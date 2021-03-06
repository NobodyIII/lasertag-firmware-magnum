#ifndef _W25QXXCONFIG_H
#define _W25QXXCONFIG_H

#include "main.h"

#define _W25QXX_SPI                   hspi2
#define _W25QXX_CS_GPIO               SPIFLASH_NSS_GPIO_Port
#define _W25QXX_CS_PIN                SPIFLASH_NSS_Pin
#define _W25QXX_USE_FREERTOS          0
#define _W25QXX_DEBUG                 0

#endif
