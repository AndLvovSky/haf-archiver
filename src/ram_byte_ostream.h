#ifndef RAM_BYTE_OSTREAM_H
#define RAM_BYTE_OSTREAM_H

#include "byte_ostream.h"
#include "data.h"

#include <vector>

/**
 * @brief The RamByteOstream class implements ByteOstream, using RAM memory.
 *
 * The output is keeping inside this class. Basically used for testing.
 */
class RamByteOstream : public ByteOstream {

private:

    /**< Bytes array. */
    std::vector<char> data;

public:

    /**
     * Default constructor.
     */
    RamByteOstream();

    void putByte(char byte) override;

    /**
     * @return Accumulated bytes.
     */
    Data getData();

};

#endif // RAM_BYTE_OSTREAM_H
