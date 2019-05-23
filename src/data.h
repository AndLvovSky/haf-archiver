#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

/**
 * @brief The Data class represents byte array.
 */
struct Data {

    /** Byte array size. */
    typedef unsigned int SizeType;

    /** Container for bytes. */
    typedef std::vector<char> Chunks;

    SizeType size; /**< Size of the array. */

    Chunks chunks; /**< Array content. */

    /**
     * Default constructor.
     */
    Data();

    /**
     * Copy constructor.
     */
    Data(const Data& data);

    /**
     * Creates Data object from std::string.
     * @param text - string to convert.
     */
    Data(const std::string& text);

    /**
     * Creates Data with specified array size.
     */
    Data(SizeType size);

    /**
     * Initialize Data with specified array size and content.
     * @param size - array size.
     * @param chunks - array content.
     */
    Data(SizeType size, const Chunks& chunks);

    /**
     *  Default destructor.
     */
    ~Data() = default;

    /**
     * @return Byte in specified position.
     */
    char& operator [] (SizeType pos);

    /**
     * Assignment operator.
     */
    void operator = (const Data& other);

    /**
     * Casting operator to std::string.
     */
    operator std::string ();

};

#endif // DATA_H
