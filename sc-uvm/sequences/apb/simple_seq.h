#ifndef _SIMPLE_SEQ_H_
#define _SIMPLE_SEQ_H_

#include "base_sequence.h"

#include <uvc_apb.h>
#include <iostream>
#include <sstream>
#include <string>
#include <systemc>
#include <uvm>

class simple_seq : public base_sequence {
public:

    simple_seq(const std::string& name)
        : base_sequence(name)
        {

        }

    UVM_OBJECT_PARAM_UTILS(simple_seq);

    void body(){

        ARCHI_WRITE(0, 12);
        ARCHI_READ(4);

        for(int i = 0; i < 100; i++){
            ARCHI_WRITE(0, i*5);
            ARCHI_READ(4);
        }

        UVM_INFO(this->get_name(), "Finishing sequence", uvm::UVM_MEDIUM);
    };

};
#endif
