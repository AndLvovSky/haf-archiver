#include "key.h"

Key::Key(Node::NodePtr root,
    Data::SizeType oldByteCount, Data::SizeType bitCount) :
    root(root), oldByteCount(oldByteCount), bitCount(bitCount) {}
