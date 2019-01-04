/*
 * switch.c
 *
 *  Created on: Jun 30, 2015
 *      Author: tim
 */

#include <string.h>

#include <ble.h>
#include <ble_gatts.h>
#include <app_error.h>
#include <nordic_common.h>
#include <nrf_gpio.h>

#include "homekit/homekit-config.h"
#include "homekit/uuids.h"
#include "homekit/service.h"
#include "switch.h"

#define NAME  "Temperature Sensor"
#if defined(NRF52)
#define LED   17 // P0.17
#else
#define LED   21 // P0.21
#endif
static float current_temperature = 0;

static void service_temperature_sensor_state(uint8_t** p_data, uint16_t* p_length, const service_characteristic_t* characteristic)
{

	*p_data = (uint8_t*)&current_temperature;
  *p_length = sizeof(current_temperature);
}


void service_tmperature_sensor_init(void)
{
  static const service_service_t service =
  {
    .uuid = { .type = BLE_UUID_TYPE_BLE, .uuid = HOMEKIT_SERVICE_TEMPERATURE_SENSOR }
  };
  static const service_characteristic_t characteristics[] =
  {
    { .uuid = { .type = HOMEKIT_BASE_TYPE, .uuid = HOMEKIT_NAME }, SERVICE_STRING(NAME) },
    { .uuid = { .type = HOMEKIT_BASE_TYPE, .uuid = HOMEKIT_TEMPERATURE }, .length = 1, .read = service_temperature_sensor_state, .notify = 1 },
    {}
  };
  service_addService(&service, characteristics);

//  nrf_gpio_cfg_output(LED);
//  nrf_gpio_pin_write(LED, !switch_state);
}
