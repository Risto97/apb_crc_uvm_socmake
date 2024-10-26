#ifndef _APB_BASE_SEQUENCE_H_
#define _APB_BASE_SEQUENCE_H_

#include <cstdint>
#include <uvc_apb.h>
#include <iostream>
#include <sstream>
#include <string>
#include <systemc>
#include <uvm>

class base_sequence : public uvm::uvm_sequence<uvc::apb::rw, uvc::apb::rw> {
public:
    std::vector<unsigned int> data;

    base_sequence(const std::string& name)
        : uvm::uvm_sequence<uvc::apb::rw, uvc::apb::rw>(name)
        {
        }

    UVM_OBJECT_PARAM_UTILS(base_sequence);

    uint32_t ARCHI_READ(uint32_t addr);
    void ARCHI_WRITE(uint32_t addr, uint32_t value);

    void pre_body();
    void body();
    void post_body();

    void message(const uvc::apb::rw& p);
};
#endif

