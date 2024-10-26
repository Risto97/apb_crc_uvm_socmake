#ifndef _APB_CRC_REF_H_
#define _APB_CRC_REF_H_

#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <bit>

#include "CRC.h"

#include <systemc>

#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"

class apb_crc_ref : public sc_core::sc_module {
public:
    tlm_utils::simple_target_socket<apb_crc_ref, 32> socket;
    
    CRC::Parameters<crcpp_uint32, 32> crc_params;
    uint32_t crc_ref_value = 0;

    apb_crc_ref(sc_core::sc_module_name name) : sc_core::sc_module(name) {
        socket.register_b_transport(this, &apb_crc_ref::b_transport);

        crc_params.initialValue = crc_ref_value;
        crc_params.polynomial = 0x04c11db7;
        crc_params.reflectInput = 0;
        crc_params.reflectOutput = 0;
        crc_params.finalXOR = 0;

    }
    SC_HAS_PROCESS(apb_crc_ref);

    virtual void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay){

        tlm::tlm_command cmd  = trans.get_command();
        uint32_t         addr = trans.get_address();
        uint8_t          *ptr = trans.get_data_ptr();
        uint32_t         len  = trans.get_data_length();
        uint8_t          *byt = trans.get_byte_enable_ptr();
        uint32_t         wid  = trans.get_streaming_width();

        uint32_t data = *(uint32_t*)ptr;


        if(cmd == tlm::tlm_command::TLM_WRITE_COMMAND ){
            if(addr == 0){
                crc_params.initialValue = crc_ref_value;
                crc_ref_value = CRC::Calculate(&data, 1, crc_params);
                trans.set_response_status(tlm::TLM_OK_RESPONSE);
            } else {
                trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
            }
        }

        if(cmd == tlm::tlm_command::TLM_READ_COMMAND ){
            if(addr == 4){
                trans.set_data_ptr(reinterpret_cast<uint8_t *>(&crc_ref_value));
                trans.set_data_length(4);
                trans.set_response_status(tlm::TLM_OK_RESPONSE);
            } else {
                trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
            }
        }


        // trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }
};

#endif


// // #define crcpp_uint32
//
// #include "CRC.h" // Only need to include this header file!
//                  // No libraries need to be included. No project settings need to be messed with.
// 				 
// #include <iomanip>  // Includes ::std::hex
// #include <iostream> // Includes ::std::cout
// #include <cstdint>  // Includes ::std::uint32_t
//
// int main(int argc, char ** argv)
// {
// 	uint32_t val = 0xC;
// 	
//     CRC::Parameters<crcpp_uint32, 32> crc_params;
//     crc_params.initialValue = 0;
//     crc_params.polynomial = 0x814141AB;
//     crc_params.reflectInput = false;
//     crc_params.reflectOutput = false;
//     crc_params.finalXOR = false;
//
// 	std::uint32_t crc = CRC::Calculate(&val, 1, crc_params);
// 	
//     std::cout << "I expect: " << "0xa0a0d58\n";
// 	std::cout << "I got   : 0x" << std::hex << crc << "\n";
// 	
// 	return 0;
// }
