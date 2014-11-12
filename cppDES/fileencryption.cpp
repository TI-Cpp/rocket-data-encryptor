#include "fileencryption.h"

FileEncryption::FileEncryption(uint64_t key) :
    des(key, 0x0000000000000000)
{
}

int FileEncryption::encrypt(string input, string output)
{
    return cipher(input, output, false);
}

int FileEncryption::decrypt(string input, string output)
{
    return cipher(input, output, true);
}

int FileEncryption::cipher(string input, string output, bool mode)
{
    ifstream ifile;
    ofstream ofile;
    ui64 buffer;

    ifile.open(input,  ios::binary | ios::in | ios::ate);
    ofile.open(output, ios::binary | ios::out);

    int size = ifile.tellg();
    ifile.seekg(0, ios::beg);

    int block = size / 8;
    if(mode) block--;

    for(int i = 0; i < block; i++)
    {
        ifile.read((char*) &buffer, 8);

        if(mode)
            buffer = des.decrypt(buffer);
        else
            buffer = des.encrypt(buffer);

        ofile.write((char*) &buffer, 8);
    }

    if(mode == false)
    {
        // Amount of padding needed
        int padding = 8 - (size % 8);

        // Padding cannot be 0 (pad full block)
        if (padding == 0)
            padding  = 8;

        // Read remaining part of file
        buffer = (ui64) 0;
        if(padding != 8)
            ifile.read((char*) &buffer, 8 - padding);

        // Pad block with a 1 followed by 0s
        int shift = padding * 8;
        buffer <<= shift;
        buffer  |= (ui64) 0x0000000000000001 << (shift - 1);

        buffer = des.encrypt(buffer);
        ofile.write((char*) &buffer, 8);
    }
    else
    {
        // Read last line of file
        ifile.read((char*) &buffer, 8);
        buffer = des.decrypt(buffer);

        // Amount of padding on file
        int padding = 0;

        // Check for and record padding on end
        while(!(buffer & 0x00000000000000ff))
        {
            buffer >>= 8;
            padding++;
        }

        buffer >>= 8;
        padding++;

        if(padding != 8)
            ofile.write((char*) &buffer, 8 - padding);
    }

    ifile.close();
    ofile.close();
    return 0;
}
