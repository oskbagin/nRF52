
#ifndef OUR_SERVICE_H__
#define OUR_SERVICE_H__

#include <stdint.h>
#include "ble.h"
#include "ble_srv_common.h"

#define BLE_UUID_OUR_BASE_UUID              {{0x6a, 0x4a, 0x22, 0x05, 0x77, 0x08, 0x79, 0xa1, 0x39, 0x43, 0xdd, 0x48, 0xe2, 0x43, 0xd3, 0x12}} // 128-bit base UUID
#define BLE_UUID_OUR_SERVICE_UUID                0x43E0 
#define BLE_UUID_OUR_CHARACTERISTC_UUID          0x43E1 

#define NUM_OF_CHAR 12

typedef struct
{
    uint16_t                    conn_handle; 
    uint16_t                    service_handle;        
    ble_gatts_char_handles_t    char_handles;
}ble_os_t;

/**@brief Function for handling BLE Stack events related to our service and characteristic.
 *
 * @details Handles all events from the BLE stack of interest to Our Service.
 *
 * @param[in]   p_our_service       Our Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_our_service_on_ble_evt(ble_os_t * p_our_service, ble_evt_t * p_ble_evt);

/**@brief Function for initializing our new service.
 *
 * @param[in]   p_our_service       Pointer to Our Service structure.
 */
void our_service_init(ble_os_t * p_our_service);

/**@brief Function for updating and sending new characteristic values
 *
 * @details The application calls this function whenever our timer_timeout_handler triggers
 *
 * @param[in]   p_our_service                     Our Service structure.
 * @param[in]   characteristic_value     New characteristic value.
 */

/** 
*/
#endif  /* _ OUR_SERVICE_H__ */
