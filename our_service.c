
#include <stdint.h>
#include <string.h>
#include "nrf_gpio.h"
#include "our_service.h"
#include "ble_srv_common.h"
#include "app_error.h"

void ble_our_service_on_ble_evt(ble_os_t * p_our_service, ble_evt_t * p_ble_evt)
{
    
}

/**@brief Function for adding our new characterstic to "Our service" that we initiated in the previous tutorial. 
 *
 * @param[in]   p_our_service        Our Service structure.
 *
 */
static uint32_t our_char_add(ble_os_t * p_our_service)
{
    uint32_t            err_code;
		ble_uuid128_t       base_uuid = BLE_UUID_OUR_BASE_UUID;
		ble_uuid_t          char_uuid[NUM_OF_CHAR];
		
		ble_gatts_char_md_t char_md[NUM_OF_CHAR];
		memset(&char_md, 0, sizeof(char_md));
		
		ble_gatts_attr_md_t cccd_md[NUM_OF_CHAR];
		memset(&cccd_md, 0, sizeof(cccd_md));
	
		ble_gatts_attr_md_t attr_md[NUM_OF_CHAR];
		memset(&attr_md, 0, sizeof(attr_md));
	
		ble_gatts_attr_t    attr_char_value[NUM_OF_CHAR];
		memset(&attr_char_value, 0, sizeof(attr_char_value));
	
	for(int i=0;i<NUM_OF_CHAR;i++){
		char_uuid[i].uuid      = BLE_UUID_OUR_CHARACTERISTC_UUID;
		err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid[i].type);
		APP_ERROR_CHECK(err_code);
		
		if(i<9)
			char_uuid[i].uuid      = BLE_UUID_OUR_CHARACTERISTC_UUID+i;
		else if(i>=9)
			char_uuid[i].uuid      = BLE_UUID_OUR_CHARACTERISTC_UUID+i+6;
		
		err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid[i].type);
		APP_ERROR_CHECK(err_code);
		
		if(i!=3 && i!=4 && i!=10 && i!=11){
			char_md[i].char_props.write = 1;
		}
		if(i!=1 && i!=2 && i!=5 && i!=7 && i!=8 && i!=9){
			char_md[i].char_props.read = 1;
		}
		
		attr_md[i].vloc        = BLE_GATTS_VLOC_STACK;
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md[i].read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md[i].write_perm);
		
		attr_char_value[i].p_uuid      = &char_uuid[i];
		attr_char_value[i].p_attr_md   = &attr_md[i];
	}
		
		
	/*adding chars to service*/
  for(int i=0;i<NUM_OF_CHAR;i++){
		err_code = sd_ble_gatts_characteristic_add(p_our_service->service_handle,
                                   &char_md[i],
                                   &attr_char_value[i],
                                   &p_our_service->char_handles);
		APP_ERROR_CHECK(err_code);
	}
	
    return NRF_SUCCESS;
}


/**@brief Function for initiating our new service.
 *
 * @param[in]   p_our_service        Our Service structure.
 *
 */
void our_service_init(ble_os_t * p_our_service)
{
    uint32_t   err_code; // Variable to hold return codes from library and softdevice functions
	
    ble_uuid_t        service_uuid;
    ble_uuid128_t     base_uuid = BLE_UUID_OUR_BASE_UUID;
    service_uuid.uuid = BLE_UUID_OUR_SERVICE_UUID;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &service_uuid.type);
    APP_ERROR_CHECK(err_code);    
    
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &p_our_service->service_handle);
    
    APP_ERROR_CHECK(err_code);
    our_char_add(p_our_service);
}
