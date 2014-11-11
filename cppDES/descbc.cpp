#include "descbc.h"

DESCBC::DESCBC(uint64_t key, uint64_t iv) :
    des(key),
    iv(iv),
    last_block(iv)
{
}

ui64 DESCBC::encrypt(uint64_t block)
{
    last_block = des.encrypt(block ^ last_block);
    return last_block;
}

ui64 DESCBC::decrypt(uint64_t block)
{
    ui64 result = des.decrypt(block) ^ last_block;
    last_block = block;
    return result;
}

void DESCBC::reset()
{
    last_block = iv;
}
